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
    CuLibraryLoadData,
    CuLibraryUnload,
    CuDevicePrimaryCtxRelease,
    CuCtxPushCurrent,
    CuInit,
};


struct CuDriverCallStructure {
    CuDriverCall op;

    union{
        struct{

        }empty;
        struct{
            size_t size;
        }cuMemAlloc;

        struct{
            CUdeviceptr dptr;
        }cuMemFree;
        struct{
            const void * srcHost;
            CUdeviceptr dstDevice;
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
            CUdeviceptr dptr;
            int pi;

            CUcontext ctx;

            size_t  bytes;
        }returnParams;
};


#endif