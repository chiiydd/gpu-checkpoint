#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <cstddef>
#include <cstdint>
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
    CuCtxPopCurrent,
    CuInit,
    CuCtxCreate,
    CuLibraryGetModule,
    CuModuleGetFunction,
    CuLaunchKernel,
    hidden_get_device_ctx,
    Hidden_1_1,
    Hidden_1_5,
    hidden_3_0,
    hidden_3_1,
    hidden_3_2,
    hidden_4_1,
    hidden_4_2,
    hidden_5_0,
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
            size_t bytesize;
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
            CUdevice dev;
        }cuDeviceTotalMem;
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

        }cuCtxPopCurrent;
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

        struct{
            CUdevice dev;
        }hiddenGetDeviceCtx;

        struct{
            uint32_t dev;
        }hidden_get_device_ctx;
        struct{
            int64_t arg1;
            uint64_t arg2;
            uint64_t *arg3;
            uint64_t arg4;
        }hidden_3_0;

        struct{
            void * arg1;
            void * arg2;
        }hidden_3_1;

        struct{
            void *arg1;
            uint64_t arg2;
            void * arg3;
        }hidden_3_2;
        struct{
            int64_t arg1; //CUctx
        }hidden_4_1;
        struct{
            uint32_t arg1;
            uint64_t arg2;
            uint64_t * arg3;
        }hidden_5_0;

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
            struct{
                uint64_t arg1;
                uint64_t arg2;
            }hidden_1_1;
            struct{
                uint64_t arg1;
                uint64_t arg2;
            }hidden_1_5;

            struct{
                uint64_t arg2;
            }hidden_3_1;
            struct{
                int arg2;
                int64_t arg3;
            }hidden_4_1;
        }returnParams;
};

#endif