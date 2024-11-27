#include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libelf.h>
#include <gelf.h>
#include <dlfcn.h>

#include "cpu-elf2.h"
#include "macro_common.h"

#define uint16_t unsigned short
#define CRICKET_ELF_NV_INFO_PREFIX ".nv.info"
#define CRICKET_ELF_NV_SHARED_PREFIX ".nv.shared."
#define CRICKET_ELF_NV_TEXT_PREFIX ".nv.text."
#define CRICKET_ELF_TEXT_PREFIX ".text."

#define CRICKET_ELF_FATBIN ".nv_fatbin"
#define CRICKET_ELF_REGFUN "_ZL24__sti____cudaRegisterAllv"

#define FATBIN_STRUCT_MAGIC 0x466243b1
#define FATBIN_TEXT_MAGIC   0xBA55ED50

struct  __attribute__((__packed__)) fat_elf_header
{
    uint32_t magic;
    uint16_t version;
    uint16_t header_size;
    uint64_t size;
};
struct  __attribute__((__packed__)) fat_text_header
{
    uint16_t kind;
    uint16_t unknown1;
    uint32_t header_size;
    uint64_t size;
    uint32_t compressed_size;       // Size of compressed data
    uint32_t unknown2;              // Address size for PTX?
    uint16_t minor;
    uint16_t major;
    uint32_t arch;
    uint32_t obj_name_offset;
    uint32_t obj_name_len;
    uint64_t flags;
    uint64_t zero;                  // Alignment for compression?
    uint64_t decompressed_size;     // Length of compressed data in decompressed representation.
                                    // There is an uncompressed footer so this is generally smaller
                                    // than size.
};

#define FATBIN_FLAG_64BIT     0x0000000000000001LL
#define FATBIN_FLAG_DEBUG     0x0000000000000002LL
#define FATBIN_FLAG_LINUX     0x0000000000000010LL
#define FATBIN_FLAG_COMPRESS  0x0000000000002000LL

#define INITIAL_CAPACITY 4


