#include "cuda_subset.h"



// Function pointer to the real cuGetProcAddress
#if(CUDA_VERSION < 12000)
typedef CUresult (*cuGetProcAddress_t)(
    const char *, void **, unsigned int, cuuint64_t);
#else
typedef CUresult (*cuGetProcAddress_t)(
    const char *, void **, int, cuuint64_t, CUdriverProcAddressQueryResult *);
#endif

CUresult cuGetProcAddress(const char * symbol, void * * pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus);
