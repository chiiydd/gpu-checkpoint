#include "cuda.h"



// Function pointer to the real cuGetProcAddress
#if(CUDA_VERSION < 12000)
using cuGetProcAddress_t = CUresult (*)(const char *, void **, unsigned int, cuuint64_t);
#else
using cuGetProcAddress_t = CUresult (*)(const char *, void **, int, cuuint64_t, CUdriverProcAddressQueryResult *);
#endif

CUresult cuGetProcAddress(const char * symbol, void * * pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus);