void hexdump(const uint8_t* data, size_t size)
{
    size_t pos = 0;
    while (pos < size) {
        printf("%#05zx: ", pos);
        for (int i = 0; i < 16; i++) {
            if (pos + i < size) {
                printf("%02x", data[pos + i]);
            } else {
                printf("  ");
            }
            if (i % 4 == 3) {
                printf(" ");
            }
        }
        printf(" | ");
        for (int i = 0; i < 16; i++) {
            if (pos + i < size) {
                if (data[pos + i] >= 0x20 && data[pos + i] <= 0x7e) {
                    printf("%c", data[pos + i]);
                } else {
                    printf(".");
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");
        pos += 16;
    }
}
int list_init(list *l, size_t element_size)
{
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    if (element_size == 0LL) {
        HLOG("element_size of 0 does not make sense");
        return 1;
    }
    memset(l, 0, sizeof(list));
    if ((l->elements = malloc(INITIAL_CAPACITY*element_size)) == NULL) {
        HLOG("allocation failed");
        return 1;
    }
    l->element_size = element_size;
    l->capacity = INITIAL_CAPACITY;
    l->length = 0LL;

    return 0;
}

int list_free(list *l)
{
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    free(l->elements);
    l->length = 0;
    l->capacity = 0;
    return 0;
}

int list_free_elements(list *l)
{
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    for (size_t i=0; i < l->length; ++i) {
        free(*(void**)list_get(l, i));
    }
    return 0;
}

int list_append(list *l, void **new_element)
{
    int ret = 0;
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    if (l->capacity == l->length) {
        l->elements = realloc(l->elements, l->capacity*2*l->element_size);
        if (l->elements == NULL) {
            HLOG("realloc failed.");
            /* the old pointer remains valid */
            return 1;
        }
        l->capacity *= 2;
    }
    if (new_element != NULL) {
        *new_element = list_get(l, l->length++);
    }

    return ret;
}

int list_append_copy(list *l, void *new_element)
{
    int ret = 0;
    void *elem;
    if ( (ret = list_append(l, &elem)) != 0) {
        goto out;
    }
    memcpy(elem, new_element, l->element_size);
 out:
    return ret;
}

int list_at(list *l, size_t at, void **element)
{
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    if (at >= l->length) {
        HLOG("accessing list out of bounds");
        return 1;
    }
    if (element != NULL) {
        *element = list_get(l, at);
    }
    return 0;
}

inline void* list_get(list *l, size_t at) {
    return (l->elements+at*l->element_size);
}

int list_insert(list *l, size_t at, void *new_element)
{
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    if (at > l->length) {
        HLOG("accessing list out of bounds");
        return 1;
    }
    if (at == l->length) {
        return list_append_copy(l, new_element);
    }

    if (list_append(l, NULL) != 0) {
        HLOG("error while lengthening list");
        return 1;
    }
    memmove(list_get(l, at+1), list_get(l, at), (l->length-at)*l->element_size);

    if (new_element != NULL) {
        memcpy(list_get(l, at), new_element, l->element_size);
    }

    l->length += 1; //appending a NULL element does not increase list length
    return 0;
}

int list_rm(list *l, size_t at)
{
    if (l == NULL) {
        HLOG("list parameter is NULL");
        return 1;
    }
    if (at >= l->length) {
        HLOG("accessing list out of bounds");
        return 1;
    }
    if (at < l->length-1) {
        memmove(list_get(l, at), list_get(l, at+1), (l->length-1-at)*l->element_size);
    }
    l->length -= 1;
    return 0;
}
int elf2_init(void)
{
    if (elf_version(EV_CURRENT) == EV_NONE) {
        HLOG("ELF library initialization failed: %s", elf_errmsg(-1));
        return -1;
    }
    return 0;
}

static int flag_to_str(char** str, uint64_t flag)
{
    return asprintf(str, "64Bit: %s, Debug: %s, Linux: %s, Compress %s",
        (flag & FATBIN_FLAG_64BIT) ? "yes" : "no",
        (flag & FATBIN_FLAG_DEBUG) ? "yes" : "no",
        (flag & FATBIN_FLAG_LINUX) ? "yes" : "no",
        (flag & FATBIN_FLAG_COMPRESS) ? "yes" : "no");
}

kernel_info_t* utils_search_info(list *kernel_infos, const char *kernelname)
{
    kernel_info_t *info = NULL;
    if (kernel_infos == NULL) {
        HLOG("list is NULL.");
        return NULL;
    }
    HLOG("searching for %s in %d entries", kernelname, kernel_infos->length);
    for (int i=0; i < kernel_infos->length; ++i) {
        if (list_at(kernel_infos, i, (void**)&info) != 0) {
            HLOG("no element at index %d", i);
        }
        if (strcmp(kernelname, info->name) == 0) {
            return info;
        }
    }
    return NULL;
}
static void print_header(struct fat_text_header *th)
{
    char* flagstr = NULL;
    flag_to_str(&flagstr, th->flags);

    HLOG( "text_header: fatbin_kind: %#x, header_size %#x, size %#zx, compressed_size %#x,\
 minor %#x, major %#x, arch %d, decompressed_size %#zx\n\tflags: %s\n",
        th->kind,
        th->header_size,
        th->size,
        th->compressed_size,
        th->minor,
        th->major,
        th->arch,
        th->decompressed_size,
        flagstr);
    HLOG( "\tunknown fields: unknown1: %#x, unknown2: %#x, zeros: %#zx\n",
        th->unknown1,
        th->unknown2,
        th->zero);

    free(flagstr);
}

/** Check the header of a fatbin
 * Performs some integrity checks and returns the elf header
 * @param fatbin_data Pointer to the fatbin data
 * @param fatbin_size Size of the fatbin data
 * @param decompressed_size Pointer to a variable that will be set to the size of the decompressed data
 * @param compressed_data Pointer to a variable that will be set to point to the compressed data
*/
static int get_elf_header(const uint8_t* fatbin_data, size_t fatbin_size, struct fat_elf_header **elf_header)
{
    struct fat_elf_header *eh = NULL;

    if (fatbin_data == NULL || elf_header == NULL) {
        HLOG("fatbin_data is NULL");
        return 1;
    }

    if (fatbin_size < sizeof(struct fat_elf_header)) {
        HLOG("fatbin_size is too small");
        return 1;
    }

    eh = (struct fat_elf_header*) fatbin_data;
    if (eh->magic != FATBIN_TEXT_MAGIC) {
        HLOG("Invalid magic  number: expected %#x but got %#x", FATBIN_TEXT_MAGIC, eh->magic);
        return 1;
    }

    if (eh->version != 1 || eh->header_size != sizeof(struct fat_elf_header)) {
        HLOG("fatbin text version is wrong or header size is inconsistent.\
            This is a sanity check to avoid reading a new fatbinary format");
        return 1;
    }
    
    *elf_header = eh;
    return 0;
}

/** Check the text header of a fatbin
 * Performs some integrity checks and returns the text header
 * @param fatbin_data Pointer to the fatbin data
 * @param fatbin_size Size of the fatbin data
 * @param decompressed_size Pointer to a variable that will be set to the size of the decompressed data
 * @param compressed_data Pointer to a variable that will be set to point to the compressed data
*/
static int get_text_header(const uint8_t* fatbin_data, size_t fatbin_size, struct fat_text_header **text_header)
{
    struct fat_text_header *th = NULL;

    if (fatbin_data == NULL || text_header == NULL) {
        HLOG("fatbin_data is NULL");
        return 1;
    }

    if (fatbin_size < sizeof(struct fat_text_header)) {
        HLOG("fatbin_size is too small");
        return 1;
    }

    th = (struct fat_text_header*)fatbin_data;

    if(th->obj_name_offset != 0) {
        if (((char*)th)[th->obj_name_offset + th->obj_name_len] != '\0') {
            HLOG("Fatbin object name is not null terminated");
        } else {
            char *obj_name = (char*)th + th->obj_name_offset;
            HLOG("Fatbin object name: %s (len:%#x)", obj_name, th->obj_name_len);
        }
    }

    *text_header = th;
    return 0;
}

/** Decompresses a fatbin file
 * @param input Pointer compressed input data
 * @param input_size Size of compressed data
 * @param output preallocated memory where decompressed output should be stored
 * @param output_size size of output buffer. Should be equal to the size of the decompressed data
 */
static size_t decompress(const uint8_t* input, size_t input_size, uint8_t* output, size_t output_size)
{
    size_t ipos = 0, opos = 0;  
    uint64_t next_nclen;  // length of next non-compressed segment
    uint64_t next_clen;   // length of next compressed segment
    uint64_t back_offset; // negative offset where redudant data is located, relative to current opos

    while (ipos < input_size) {
        next_nclen = (input[ipos] & 0xf0) >> 4;
        next_clen = 4 + (input[ipos] & 0xf);
        if (next_nclen == 0xf) {
            do {
                next_nclen += input[++ipos];
            } while (input[ipos] == 0xff);
        }
        
        if (memcpy(output + opos, input + (++ipos), next_nclen) == NULL) {
            HLOG("copying data");
            return 0;
        }
#ifdef FATBIN_DECOMPRESS_DEBUG
        printf("%#04zx nocompress (len:%#x):\n", opos, next_nclen);
        hexdump(output + opos, next_nclen);
#endif
        ipos += next_nclen;
        opos += next_nclen;
        if (ipos >= input_size || opos >= output_size) {
            break;
        }
        back_offset = input[ipos] + (input[ipos + 1] << 8);       
        ipos += 2;
        if (next_clen == 0xf+4) {
            do {
                next_clen += input[ipos++];
            } while (input[ipos - 1] == 0xff);
        }
#ifdef FATBIN_DECOMPRESS_DEBUG
        printf("%#04zx compress (decompressed len: %#x, back_offset %#x):\n", opos, next_clen, back_offset);
#endif
        if (next_clen <= back_offset) {
            if (memcpy(output + opos, output + opos - back_offset, next_clen) == NULL) {
                HLOG("Error copying data");
                return 0;
            }
        } else {
            if (memcpy(output + opos, output + opos - back_offset, back_offset) == NULL) {
                HLOG("Error copying data");
                return 0;
            }
            for (size_t i = back_offset; i < next_clen; i++) {
                output[opos + i] = output[opos + i - back_offset];
            }
        }
#ifdef FATBIN_DECOMPRESS_DEBUG
        hexdump(output + opos, next_clen);
#endif
        opos += next_clen;
    }
    HLOG("ipos: %#zx, opos: %#zx, ilen: %#zx, olen: %#zx", ipos, opos, input_size, output_size);
    return opos;
}

static ssize_t decompress_section(const uint8_t *input, uint8_t **output, size_t *output_size,
                                  struct fat_elf_header *eh, struct fat_text_header *th, size_t *eh_out_offset)
{
    struct fat_text_header *th_out = NULL;
    struct fat_elf_header *eh_out = NULL;
    uint8_t *output_pos = 0;
    size_t padding;
    size_t input_read = 0;
    const uint8_t zeroes[6] = {0};

    if (output == NULL || output_size == NULL || eh == NULL || th == NULL || eh_out_offset == NULL) {
        HLOG("invalid parameters");
        return 1;
    }

    if ((*output = (uint8_t *)realloc(*output, *output_size + th->decompressed_size + eh->header_size + th->header_size)) == NULL) {
        HLOG("Error allocating memory of size %#zx for output buffer: %s", 
                *output_size + th->decompressed_size + eh->header_size + th->header_size, strerror(errno));
        goto error;
    }
    output_pos = *output + *output_size;
    *output_size += th->decompressed_size + th->header_size;

    if (input == (uint8_t*)eh + eh->header_size + th->header_size) { // We are at the first section
        if (memcpy(output_pos, eh, eh->header_size) == NULL) {
            HLOG("Error copying data");
            goto error;
        }
        eh_out = ((struct fat_elf_header*)(output_pos));
        eh_out->size = 0;
        *eh_out_offset = output_pos - *output;
        output_pos += eh->header_size;
        *output_size += eh->header_size;
    }
    eh_out = ((struct fat_elf_header*)(*output + *eh_out_offset)); // repair pointer in case realloc moved the buffer
    eh_out->size += th->decompressed_size + th->header_size;       // set size

    if (memcpy(output_pos, th, th->header_size) == NULL) {
        HLOG("Error copying data");
        goto error;
    }
    th_out = ((struct fat_text_header*)output_pos);
    th_out->flags &= ~FATBIN_FLAG_COMPRESS;  // clear compressed flag
    th_out->compressed_size = 0;             // clear compressed size
    th_out->decompressed_size = 0;           // clear decompressed size
    th_out->size = th->decompressed_size;    // set size

    output_pos += th->header_size;

    if (decompress(input, th->compressed_size, output_pos, th->decompressed_size) != th->decompressed_size) {
        HLOG("Decompression failed");
        goto error;
    }

    input_read += th->compressed_size;
    output_pos += th->decompressed_size;

    // if (input_pos != (uint8_t*)th + eh->size) {
    //     printf("There is %#zx bytes of data remaining\n", (uint8_t*)th + eh->size - input_pos);
    // }
    
    padding = (8 - (size_t)(input + input_read) % 8);
    if (memcmp(input + input_read, zeroes, padding) != 0) {
        HLOG("expected %#zx zero bytes, got:", padding);
        hexdump(input + input_read, 0x60);
        goto error;
    }
    input_read += padding;

    padding = ((8 - (size_t)th->decompressed_size) % 8);
    // Because we always allocated enough memory for one more elf_header and this is smaller than
    // the maximal padding of 7, we do not have to reallocate here.
    memset(output_pos, 0, padding);
    *output_size += padding;
    eh_out->size += padding;
    th_out->size += padding;

    return input_read;
 error:
    free(*output);
    *output = NULL;
    return -1;
}

static ssize_t decompress_single_section(const uint8_t *input, uint8_t **output, size_t *output_size,
                                         struct fat_elf_header *eh, struct fat_text_header *th)
{
    size_t padding;
    size_t input_read = 0;
    size_t output_written = 0;
    size_t decompress_ret = 0;
    const uint8_t zeroes[8] = {0};

    if (input == NULL || output == NULL || eh == NULL || th == NULL) {
        HLOG("invalid parameters");
        return 1;
    }

    // add max padding of 7 bytes
    if ((*output = (uint8_t *)malloc(th->decompressed_size + 7)) == NULL) {
        HLOG("Error allocating memory of size %#zx for output buffer: %s", 
                th->decompressed_size, strerror(errno));
        goto error;
    }
    print_header(th);

    if ((decompress_ret = decompress(input, th->compressed_size, *output, th->decompressed_size)) != th->decompressed_size) {
        HLOG("Decompression failed: decompressed size is %#zx, but header says %#zx", 
                decompress_ret, th->decompressed_size);
        HLOG("input pos: %#zx, output pos: %#zx", input - (uint8_t*)eh, *output);
        hexdump(input, 0x160);
        if (decompress_ret >= 0x60)
            hexdump((*output) + decompress_ret - 0x60, 0x60);
        goto error;
    }
    input_read += th->compressed_size;
    output_written += th->decompressed_size;

    padding = ((8 - (size_t)(input + input_read)) % 8);
    if (memcmp(input + input_read, zeroes, padding) != 0) {
        HLOG("expected %#zx zero bytes, got:", padding);
        hexdump(input + input_read, 0x60);
        goto error;
    }
    input_read += padding;

    padding = ((8 - (size_t)th->decompressed_size) % 8);
    // Because we always allocated enough memory for one more elf_header and this is smaller than
    // the maximal padding of 7, we do not have to reallocate here.
    memset(*output, 0, padding);
    output_written += padding;

    *output_size = output_written;
    return input_read;
 error:
    free(*output);
    *output = NULL;
    return -1;
}

/** Decompresses a fatbin file
 * @param fatbin_data Pointer to the fatbin data
 * @param fatbin_size Size of the fatbin data
 * @param decompressed_data Pointer to a variable that will be set to point to the decompressed data
 * @param decompressed_size Pointer to a variable that will be set to the size of the decompressed data
 */
static size_t decompress_fatbin(const uint8_t* fatbin_data, size_t fatbin_size, uint8_t** decompressed_data)
{
    struct fat_elf_header *eh = NULL;
    size_t eh_out_offset = 0;
    struct fat_text_header *th = NULL;
    const uint8_t *input_pos = fatbin_data;

    int i = 0;
    uint8_t *output = NULL;
    size_t output_size = 0;
    ssize_t input_read;

    if (fatbin_data == NULL || decompressed_data == NULL) {
        HLOG("fatbin_data is NULL");
        goto error;
    }

    while (input_pos < fatbin_data + fatbin_size) {
        if (get_elf_header(input_pos, fatbin_size - (input_pos - fatbin_data), &eh) != 0) {
            HLOG("Something went wrong while checking the header.");
            goto error;
        }
        // printf("elf header no. %d: magic: %#x, version: %#x, header_size: %#x, size: %#zx\n",
        //        i++, eh->magic, eh->version, eh->header_size, eh->size);
        input_pos += eh->header_size;
        do {
            if (get_text_header(input_pos, fatbin_size - (input_pos - fatbin_data) - eh->header_size, &th) != 0) {
                HLOG("Something went wrong while checking the header.");
                goto error;
            }
            //print_header(th);
            input_pos += th->header_size;

            if ((input_read = decompress_section(input_pos, &output, &output_size, eh, th, &eh_out_offset)) < 0) {
                HLOG("Something went wrong while decompressing text section.");
                goto error;
            }
            input_pos += input_read;

        } while (input_pos < (uint8_t*)eh + eh->header_size + eh->size);

        //printf("##### Decompressed data (size %#zx): #####\n", th->decompressed_size);
        //hexdump(output_pos, th->decompressed_size);
    }

    *decompressed_data = output;
    return output_size;
 error:
    if (output != NULL) {
        free(output);
    }
    *decompressed_data = NULL;
    return 0;
}

int elf2_get_fatbin_info(const struct fat_header *fatbin, list *kernel_infos, uint8_t** fatbin_mem, size_t* fatbin_size)
{
    struct fat_elf_header* eh;
    struct fat_text_header* th;
    const uint8_t *input_pos = NULL;
    const uint8_t *fatbin_data = NULL;
    uint8_t *text_data = NULL;
    size_t text_data_size = 0;
    size_t fatbin_total_size = 0;
    int ret = -1;
    if (fatbin == NULL || fatbin_mem == NULL || fatbin_size == NULL) {
        HLOG("at least one parameter is NULL");
        goto error;
    }
    fatbin_data = input_pos = (const uint8_t*)fatbin->text;
    if (fatbin->magic != FATBIN_STRUCT_MAGIC) {
        HLOG("fatbin struct magic number is wrong. Got %llx, expected %llx.", fatbin->magic, FATBIN_STRUCT_MAGIC);
        goto error;
    }
    HLOG( "Fatbin: magic: %x, version: %x, text: %lx, data: %lx, ptr: %lx, ptr2: %lx, zero: %lx",
           fatbin->magic, fatbin->version, fatbin->text, fatbin->data, fatbin->unknown, fatbin->text2, fatbin->zero);

    if (get_elf_header((uint8_t*)fatbin->text, sizeof(struct fat_elf_header), &eh) != 0) {
        HLOG("Something went wrong while checking the header.");
        hexdump((uint8_t*)fatbin->text, 100);
        goto error;
    }
    // HLOG( "elf header: magic: %#x, version: %#x, header_size: %#x, size: %#zx",
    //        eh->magic, eh->version, eh->header_size, eh->size); 

    input_pos += eh->header_size;
    fatbin_total_size = eh->header_size + eh->size;
    do {
        if (get_text_header(input_pos, *fatbin_size - (input_pos - fatbin_data) - eh->header_size, &th) != 0) {
            HLOG("Something went wrong while checking the header.");
            goto error;
        }
        //print_header(th);
        input_pos += th->header_size;
        if (th->kind != 2) { // section does not cotain device code (but e.g. PTX)
            input_pos += th->size;
            continue;
        }
        if (th->flags & FATBIN_FLAG_DEBUG) {
            HLOG("fatbin contains debug information.");
        }

        if (th->flags & FATBIN_FLAG_COMPRESS) {
            ssize_t input_read;

            HLOG("fatbin contains compressed device code. Decompressing...");
            if ((input_read = decompress_single_section(input_pos, &text_data, &text_data_size, eh, th)) < 0) {
                HLOG("Something went wrong while decompressing text section.");
                goto error;
            }
            input_pos += input_read;
            //hexdump(text_data, text_data_size);
        } else {
            text_data = (uint8_t*)input_pos;
            text_data_size = th->size;
            input_pos += th->size;
        }
        // print_header(th);
        if (elf2_parameter_info(kernel_infos, text_data , text_data_size) != 0) {
            HLOG("error getting parameter info");
            goto error;
        }
        if (th->flags & FATBIN_FLAG_COMPRESS) {
            free(text_data);
        }
    } while (input_pos < (uint8_t*)eh + eh->header_size + eh->size);

    // if (get_elf_header((uint8_t*)fatbin->text2, sizeof(struct fat_elf_header), &eh) != 0) {
    //     HLOG("Something went wrong while checking the header.");
    //     goto error;
    // }
    // fatbin_total_size += eh->header_size + eh->size;

    *fatbin_mem = (uint8_t *)fatbin->text;
    *fatbin_size = fatbin_total_size;
    ret = 0;
 error:
    return ret;
}

static void print_hexmem(void *mem, size_t len)
{
    for (int i=0; i<len; i++) {
        printf("%02x ", ((uint8_t*)mem)[i]);
    }
    printf("\n");
}

#define EIATTR_PARAM_CBANK              0xa
#define EIATTR_EXTERNS                  0xf
#define EIATTR_FRAME_SIZE               0x11
#define EIATTR_MIN_STACK_SIZE           0x12
#define EIATTR_KPARAM_INFO              0x17
#define EIATTR_CBANK_PARAM_SIZE         0x19
#define EIATTR_MAX_REG_COUNT            0x1b
#define EIATTR_EXIT_INSTR_OFFSETS       0x1c
#define EIATTR_S2RCTAID_INSTR_OFFSETS   0x1d
#define EIATTR_CRS_STACK_SIZE           0x1e
#define EIATTR_SW1850030_WAR            0x2a
#define EIATTR_REGCOUNT                 0x2f
#define EIATTR_SW2393858_WAR            0x30
#define EIATTR_INDIRECT_BRANCH_TARGETS  0x34
#define EIATTR_CUDA_API_VERSION         0x37

#define EIFMT_NVAL                      0x1
#define EIFMT_HVAL                      0x3
#define EIFMT_SVAL                      0x4


static int get_section_by_name(Elf *elf, const char *name, Elf_Scn **section)
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    char *section_name = NULL;
    size_t str_section_index;

    if (elf == NULL || name == NULL || section == NULL) {
        HLOG("invalid argument");
        return -1;
    }

    if (elf_getshdrstrndx(elf, &str_section_index) != 0) {
        HLOG("elf_getshstrndx failed");
        return -1;
    }

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            HLOG("gelf_getshdr failed");
            return -1;
        }
        if ((section_name = elf_strptr(elf, str_section_index, shdr.sh_name)) == NULL) {
            HLOG("elf_strptr failed");
            return -1;
        }
        if (strcmp(section_name, name) == 0) {
            *section = scn;
            return 0;
        }
    }
    return -1;
}

