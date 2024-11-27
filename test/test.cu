#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cuda_runtime.h>
#include <cuda.h>
#include <iostream>

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
__global__ void add(int *dev_a, int *dev_b, int *dev_c) {
    dev_c[threadIdx.x] = dev_a[threadIdx.x] + dev_b[threadIdx.x];
}

void cudart_call(){
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {10, 20, 30, 40, 50};
    int c[5] = {0, 0, 0, 0, 0};

    int *dev_a, *dev_b, *dev_c;
    cudaMalloc((void**)&dev_a, 5 * sizeof(int));
    cudaMalloc((void**)&dev_b, 5 * sizeof(int));
    cudaMalloc((void**)&dev_c, 5 * sizeof(int));

    cudaMemcpy(dev_a, a, 5 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, 5 * sizeof(int), cudaMemcpyHostToDevice);

    add<<<1, 5>>>(dev_a, dev_b, dev_c);

    cudaMemcpy(c, dev_c, 5 * sizeof(int), cudaMemcpyDeviceToHost);

    for(int i = 0; i < 5; i++){
        std::cout << c[i] << std::endl;
    }

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

}

void print_cuda_error(CUresult result){
    const char * error_string;
    cuGetErrorString(result, &error_string);
    std::cout<<"CUDA Error: "<<error_string<<std::endl;
}

