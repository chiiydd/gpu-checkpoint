#ifndef  MEMORY_MANAGE_H
#define  MEMORY_MANAGE_H
#include "communication.h"
#include "cuda_original.h"

CUresult  hookedCuMemAlloc(CUdeviceptr *dptr, size_t size);
#endif 