static int print_sections(Elf *elf)
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    char *section_name = NULL;
    size_t str_section_index;

    if (elf == NULL) {
        HLOG("invalid argument");
        return -1;
    }

    if (elf_getshdrstrndx(elf, &str_section_index) != 0) {
        HLOG("elf_getshstrndx Wfailed");
        return -1;
    }

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            HLOG("gelf_getshdr failed");
            return -1;
        }
        if ((section_name = elf_strptr(elf, str_section_index, shdr.sh_name)) == NULL) {
            HLOG("elf_strptr failed");
            return -1;
        }
    }
    return -1;
}

static char* get_kernel_section_from_kernel_name(const char *kernel_name)
{
    char *section_name = NULL;
    if (kernel_name == NULL) {
        HLOG("invalid argument");
        return NULL;
    }

    if (kernel_name[0] == '$') {
        const char *p;
        if ((p = strchr(kernel_name+1, '$')) == NULL) {
            HLOG("invalid kernel name");
            return NULL;
        }
        int len = (p - kernel_name) - 1;
        if (asprintf(&section_name, ".nv.info.%.*s", len, kernel_name+1) == -1) {
            HLOG("asprintf failed");
            return NULL;
        }
    } else {
        if (asprintf(&section_name, ".nv.info.%s", kernel_name) == -1) {
            HLOG("asprintf failed");
            return NULL;
        }
    }
    return section_name;
}

