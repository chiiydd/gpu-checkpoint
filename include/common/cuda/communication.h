#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <cstddef>
#include "cuda_subset.h"
#include "fatbinary.h"
enum class CuDriverCall{
    CuMemAlloc,
    CuMemFree,
    CuMemcpyHtoD,
    CuMemcpyDtoH,
    CuDriverGetVersion,
    CuDeviceGet,
    CuDeviceGetCount,
    CuDeviceGetName,
    CuDeviceGetUuid,
    CuDeviceTotalMem,
    CuGetExportTable,
    CuModuleGetLoadingMode,
    CuDeviceGetAttribute,
    CuCtxGetCurrent,
    CuCtxSetCurrent,
    CuDevicePrimaryCtxRetain,
    CuLibraryLoadData,
    CuLibraryUnload,
    CuDevicePrimaryCtxRelease,
    CuCtxPushCurrent,
    CuInit,
    CuCtxCreate,
    CuLibraryGetModule,
    CuModuleGetFunction,
    CuLaunchKernel,
    
    
};


struct CuDriverCallStructure {
    CuDriverCall op;

    union{
        struct{

        }empty;
        struct{
            unsigned int flags;
        }cuInit;
        struct{
            size_t size;
        }cuMemAlloc;

        struct{
            CUdeviceptr dptr;
        }cuMemFree;
        struct{
            CUdeviceptr dstDevice;
            const void * srcHost;
            size_t ByteCount;
        }cuMemcpyHtoD;
        struct{
            void * dstHost;
            CUdeviceptr srcDevice;
            size_t ByteCount;
        }cuMemcpyDtoH;


        struct{
            int ordinal;
        }cuDeviceGet;
        struct{
            char * name;
            int len;
            CUdevice device;
        }cuDeviceGetName;

        struct {
            CUdevice dev;
        }cuDeviceGetUuid;
        struct {
            const void * * ppExportTable;
            const CUuuid * pExportTableId;
        }cuGetExportTable;
        struct {
            CUmoduleLoadingMode * mode;
        }cuModuleGetLoadingMode;
        struct {
            CUdevice dev;
        }cuDeviceTotalMem;
        struct{
            CUdevice_attribute attrib;
            CUdevice dev;
        }cuDeviceGetAttribute;
        struct{

        }cuCtxGetCurrent;
        struct{
            CUcontext ctx;
        }cuCtxSetCurrent;
        struct{
            unsigned int flags;
            CUdevice dev;
        }cuCtxCreate;
        struct{
            CUdevice dev;
        }cuDevicePrimaryCtxRetain;
        struct{

        }cuCtxGetDevice;
        struct{
            CUcontext ctx;
        }cuCtxPushCurrent;
        struct{
            CUlibrary library;
        }cuLibraryUnload;
        struct{
            CUdevice dev;
        }cuDevicePrimaryCtxRelease;
        struct{
            FatBinaryWrapper wrapper;
            unsigned long fatbinSize;
            unsigned int numJitOptions;
            unsigned int numLibraryOptions;
        }cuLibraryLoadData;
        struct{
            CUlibrary library;
        }cuLibraryGetModule;

        struct{
            CUmodule mod;
            const char * name;
            unsigned long nameLength;
        }cuModuleGetFunction;

        struct{
                CUfunction f;
                unsigned int gridDimX;
                unsigned int gridDimY;
                unsigned int gridDimZ;
                unsigned int blockDimX;
                unsigned int blockDimY;
                unsigned int blockDimZ;
                unsigned int sharedMemBytes;
                CUstream hStream;
                size_t parametersMetadataLen;
        }cuLaunchKernel;
    }params;
};


struct CuDriverCallReplyStructure{
        CuDriverCall op;
        CUresult  result;


        union{
            struct{}empty;
            int driverVersion;  //cuGetDriverVersion
            CUmoduleLoadingMode mode; //cuModuleGetLoadingMode
            int count;
            CUdevice device;
            CUdeviceptr dptr;
            int pi;
            CUfunction hfunc; //cuModuleGetFunction
            CUcontext ctx;
            CUmodule mod;
            CUlibrary lib;

            size_t  bytes;
            char uuid[16];
        }returnParams;
};

#endif