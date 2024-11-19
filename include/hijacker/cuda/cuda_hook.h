#ifndef __CUDA_CUDA_HOOK_H__
#define __CUDA_CUDA_HOOK_H__
#include <string>
#include "cuda_original.h"


class CuDriverFunction{
    public:
        std::string symbol;
        int cudaVersion;
        cuuint64_t flags;
        void *funcPtr;
    CuDriverFunction() : symbol("DEFAULT"),cudaVersion(0), flags(0), funcPtr(nullptr) {} // 默认构造函数
    CuDriverFunction(const char * symbol,int cudaVersion, cuuint64_t flags, void *funcPtr):symbol(symbol),cudaVersion(cudaVersion),flags(flags),funcPtr(funcPtr){}

};
// Function pointer to the real cuGetProcAddress
// #if(CUDA_VERSION < 12000)
// using cuGetProcAddress_t = CUresult (*)(const char *, void **, unsigned int, cuuint64_t);
// #else
using cuGetProcAddress_t = CUresult (*)(const char *, void **, int, cuuint64_t, CUdriverProcAddressQueryResult *);
// #endif

CUresult cuGetProcAddress_v2(const char * symbol, void * * pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus);

extern cuGetProcAddress_t realCuGetProcAddress;
// cuGetProcAddress_t cuGetProcAddress;





#endif