static int get_parm_for_kernel(Elf *elf, kernel_info_t *kernel, void* memory, size_t memsize)
{
    struct __attribute__((__packed__)) nv_info_kernel_entry {
        uint8_t format;
        uint8_t attribute;
        uint16_t values_size;
        uint32_t values;
    };
    struct __attribute__((__packed__)) nv_info_kparam_info {
        uint32_t index;
        uint16_t ordinal;
        uint16_t offset;
        uint16_t unknown : 12;
        uint8_t  cbank : 6;
        uint16_t size : 14;
        // missing are "space" (possible padding info?), and "Pointee's logAlignment"
        // these were always 0 in the kernels I tested
    };
    int ret = -1;
    char *section_name = NULL;
    Elf_Scn *section = NULL;
    Elf_Data *data = NULL;
    size_t secpos=0;
    int i=0;

    if (kernel == NULL || kernel->name == NULL || memory == NULL) {
        HLOG("at least one parameter is NULL");
        goto cleanup;
    }
    kernel->param_num = 0;
    kernel->param_size = 0;
    kernel->param_offsets = NULL;
    kernel->param_sizes = NULL;

    if ((section_name = get_kernel_section_from_kernel_name(kernel->name)) == NULL) {
        HLOG("get_kernel_section_from_kernel_name failed");
        goto cleanup;
    }

    if (get_section_by_name(elf, section_name, &section) != 0) {
        HLOG("section %s not found", section_name);
        goto cleanup;
    }

    if ((data = elf_getdata(section, NULL)) == NULL) {
        HLOG("error getting section data");
        goto cleanup;
    }

    //print_hexmem(data->d_buf, data->d_size);

    while (secpos < data->d_size) {
        struct nv_info_kernel_entry *entry = (struct nv_info_kernel_entry*)(data->d_buf+secpos);
        // printf("entry %d: format: %#x, attr: %#x, ", i++, entry->format, entry->attribute);
        if (entry->format == EIFMT_SVAL && entry->attribute == EIATTR_KPARAM_INFO) {
            if (entry->values_size != 0xc) {
                HLOG("EIATTR_KPARAM_INFO values size has not the expected value of 0xc");
                goto cleanup;
            }
            struct nv_info_kparam_info *kparam = (struct nv_info_kparam_info*)&entry->values;
            // printf("kparam: index: %#x, ordinal: %#x, offset: %#x, unknown: %#0x, cbank: %#0x, size: %#0x\n",
            //     kparam->index, kparam->ordinal, kparam->offset, kparam->unknown, kparam->cbank, kparam->size);
            HLOG( "param %d: offset: %#x, size: %#x", kparam->ordinal, kparam->offset, kparam->size);
            if (kparam->ordinal >= kernel->param_num) {
                kernel->param_offsets = (uint16_t *)realloc(kernel->param_offsets,
                                              (kparam->ordinal+1)*sizeof(uint16_t));
                kernel->param_sizes = (uint16_t *)realloc(kernel->param_sizes,
                                            (kparam->ordinal+1)*sizeof(uint16_t));
                kernel->param_num = kparam->ordinal+1;
            }
            kernel->param_offsets[kparam->ordinal] = kparam->offset;
            kernel->param_sizes[kparam->ordinal] = kparam->size;
            secpos += sizeof(struct nv_info_kernel_entry) + entry->values_size-4;
        } else if (entry->format == EIFMT_HVAL && entry->attribute == EIATTR_CBANK_PARAM_SIZE) {
            kernel->param_size = entry->values_size;
            HLOG("cbank_param_size: %#0x", entry->values_size);
            secpos += sizeof(struct nv_info_kernel_entry)-4;
        } else if (entry->format == EIFMT_HVAL) {
            // printf("hval: %#x(%d)\n", entry->values_size, entry->values_size);
            secpos += sizeof(struct nv_info_kernel_entry)-4;
        } else if (entry->format == EIFMT_SVAL) {
            // printf("sval_size: %#x ", entry->values_size);
            // for (int j=0; j*sizeof(uint32_t) < entry->values_size; j++) {
            //     printf("val%d: %#x(%d) ", j, (&entry->values)[j], (&entry->values)[j]);
            // }
            // printf("\n");
            secpos += sizeof(struct nv_info_kernel_entry) + entry->values_size-4;
        } else if (entry->format == EIFMT_NVAL) {
            // printf("nval\n");
            secpos += sizeof(struct nv_info_kernel_entry)-4;
        } else {
            HLOG("unknown format: %#x", entry->format);
            secpos += sizeof(struct nv_info_kernel_entry)-4;
        }
    }
    // printf("remaining: %d\n", data->d_size % sizeof(struct nv_info_kernel_entry));
    ret = 0;
 cleanup:
    free(section_name);
    return ret;
}

