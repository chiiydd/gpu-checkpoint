#ifndef FAT_BINARY_H
#define FAT_BINARY_H
#include <cstdint>
#include <stdint.h>
#include <unistd.h>
#include <list>
extern "C" {
  /*
  * These defines are for the fatbin.c runtime wrapper
  */
  #define FATBINC_MAGIC   0x466243B1
  #define FATBINC_VERSION 1
  #define FATBINC_LINK_VERSION 2

  typedef struct {
    int magic;
    int version;
    const unsigned long long* data;
    void *filename_or_fatbins;  /* version 1: offline filename,
                                * version 2: array of prelinked fatbins */
  }FatBinaryWrapper;
}
struct  alignas(8) FatBinaryHeader     
{
    uint32_t 			magic;
    uint16_t         	version;
    uint16_t         	headerSize;
    uint64_t 	fatSize;
};


struct  alignas(8) FatEntryHeader
{
    uint16_t kind; 
    uint16_t unknown1;
    uint32_t headerSize;
    uint64_t size;
    uint32_t compressedSize;       // Size of compressed data
    uint32_t unknown2;              // Address size for PTX?
    uint16_t minor;
    uint16_t major;
    uint32_t arch;
    uint32_t objNameOffset;
    uint32_t objNameLen;
    uint64_t flags;
    uint64_t zero;                  // Alignment for compression?
    uint64_t decompressedSize;     // Length of compressed data in decompressed representation.
                                    // There is an uncompressed footer so this is generally smaller
                                    // than size.
};
struct KernelInfo {
    char *name;
    size_t param_size;
    size_t param_num;
    uint16_t *param_offsets;
    uint16_t *param_sizes;
    void *host_fun;
};


void readFatbinaryEntryHeader(void *fatbin) ;
void printHex(const void *data, unsigned int size) ;
#endif //FAT_BINARY_H









