#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <cstddef>
#include "cuda_subset.h"
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
    cuLibraryLoadData,
    cuLibraryUnload,
    cuDevicePrimaryCtxRelease,
    cuCtxPushCurrent,
    CuInit,
    cuDriverGetVersion,
};


struct CuDriverCallStructure {
    CuDriverCall op;

    union{
        struct{

        }empty;
        struct{
            CUdeviceptr *dptr;
            size_t size;
        }cuMemAlloc;

        struct{
            CUdeviceptr dptr;
        }cuMemFree;
        struct{
            CUdeviceptr dstDevice;
            const void *srcHost;
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
            int len;
            CUdevice device;
        }cuDeviceGetName;
        struct {
            CUdevice device;
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
            CUcontext * ptx;
            CUdevice dev;
        }cuDevicePrimaryCtxRetain;
        struct{

        }cuCtxGetDevice;
        struct{
            CUlibrary * library;
            const void * code;
            CUjit_option * jitOptions;
             void * * jitOptionsValues;
             unsigned int numJitOptions;
             CUlibraryOption * libraryOptions;
              void * * libraryOptionValues;
              unsigned int numLibraryOptions;
        }cuLibraryLoadData;
        struct{
            CUcontext ctx;
        }cuCtxPushCurrent;
        struct{
            CUlibrary library;
        }cuLibraryUnload;
        struct{
            CUdevice dev;
        }cuDevicePrimaryCtxRelease;

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

            int pi;
        }returnParams;
};


#endif