static int get_symtab(Elf *elf, Elf_Data **symbol_table_data, size_t *symbol_table_size, GElf_Shdr *symbol_table_shdr)
{
    GElf_Shdr shdr;
    Elf_Scn *section = NULL;

    if (elf == NULL || symbol_table_data == NULL || symbol_table_size == NULL) {
        HLOG("invalid argument");
        return -1;
    }

    if (get_section_by_name(elf, ".symtab", &section) != 0) {
        HLOG("could not find .symtab section");
        return -1;
    }

    if (gelf_getshdr(section, &shdr) == NULL) {
        HLOG("gelf_getshdr failed");
        return -1;
    }

    if (symbol_table_shdr != NULL) {
        *symbol_table_shdr = shdr;
    }

    if(shdr.sh_type != SHT_SYMTAB) {
        HLOG("not a symbol table: %d", shdr.sh_type);
        return -1;
    }

    if ((*symbol_table_data = elf_getdata(section, NULL)) == NULL) {
        HLOG("elf_getdata failed");
        return -1;
    }

    *symbol_table_size = shdr.sh_size / shdr.sh_entsize;

    return 0;
}

static void print_symtab(Elf *elf)
{
    GElf_Sym sym;
    Elf_Data *symbol_table_data = NULL;
    GElf_Shdr shdr;
    size_t symnum;
    int i = 0;

    if (get_symtab(elf, &symbol_table_data, &symnum, &shdr) != 0) {
        HLOG("could not get symbol table");
        return;
    }

    HLOG("found %d symbols", symnum);

    while (gelf_getsym(symbol_table_data, i, &sym) != NULL) {
        printf("sym %d: name: %s, value: %#lx, size: %#lx, info: %#x, other: %#x, shndx: %#x\n", i,
               elf_strptr(elf, shdr.sh_link, sym.st_name),
               sym.st_value, sym.st_size, sym.st_info, sym.st_other, sym.st_shndx);
        i++;
    }
}