void * read_file(const char * filename, size_t * size){
    FILE * file = fopen(filename, "rb");
    if(!file){
        return NULL;
    }
    
    void * buffer;
    int result;
    result=fseek(file, 0, SEEK_END);
    if(result == -1){
        std::cout<<"Error in fseek"<<std::endl;
        fclose(file);
        return NULL;
    }
    long file_size = ftell(file);
    if(file_size == -1){
        std::cout<<"Error in ftell"<<std::endl;
        fclose(file);
        return NULL;
    }
    *size = file_size;
    
    buffer=malloc(file_size);
    rewind(file); // 将文件指针重置到文件开头


    result = fread(buffer, 1, file_size, file);
    if(result != file_size){
        std::cout<<"Error in fread"<<std::endl;
        fclose(file);
        free(buffer);
        return NULL;
    }
    fclose(file);

    
    // hexdump((uint8_t *)buffer, file_size);
    return buffer;
}
void cuda_call(){
    int a[5] ={1,2,3,4,5};
    int b[5] ={10,20,30,40,50};
    int c[5] ={0,0,0,0,0};
    
    CUdevice cuDevice;
    CUcontext cuContext;
    CUmoduleLoadingMode mode;
    CUresult result;
    CUlibrary library;
    CUmodule mod;
    CUfunction func;

    cuInit(0);
    cuDeviceGet(&cuDevice, 0);
    std::cout<<"Device: "<<cuDevice<<std::endl;

    char * gpu_name = new char[100];
    cuDeviceGetName(gpu_name, 100, cuDevice);
    std::cout<<"GPU Name: "<<gpu_name<<std::endl;


    result=cuModuleGetLoadingMode(&mode);
    if (result!=CUDA_SUCCESS){
        std::cout<<"[cuModuleGetLoadingMode] fails\n";
        print_cuda_error(result);
        return;
    }

    std::cout<<"[cuModuleGetLoadingMode] get mod:"<<mode<<std::endl;
    cuCtxCreate(&cuContext, 0, cuDevice);
    std::cout<<"[cuCtxCreate] Context Create: "<<cuContext<<std::endl;

    CUcontext ctx;
    cuCtxGetCurrent(&ctx);
    std::cout<<"[cuCtxGetCurrent] Current Context: "<<ctx<<std::endl;

    cuCtxSetCurrent(cuContext);

    cuDevicePrimaryCtxRetain(&ctx, cuDevice);

    std::cout<<"[cuDevicePrimaryCtxRetain] Primary Context: "<<ctx<<std::endl;
    CUdevice dev;
    cuCtxGetDevice(&dev);
    std::cout<<"[cuCtxGetDevice] Current Context Device: "<<dev<<std::endl;

    int *dev_a, *dev_b, *dev_c;
    cuMemAlloc_v2((CUdeviceptr*)&dev_a, 5 * sizeof(int));
    cuMemAlloc_v2((CUdeviceptr*)&dev_b, 5 * sizeof(int));
    cuMemAlloc_v2((CUdeviceptr*)&dev_c, 5 * sizeof(int));

    cuMemcpyHtoD_v2((CUdeviceptr)dev_a, a, 5 * sizeof(int));
    cuMemcpyHtoD_v2((CUdeviceptr)dev_b, b, 5 * sizeof(int));



    void * fatbin;
    size_t size;
    fatbin=read_file("/workspace/test.fatbin", &size);
    if(fatbin == NULL){
        std::cout<<"Error in read  fatbinary file"<<std::endl;
        return;
    }

    std::cout<<"Fatbin address: "<<&fatbin<<std::endl;
    FatBinaryHeader *header = (FatBinaryHeader*)fatbin;
    
    //打印fatbin头部信息
    std::cout<<"Magic: "<<std::hex<<header->magic<<std::endl;

    //取消十六进制输出
    std::cout<<std::dec;

    std::cout<<"Version: "<<header->version<<std::endl;
    std::cout<<"Header Size: "<<header->headerSize<<std::endl;
    std::cout<<"Fat Size: "<<header->fatSize<<std::endl;


	FatEntryHeader * fatbinEntry=(FatEntryHeader *) ((char *)fatbin+header->headerSize);
	
    //打印fatbinEntry头部信息
    std::cout<<"Kind: "<<fatbinEntry->kind<<std::endl;
    std::cout<<"Unknown1: "<<fatbinEntry->unknown1<<std::endl;
    std::cout<<"Header Size: "<<fatbinEntry->headerSize<<std::endl;
    std::cout<<"Size: "<<fatbinEntry->size<<std::endl;
    std::cout<<"Compressed Size: "<<fatbinEntry->compressedSize<<std::endl;
    std::cout<<"Unknown2: "<<fatbinEntry->unknown2<<std::endl;
    std::cout<<"Minor: "<<fatbinEntry->minor<<std::endl;
    std::cout<<"Major: "<<fatbinEntry->major<<std::endl;
    std::cout<<"Arch: "<<fatbinEntry->arch<<std::endl;

    FatBinaryWrapper wrapper ={FATBINC_MAGIC, FATBINC_LINK_VERSION, (const unsigned long long*)fatbin, NULL};

    CUlibraryOption option[]={
        CU_LIBRARY_BINARY_IS_PRESERVED
    };
    
    int values []={1};
    result= cuLibraryLoadData(&library, &wrapper, nullptr , nullptr, 0, option,(void **)&values ,1);

    std::cout<<"[cuLibraryLoadData] get lib:"<<library<<std::endl;
    if(result != CUDA_SUCCESS){

        std::cout<<"Error in cuLibraryLoadData"<<std::endl;
        print_cuda_error(result);
        return;
    }
    cuCtxGetCurrent(&ctx);
    std::cout<<"[cuCtxPushCurrent] Current Context: "<<ctx<<std::endl;

    result=cuCtxPushCurrent(ctx);


    if(result != CUDA_SUCCESS){

        std::cout<<"Error in cuCtxPushCurrent"<<std::endl;
        print_cuda_error(result);
        return;
    }
    
    cuCtxGetCurrent(&ctx);
    std::cout<<"[cuCtxPushCurrent] Current Context: "<<ctx<<std::endl;


    result =cuLibraryGetModule(&mod, library);
    if(result != CUDA_SUCCESS){

        std::cout<<"Error in cuLibraryGetModule:"<<result<<std::endl;
        print_cuda_error(result);

        return;
    }

    result =cuCtxPopCurrent_v2(&ctx);
    result = cuModuleGetFunction(&func, mod, "_Z3addPiS_S_");
    if(result != CUDA_SUCCESS){
        std::cout<<"Error in cuModuleGetFunction"<<std::endl;
        print_cuda_error(result);

        return;
    }

    void *args[] = {&dev_a, &dev_b, &dev_c};
    result = cuLaunchKernel(func, 1, 1, 1, 5, 1, 1, 0, 0, args, 0);
    if(result != CUDA_SUCCESS){
        std::cout<<"Error in cuLaunchKernel"<<std::endl;
        return;
    }
    
    cuMemcpyDtoH_v2(c, (CUdeviceptr)dev_c, 5 * sizeof(int));

    for(int i = 0; i < 5; i++){
        std::cout << c[i] << std::endl;
    }
    cuMemFree_v2((CUdeviceptr)dev_a);
    cuMemFree_v2((CUdeviceptr)dev_b);
    cuMemFree_v2((CUdeviceptr)dev_c);
}
int main(){
    // int device_count;
    // cudaGetDeviceCount(&device_count);
    // for (int i = 0; i < device_count; i++) {
    //     cudaDeviceProp prop;
    //     cudaGetDeviceProperties(&prop, i);

    //     printf("Device %d: %s\n", i, prop.name);
    //     printf("  Compute Capability: %d.%d\n", prop.major, prop.minor);
    // }
    cuda_call();

    // cudart_call();
    return 0;
}