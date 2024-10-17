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


using CuDriverCallStructure=struct {
    CuDriverCall op;

    union{
        struct{

        }cuInit;
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
            int * driverVersion;
        }cuDriverGetVersion;
        struct{
            CUdevice * device;
            int ordinal;
        }cuDeviceGet;
        struct{
            int * count;
        }cuDeviceGetCount;
        struct{
            char * name;
            int len;
            CUdevice device;
        }cuDeviceGetName;
        struct {
            CUuuid * uuid;
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
            int * pi;
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


using CuDriverCallReplyStructure=struct {
        CuDriverCall op;
        CUresult  result;


        union{

        }returnParams;
};