static int check_elf(Elf *elf)
{
    Elf_Kind ek;
    GElf_Ehdr ehdr;

    int elfclass;
    char *id;
    size_t program_header_num;
    size_t sections_num;
    size_t section_str_num;
    int ret = -1;

    if ((ek = elf_kind(elf)) != ELF_K_ELF) {
        HLOG("elf_kind is not ELF_K_ELF, but %d", ek);
        goto cleanup;
    }

    if (gelf_getehdr(elf, &ehdr) == NULL) {
        HLOG("gelf_getehdr failed");
        goto cleanup;
    }

    if ((elfclass = gelf_getclass(elf)) == ELFCLASSNONE) {
        HLOG("gelf_getclass failed");
        goto cleanup;
    }

    if ((id = elf_getident(elf, NULL)) == NULL) {
        HLOG("elf_getident failed");
        goto cleanup;
    }

    HLOG( "elfclass: %d-bit; elf ident[0..%d]: %7s",
        (elfclass == ELFCLASS32) ? 32 : 64,
        EI_ABIVERSION, id);

    if (elf_getshdrnum(elf, &sections_num) != 0) {
        HLOG("elf_getphdrnum failed");
        goto cleanup;
    }

    if (elf_getphdrnum(elf, &program_header_num) != 0) {
        HLOG("elf_getshdrnum failed");
        goto cleanup;
    }

    if (elf_getshdrstrndx(elf, &section_str_num) != 0) {
        HLOG("elf_getshstrndx Wfailed");
        goto cleanup;
    }

    HLOG( "elf contains %d sections, %d program_headers, string table section: %d",
        sections_num, program_header_num, section_str_num);

    ret = 0;
cleanup:
    return ret;
}

int elf2_parameter_info(list *kernel_infos, void* memory, size_t memsize)
{
    struct __attribute__((__packed__)) nv_info_entry{
        uint8_t format;
        uint8_t attribute;
        uint16_t values_size;
        uint32_t kernel_id;
        uint32_t value;
    };

    Elf *elf = NULL;
    Elf_Scn *section = NULL;
    Elf_Data *data = NULL, *symbol_table_data = NULL;
    GElf_Shdr symtab_shdr;
    size_t symnum;
    int i = 0;
    GElf_Sym sym;

    int ret = -1;
    kernel_info_t *ki = NULL;
    const char *kernel_str;

    if (memory == NULL || memsize == 0) {
        HLOG("memory was NULL or memsize was 0");
        return -1;
    }

#define ELF_DUMP_TO_FILE 1

#ifdef ELF_DUMP_TO_FILE
    FILE* fd2 = fopen("/tmp/cricket-elf-dump", "wb");
    fwrite(memory, memsize, 1, fd2);
    fclose(fd2);
#endif

    if ((elf = elf_memory((char *)memory, memsize)) == NULL) {
        HLOG("elf_memory failed");
        goto cleanup;
    }

    if (check_elf(elf) != 0) {
        HLOG("check_elf failed");
        goto cleanup;
    }

    if (get_symtab(elf, &symbol_table_data, &symnum, &symtab_shdr) != 0) {
        HLOG("could not get symbol table");
        goto cleanup;
    }

    if (get_section_by_name(elf, ".nv.info", &section) != 0) {
        HLOG("could not find .nv.info section. This means this binary does not contain any kernels.");
        ret = 0;    // This is not an error.
        goto cleanup;
    }

    if ((data = elf_getdata(section, NULL)) == NULL) {
        HLOG("elf_getdata failed");
        goto cleanup;
    }

    for (size_t secpos=0; secpos < data->d_size; secpos += sizeof(struct nv_info_entry)) {
        struct nv_info_entry *entry = (struct nv_info_entry *)(data->d_buf+secpos);
        // HLOG( "%d: format: %#x, attr: %#x, values_size: %#x kernel: %#x, sval: %#x(%d)", 
        // i++, entry->format, entry->attribute, entry->values_size, entry->kernel_id, 
        // entry->value, entry->value);

        if (entry->values_size != 8) {
            HLOG("unexpected values_size: %#x", entry->values_size);
            continue;
        }

        if (entry->attribute != EIATTR_FRAME_SIZE) {
            continue;
        }

        if (entry->kernel_id >= symnum) {
            HLOG("kernel_id out of bounds: %#x", entry->kernel_id);
            continue;
        }

        if (gelf_getsym(symbol_table_data, entry->kernel_id, &sym) == NULL) {
            HLOG("gelf_getsym failed for entry %d", entry->kernel_id);
            continue;
        }

        if ((kernel_str = elf_strptr(elf, symtab_shdr.sh_link, sym.st_name) ) == NULL) {
            HLOG("strptr failed for entry %d", entry->kernel_id);
            continue;
        }

        /* When using (some?) intrinsics, nvcc adds symbols for them in the .nv.info table.
        * They are prefixed with $__internal_7_$ and are not kernels. We skip them he
        */
        const char *intrinsics_prefix = "$__internal_";
        if (strncmp(kernel_str, intrinsics_prefix, strlen(intrinsics_prefix)) == 0) {
            continue;
        }

        if (utils_search_info(kernel_infos, kernel_str) != NULL) {
            continue;
        }

        HLOG("found new kernel: %s (symbol table id: %#x)", kernel_str, entry->kernel_id);

        if (list_append(kernel_infos, (void**)&ki) != 0) {
            HLOG("error on appending to list");
            goto cleanup;
        }

        size_t buflen = strlen(kernel_str)+1;
        if ((ki->name = (char *)malloc(buflen)) == NULL) {
            HLOG("malloc failed");
            goto cleanup;
        }
        if (strncpy(ki->name, kernel_str, buflen) != ki->name) {
            HLOG("strncpy failed");
            goto cleanup;
        }

        if (get_parm_for_kernel(elf, ki, memory, memsize) != 0) {
            HLOG("get_parm_for_kernel failed for kernel %s", kernel_str);
            goto cleanup;
        }
    }

    ret = 0;
 cleanup:
    if (elf != NULL) {
        elf_end(elf);
    }
    return ret;
}

void* elf2_symbol_address(const char *symbol)
{
    return dlsym(RTLD_DEFAULT, symbol);
}