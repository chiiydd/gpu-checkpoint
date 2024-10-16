
// auto generate 471 apis

#include "cuda_subset.h"
#include "hook.h"
#include "macro_common.h"
#include "trace_profile.h"
#include <cstdio>

CUresult cuGetErrorString(CUresult error, const char * * pStr) {
    HOOK_TRACE_PROFILE("cuGetErrorString");
    using func_ptr = CUresult (*)(CUresult, const char * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGetErrorString"));
    HOOK_CHECK(func_entry);
    return func_entry(error, pStr);
}

CUresult cuGetErrorName(CUresult error, const char * * pStr) {
    HOOK_TRACE_PROFILE("cuGetErrorName");
    using func_ptr = CUresult (*)(CUresult, const char * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGetErrorName"));
    HOOK_CHECK(func_entry);
    return func_entry(error, pStr);
}

CUresult cuInit(unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuInit");
    using func_ptr = CUresult (*)(unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuInit"));
    HOOK_CHECK(func_entry);
    return func_entry(Flags);
}

CUresult cuDriverGetVersion(int * driverVersion) {
    HOOK_TRACE_PROFILE("cuDriverGetVersion");
    using func_ptr = CUresult (*)(int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDriverGetVersion"));
    HOOK_CHECK(func_entry);
    return func_entry(driverVersion);
}

CUresult cuDeviceGet(CUdevice * device, int ordinal) {
    HOOK_TRACE_PROFILE("cuDeviceGet");
    using func_ptr = CUresult (*)(CUdevice *, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGet"));
    HOOK_CHECK(func_entry);
    return func_entry(device, ordinal);
}

CUresult cuDeviceGetCount(int * count) {
    HOOK_TRACE_PROFILE("cuDeviceGetCount");
    using func_ptr = CUresult (*)(int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetCount"));
    HOOK_CHECK(func_entry);
    return func_entry(count);
}

CUresult cuDeviceGetName(char * name, int len, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetName");
    using func_ptr = CUresult (*)(char *, int, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetName"));
    HOOK_CHECK(func_entry);
    return func_entry(name, len, dev);
}

CUresult cuDeviceGetUuid(CUuuid * uuid, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetUuid");
    using func_ptr = CUresult (*)(CUuuid *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetUuid"));
    HOOK_CHECK(func_entry);
    return func_entry(uuid, dev);
}

CUresult cuDeviceGetUuid_v2(CUuuid * uuid, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetUuid_v2");
    using func_ptr = CUresult (*)(CUuuid *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetUuid_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(uuid, dev);
}

CUresult cuDeviceGetLuid(char * luid, unsigned int * deviceNodeMask, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetLuid");
    using func_ptr = CUresult (*)(char *, unsigned int *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetLuid"));
    HOOK_CHECK(func_entry);
    return func_entry(luid, deviceNodeMask, dev);
}

CUresult cuDeviceTotalMem(size_t * bytes, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceTotalMem");
    using func_ptr = CUresult (*)(size_t *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceTotalMem"));
    HOOK_CHECK(func_entry);
    return func_entry(bytes, dev);
}

CUresult cuDeviceGetTexture1DLinearMaxWidth(size_t * maxWidthInElements, CUarray_format format, unsigned numChannels, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetTexture1DLinearMaxWidth");
    using func_ptr = CUresult (*)(size_t *, CUarray_format, unsigned, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetTexture1DLinearMaxWidth"));
    HOOK_CHECK(func_entry);
    return func_entry(maxWidthInElements, format, numChannels, dev);
}

CUresult cuDeviceGetAttribute(int * pi, CUdevice_attribute attrib, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetAttribute");
    using func_ptr = CUresult (*)(int *, CUdevice_attribute, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(pi, attrib, dev);
}

CUresult cuDeviceGetNvSciSyncAttributes(void * nvSciSyncAttrList, CUdevice dev, int flags) {
    HOOK_TRACE_PROFILE("cuDeviceGetNvSciSyncAttributes");
    using func_ptr = CUresult (*)(void *, CUdevice, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetNvSciSyncAttributes"));
    HOOK_CHECK(func_entry);
    return func_entry(nvSciSyncAttrList, dev, flags);
}

CUresult cuDeviceSetMemPool(CUdevice dev, CUmemoryPool pool) {
    HOOK_TRACE_PROFILE("cuDeviceSetMemPool");
    using func_ptr = CUresult (*)(CUdevice, CUmemoryPool);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceSetMemPool"));
    HOOK_CHECK(func_entry);
    return func_entry(dev, pool);
}

CUresult cuDeviceGetMemPool(CUmemoryPool * pool, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetMemPool");
    using func_ptr = CUresult (*)(CUmemoryPool *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetMemPool"));
    HOOK_CHECK(func_entry);
    return func_entry(pool, dev);
}

CUresult cuDeviceGetDefaultMemPool(CUmemoryPool * pool_out, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetDefaultMemPool");
    using func_ptr = CUresult (*)(CUmemoryPool *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetDefaultMemPool"));
    HOOK_CHECK(func_entry);
    return func_entry(pool_out, dev);
}

CUresult cuDeviceGetExecAffinitySupport(int * pi, CUexecAffinityType type, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetExecAffinitySupport");
    using func_ptr = CUresult (*)(int *, CUexecAffinityType, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetExecAffinitySupport"));
    HOOK_CHECK(func_entry);
    return func_entry(pi, type, dev);
}

CUresult cuFlushGPUDirectRDMAWrites(CUflushGPUDirectRDMAWritesTarget target, CUflushGPUDirectRDMAWritesScope scope) {
    HOOK_TRACE_PROFILE("cuFlushGPUDirectRDMAWrites");
    using func_ptr = CUresult (*)(CUflushGPUDirectRDMAWritesTarget, CUflushGPUDirectRDMAWritesScope);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFlushGPUDirectRDMAWrites"));
    HOOK_CHECK(func_entry);
    return func_entry(target, scope);
}

CUresult cuDeviceGetProperties(CUdevprop * prop, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetProperties");
    using func_ptr = CUresult (*)(CUdevprop *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetProperties"));
    HOOK_CHECK(func_entry);
    return func_entry(prop, dev);
}

CUresult cuDeviceComputeCapability(int * major, int * minor, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceComputeCapability");
    using func_ptr = CUresult (*)(int *, int *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceComputeCapability"));
    HOOK_CHECK(func_entry);
    return func_entry(major, minor, dev);
}

CUresult cuDevicePrimaryCtxRetain(CUcontext * pctx, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxRetain");
    using func_ptr = CUresult (*)(CUcontext *, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevicePrimaryCtxRetain"));
    HOOK_CHECK(func_entry);
    return func_entry(pctx, dev);
}

CUresult cuDevicePrimaryCtxRelease(CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxRelease");
    using func_ptr = CUresult (*)(CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevicePrimaryCtxRelease"));
    HOOK_CHECK(func_entry);
    return func_entry(dev);
}

CUresult cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxSetFlags");
    using func_ptr = CUresult (*)(CUdevice, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevicePrimaryCtxSetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(dev, flags);
}

CUresult cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int * flags, int * active) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxGetState");
    using func_ptr = CUresult (*)(CUdevice, unsigned int *, int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevicePrimaryCtxGetState"));
    HOOK_CHECK(func_entry);
    return func_entry(dev, flags, active);
}

CUresult cuDevicePrimaryCtxReset(CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxReset");
    using func_ptr = CUresult (*)(CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevicePrimaryCtxReset"));
    HOOK_CHECK(func_entry);
    return func_entry(dev);
}

CUresult cuCtxCreate(CUcontext * pctx, unsigned int flags, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuCtxCreate");
    using func_ptr = CUresult (*)(CUcontext *, unsigned int, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pctx, flags, dev);
}

CUresult cuCtxCreate_v3(CUcontext * pctx, CUexecAffinityParam * paramsArray, int numParams, unsigned int flags, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuCtxCreate_v3");
    using func_ptr = CUresult (*)(CUcontext *, CUexecAffinityParam *, int, unsigned int, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxCreate_v3"));
    HOOK_CHECK(func_entry);
    return func_entry(pctx, paramsArray, numParams, flags, dev);
}

CUresult cuCtxDestroy(CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuCtxDestroy");
    using func_ptr = CUresult (*)(CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(ctx);
}

CUresult cuCtxPushCurrent(CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuCtxPushCurrent");
    using func_ptr = CUresult (*)(CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxPushCurrent"));
    HOOK_CHECK(func_entry);
    return func_entry(ctx);
}

CUresult cuCtxPopCurrent(CUcontext * pctx) {
    HOOK_TRACE_PROFILE("cuCtxPopCurrent");
    using func_ptr = CUresult (*)(CUcontext *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxPopCurrent"));
    HOOK_CHECK(func_entry);
    return func_entry(pctx);
}

CUresult cuCtxSetCurrent(CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuCtxSetCurrent");
    using func_ptr = CUresult (*)(CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxSetCurrent"));
    HOOK_CHECK(func_entry);
    return func_entry(ctx);
}

CUresult cuCtxGetCurrent(CUcontext * pctx) {
    HOOK_TRACE_PROFILE("cuCtxGetCurrent");
    using func_ptr = CUresult (*)(CUcontext *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetCurrent"));
    HOOK_CHECK(func_entry);
    return func_entry(pctx);
}

CUresult cuCtxGetDevice(CUdevice * device) {
    HOOK_TRACE_PROFILE("cuCtxGetDevice");
    using func_ptr = CUresult (*)(CUdevice *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetDevice"));
    HOOK_CHECK(func_entry);
    return func_entry(device);
}

CUresult cuCtxGetFlags(unsigned int * flags) {
    HOOK_TRACE_PROFILE("cuCtxGetFlags");
    using func_ptr = CUresult (*)(unsigned int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(flags);
}

CUresult cuCtxSetFlags(unsigned int flags) {
    HOOK_TRACE_PROFILE("cuCtxSetFlags");
    using func_ptr = CUresult (*)(unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxSetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(flags);
}

CUresult cuCtxGetId(CUcontext ctx, unsigned long long * ctxId) {
    HOOK_TRACE_PROFILE("cuCtxGetId");
    using func_ptr = CUresult (*)(CUcontext, unsigned long long *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetId"));
    HOOK_CHECK(func_entry);
    return func_entry(ctx, ctxId);
}

CUresult cuCtxSynchronize(void ) {
    HOOK_TRACE_PROFILE("cuCtxSynchronize");
    using func_ptr = CUresult (*)(void);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxSynchronize"));
    HOOK_CHECK(func_entry);
    return func_entry();
}

CUresult cuCtxSetLimit(CUlimit limit, size_t value) {
    HOOK_TRACE_PROFILE("cuCtxSetLimit");
    using func_ptr = CUresult (*)(CUlimit, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxSetLimit"));
    HOOK_CHECK(func_entry);
    return func_entry(limit, value);
}

CUresult cuCtxGetLimit(size_t * pvalue, CUlimit limit) {
    HOOK_TRACE_PROFILE("cuCtxGetLimit");
    using func_ptr = CUresult (*)(size_t *, CUlimit);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetLimit"));
    HOOK_CHECK(func_entry);
    return func_entry(pvalue, limit);
}

CUresult cuCtxGetCacheConfig(CUfunc_cache * pconfig) {
    HOOK_TRACE_PROFILE("cuCtxGetCacheConfig");
    using func_ptr = CUresult (*)(CUfunc_cache *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetCacheConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(pconfig);
}

CUresult cuCtxSetCacheConfig(CUfunc_cache config) {
    HOOK_TRACE_PROFILE("cuCtxSetCacheConfig");
    using func_ptr = CUresult (*)(CUfunc_cache);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxSetCacheConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(config);
}

CUresult cuCtxGetApiVersion(CUcontext ctx, unsigned int * version) {
    HOOK_TRACE_PROFILE("cuCtxGetApiVersion");
    using func_ptr = CUresult (*)(CUcontext, unsigned int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetApiVersion"));
    HOOK_CHECK(func_entry);
    return func_entry(ctx, version);
}

CUresult cuCtxGetStreamPriorityRange(int * leastPriority, int * greatestPriority) {
    HOOK_TRACE_PROFILE("cuCtxGetStreamPriorityRange");
    using func_ptr = CUresult (*)(int *, int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetStreamPriorityRange"));
    HOOK_CHECK(func_entry);
    return func_entry(leastPriority, greatestPriority);
}

CUresult cuCtxResetPersistingL2Cache(void ) {
    HOOK_TRACE_PROFILE("cuCtxResetPersistingL2Cache");
    using func_ptr = CUresult (*)(void);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxResetPersistingL2Cache"));
    HOOK_CHECK(func_entry);
    return func_entry();
}

CUresult cuCtxGetExecAffinity(CUexecAffinityParam * pExecAffinity, CUexecAffinityType type) {
    HOOK_TRACE_PROFILE("cuCtxGetExecAffinity");
    using func_ptr = CUresult (*)(CUexecAffinityParam *, CUexecAffinityType);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetExecAffinity"));
    HOOK_CHECK(func_entry);
    return func_entry(pExecAffinity, type);
}

CUresult cuCtxAttach(CUcontext * pctx, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuCtxAttach");
    using func_ptr = CUresult (*)(CUcontext *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxAttach"));
    HOOK_CHECK(func_entry);
    return func_entry(pctx, flags);
}

CUresult cuCtxDetach(CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuCtxDetach");
    using func_ptr = CUresult (*)(CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxDetach"));
    HOOK_CHECK(func_entry);
    return func_entry(ctx);
}

CUresult cuCtxGetSharedMemConfig(CUsharedconfig * pConfig) {
    HOOK_TRACE_PROFILE("cuCtxGetSharedMemConfig");
    using func_ptr = CUresult (*)(CUsharedconfig *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetSharedMemConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(pConfig);
}

CUresult cuCtxSetSharedMemConfig(CUsharedconfig config) {
    HOOK_TRACE_PROFILE("cuCtxSetSharedMemConfig");
    using func_ptr = CUresult (*)(CUsharedconfig);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxSetSharedMemConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(config);
}

CUresult cuModuleLoad(CUmodule * module, const char * fname) {
    HOOK_TRACE_PROFILE("cuModuleLoad");
    using func_ptr = CUresult (*)(CUmodule *, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleLoad"));
    HOOK_CHECK(func_entry);
    return func_entry(module, fname);
}

CUresult cuModuleLoadData(CUmodule * module, const void * image) {
    HOOK_TRACE_PROFILE("cuModuleLoadData");
    using func_ptr = CUresult (*)(CUmodule *, const void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleLoadData"));
    HOOK_CHECK(func_entry);
    return func_entry(module, image);
}

CUresult cuModuleLoadDataEx(CUmodule * module, const void * image, unsigned int numOptions, CUjit_option * options, void * * optionValues) {
    HOOK_TRACE_PROFILE("cuModuleLoadDataEx");
    using func_ptr = CUresult (*)(CUmodule *, const void *, unsigned int, CUjit_option *, void * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleLoadDataEx"));
    HOOK_CHECK(func_entry);
    return func_entry(module, image, numOptions, options, optionValues);
}

CUresult cuModuleLoadFatBinary(CUmodule * module, const void * fatCubin) {
    HOOK_TRACE_PROFILE("cuModuleLoadFatBinary");
    using func_ptr = CUresult (*)(CUmodule *, const void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleLoadFatBinary"));
    HOOK_CHECK(func_entry);
    return func_entry(module, fatCubin);
}

CUresult cuModuleUnload(CUmodule hmod) {
    HOOK_TRACE_PROFILE("cuModuleUnload");
    using func_ptr = CUresult (*)(CUmodule);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleUnload"));
    HOOK_CHECK(func_entry);
    return func_entry(hmod);
}

CUresult cuModuleGetLoadingMode(CUmoduleLoadingMode * mode) {
    HOOK_TRACE_PROFILE("cuModuleGetLoadingMode");
    using func_ptr = CUresult (*)(CUmoduleLoadingMode *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleGetLoadingMode"));
    HOOK_CHECK(func_entry);
    return func_entry(mode);
}

CUresult cuModuleGetFunction(CUfunction * hfunc, CUmodule hmod, const char * name) {
    HOOK_TRACE_PROFILE("cuModuleGetFunction");
    using func_ptr = CUresult (*)(CUfunction *, CUmodule, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleGetFunction"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, hmod, name);
}

CUresult cuModuleGetFunctionCount(unsigned int * count, CUmodule mod) {
    HOOK_TRACE_PROFILE("cuModuleGetFunctionCount");
    using func_ptr = CUresult (*)(unsigned int *, CUmodule);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleGetFunctionCount"));
    HOOK_CHECK(func_entry);
    return func_entry(count, mod);
}

CUresult cuModuleEnumerateFunctions(CUfunction * functions, unsigned int numFunctions, CUmodule mod) {
    HOOK_TRACE_PROFILE("cuModuleEnumerateFunctions");
    using func_ptr = CUresult (*)(CUfunction *, unsigned int, CUmodule);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleEnumerateFunctions"));
    HOOK_CHECK(func_entry);
    return func_entry(functions, numFunctions, mod);
}

CUresult cuModuleGetGlobal(CUdeviceptr * dptr, size_t * bytes, CUmodule hmod, const char * name) {
    HOOK_TRACE_PROFILE("cuModuleGetGlobal");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t *, CUmodule, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleGetGlobal"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytes, hmod, name);
}

CUresult cuLinkCreate(unsigned int numOptions, CUjit_option * options, void * * optionValues, CUlinkState * stateOut) {
    HOOK_TRACE_PROFILE("cuLinkCreate");
    using func_ptr = CUresult (*)(unsigned int, CUjit_option *, void * *, CUlinkState *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLinkCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(numOptions, options, optionValues, stateOut);
}

CUresult cuLinkAddData(CUlinkState state, CUjitInputType type, void * data, size_t size, const char * name, unsigned int numOptions, CUjit_option * options, void * * optionValues) {
    HOOK_TRACE_PROFILE("cuLinkAddData");
    using func_ptr = CUresult (*)(CUlinkState, CUjitInputType, void *, size_t, const char *, unsigned int, CUjit_option *, void * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLinkAddData"));
    HOOK_CHECK(func_entry);
    return func_entry(state, type, data, size, name, numOptions, options, optionValues);
}

CUresult cuLinkAddFile(CUlinkState state, CUjitInputType type, const char * path, unsigned int numOptions, CUjit_option * options, void * * optionValues) {
    HOOK_TRACE_PROFILE("cuLinkAddFile");
    using func_ptr = CUresult (*)(CUlinkState, CUjitInputType, const char *, unsigned int, CUjit_option *, void * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLinkAddFile"));
    HOOK_CHECK(func_entry);
    return func_entry(state, type, path, numOptions, options, optionValues);
}

CUresult cuLinkComplete(CUlinkState state, void * * cubinOut, size_t * sizeOut) {
    HOOK_TRACE_PROFILE("cuLinkComplete");
    using func_ptr = CUresult (*)(CUlinkState, void * *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLinkComplete"));
    HOOK_CHECK(func_entry);
    return func_entry(state, cubinOut, sizeOut);
}

CUresult cuLinkDestroy(CUlinkState state) {
    HOOK_TRACE_PROFILE("cuLinkDestroy");
    using func_ptr = CUresult (*)(CUlinkState);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLinkDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(state);
}

CUresult cuModuleGetTexRef(CUtexref * pTexRef, CUmodule hmod, const char * name) {
    HOOK_TRACE_PROFILE("cuModuleGetTexRef");
    using func_ptr = CUresult (*)(CUtexref *, CUmodule, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleGetTexRef"));
    HOOK_CHECK(func_entry);
    return func_entry(pTexRef, hmod, name);
}

CUresult cuModuleGetSurfRef(CUsurfref * pSurfRef, CUmodule hmod, const char * name) {
    HOOK_TRACE_PROFILE("cuModuleGetSurfRef");
    using func_ptr = CUresult (*)(CUsurfref *, CUmodule, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuModuleGetSurfRef"));
    HOOK_CHECK(func_entry);
    return func_entry(pSurfRef, hmod, name);
}

CUresult cuLibraryLoadData(CUlibrary * library, const void * code, CUjit_option * jitOptions, void * * jitOptionsValues, unsigned int numJitOptions, CUlibraryOption * libraryOptions, void * * libraryOptionValues, unsigned int numLibraryOptions) {
    HOOK_TRACE_PROFILE("cuLibraryLoadData");
    using func_ptr = CUresult (*)(CUlibrary *, const void *, CUjit_option *, void * *, unsigned int, CUlibraryOption *, void * *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryLoadData"));
    HOOK_CHECK(func_entry);
    return func_entry(library, code, jitOptions, jitOptionsValues, numJitOptions, libraryOptions, libraryOptionValues, numLibraryOptions);
}

CUresult cuLibraryLoadFromFile(CUlibrary * library, const char * fileName, CUjit_option * jitOptions, void * * jitOptionsValues, unsigned int numJitOptions, CUlibraryOption * libraryOptions, void * * libraryOptionValues, unsigned int numLibraryOptions) {
    HOOK_TRACE_PROFILE("cuLibraryLoadFromFile");
    using func_ptr = CUresult (*)(CUlibrary *, const char *, CUjit_option *, void * *, unsigned int, CUlibraryOption *, void * *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryLoadFromFile"));
    HOOK_CHECK(func_entry);
    return func_entry(library, fileName, jitOptions, jitOptionsValues, numJitOptions, libraryOptions, libraryOptionValues, numLibraryOptions);
}

CUresult cuLibraryUnload(CUlibrary library) {
    HOOK_TRACE_PROFILE("cuLibraryUnload");
    using func_ptr = CUresult (*)(CUlibrary);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryUnload"));
    HOOK_CHECK(func_entry);
    return func_entry(library);
}

CUresult cuLibraryGetKernel(CUkernel * pKernel, CUlibrary library, const char * name) {
    HOOK_TRACE_PROFILE("cuLibraryGetKernel");
    using func_ptr = CUresult (*)(CUkernel *, CUlibrary, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryGetKernel"));
    HOOK_CHECK(func_entry);
    return func_entry(pKernel, library, name);
}

CUresult cuLibraryGetKernelCount(unsigned int * count, CUlibrary lib) {
    HOOK_TRACE_PROFILE("cuLibraryGetKernelCount");
    using func_ptr = CUresult (*)(unsigned int *, CUlibrary);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryGetKernelCount"));
    HOOK_CHECK(func_entry);
    return func_entry(count, lib);
}

CUresult cuLibraryEnumerateKernels(CUkernel * kernels, unsigned int numKernels, CUlibrary lib) {
    HOOK_TRACE_PROFILE("cuLibraryEnumerateKernels");
    using func_ptr = CUresult (*)(CUkernel *, unsigned int, CUlibrary);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryEnumerateKernels"));
    HOOK_CHECK(func_entry);
    return func_entry(kernels, numKernels, lib);
}

CUresult cuLibraryGetModule(CUmodule * pMod, CUlibrary library) {
    HOOK_TRACE_PROFILE("cuLibraryGetModule");
    using func_ptr = CUresult (*)(CUmodule *, CUlibrary);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryGetModule"));
    HOOK_CHECK(func_entry);
    return func_entry(pMod, library);
}

CUresult cuKernelGetFunction(CUfunction * pFunc, CUkernel kernel) {
    HOOK_TRACE_PROFILE("cuKernelGetFunction");
    using func_ptr = CUresult (*)(CUfunction *, CUkernel);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuKernelGetFunction"));
    HOOK_CHECK(func_entry);
    return func_entry(pFunc, kernel);
}

CUresult cuLibraryGetGlobal(CUdeviceptr * dptr, size_t * bytes, CUlibrary library, const char * name) {
    HOOK_TRACE_PROFILE("cuLibraryGetGlobal");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t *, CUlibrary, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryGetGlobal"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytes, library, name);
}

CUresult cuLibraryGetManaged(CUdeviceptr * dptr, size_t * bytes, CUlibrary library, const char * name) {
    HOOK_TRACE_PROFILE("cuLibraryGetManaged");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t *, CUlibrary, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryGetManaged"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytes, library, name);
}

CUresult cuLibraryGetUnifiedFunction(void * * fptr, CUlibrary library, const char * symbol) {
    HOOK_TRACE_PROFILE("cuLibraryGetUnifiedFunction");
    using func_ptr = CUresult (*)(void * *, CUlibrary, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLibraryGetUnifiedFunction"));
    HOOK_CHECK(func_entry);
    return func_entry(fptr, library, symbol);
}

CUresult cuKernelGetAttribute(int * pi, CUfunction_attribute attrib, CUkernel kernel, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuKernelGetAttribute");
    using func_ptr = CUresult (*)(int *, CUfunction_attribute, CUkernel, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuKernelGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(pi, attrib, kernel, dev);
}

CUresult cuKernelSetAttribute(CUfunction_attribute attrib, int val, CUkernel kernel, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuKernelSetAttribute");
    using func_ptr = CUresult (*)(CUfunction_attribute, int, CUkernel, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuKernelSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(attrib, val, kernel, dev);
}

CUresult cuKernelSetCacheConfig(CUkernel kernel, CUfunc_cache config, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuKernelSetCacheConfig");
    using func_ptr = CUresult (*)(CUkernel, CUfunc_cache, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuKernelSetCacheConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(kernel, config, dev);
}

CUresult cuKernelGetName(const char * * name, CUkernel hfunc) {
    HOOK_TRACE_PROFILE("cuKernelGetName");
    using func_ptr = CUresult (*)(const char * *, CUkernel);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuKernelGetName"));
    HOOK_CHECK(func_entry);
    return func_entry(name, hfunc);
}

CUresult cuKernelGetParamInfo(CUkernel kernel, size_t paramIndex, size_t * paramOffset, size_t * paramSize) {
    HOOK_TRACE_PROFILE("cuKernelGetParamInfo");
    using func_ptr = CUresult (*)(CUkernel, size_t, size_t *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuKernelGetParamInfo"));
    HOOK_CHECK(func_entry);
    return func_entry(kernel, paramIndex, paramOffset, paramSize);
}

CUresult cuMemGetInfo(size_t * free, size_t * total) {
    HOOK_TRACE_PROFILE("cuMemGetInfo");
    using func_ptr = CUresult (*)(size_t *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemGetInfo"));
    HOOK_CHECK(func_entry);
    return func_entry(free, total);
}

CUresult cuMemAlloc(CUdeviceptr * dptr, size_t bytesize) {
    HOOK_TRACE_PROFILE("cuMemAlloc");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAlloc"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytesize);
}

CUresult cuMemAllocPitch(CUdeviceptr * dptr, size_t * pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes) {
    HOOK_TRACE_PROFILE("cuMemAllocPitch");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t *, size_t, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAllocPitch"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, pPitch, WidthInBytes, Height, ElementSizeBytes);
}

CUresult cuMemFree(CUdeviceptr dptr) {
    HOOK_TRACE_PROFILE("cuMemFree");
    using func_ptr = CUresult (*)(CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemFree"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr);
}

CUresult cuMemGetAddressRange(CUdeviceptr * pbase, size_t * psize, CUdeviceptr dptr) {
    HOOK_TRACE_PROFILE("cuMemGetAddressRange");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t *, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemGetAddressRange"));
    HOOK_CHECK(func_entry);
    return func_entry(pbase, psize, dptr);
}

CUresult cuMemAllocHost(void * * pp, size_t bytesize) {
    HOOK_TRACE_PROFILE("cuMemAllocHost");
    using func_ptr = CUresult (*)(void * *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAllocHost"));
    HOOK_CHECK(func_entry);
    return func_entry(pp, bytesize);
}

CUresult cuMemFreeHost(void * p) {
    HOOK_TRACE_PROFILE("cuMemFreeHost");
    using func_ptr = CUresult (*)(void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemFreeHost"));
    HOOK_CHECK(func_entry);
    return func_entry(p);
}

CUresult cuMemHostAlloc(void * * pp, size_t bytesize, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuMemHostAlloc");
    using func_ptr = CUresult (*)(void * *, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemHostAlloc"));
    HOOK_CHECK(func_entry);
    return func_entry(pp, bytesize, Flags);
}

CUresult cuMemHostGetDevicePointer(CUdeviceptr * pdptr, void * p, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuMemHostGetDevicePointer");
    using func_ptr = CUresult (*)(CUdeviceptr *, void *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemHostGetDevicePointer"));
    HOOK_CHECK(func_entry);
    return func_entry(pdptr, p, Flags);
}

CUresult cuMemHostGetFlags(unsigned int * pFlags, void * p) {
    HOOK_TRACE_PROFILE("cuMemHostGetFlags");
    using func_ptr = CUresult (*)(unsigned int *, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemHostGetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(pFlags, p);
}

CUresult cuMemAllocManaged(CUdeviceptr * dptr, size_t bytesize, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuMemAllocManaged");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAllocManaged"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytesize, flags);
}

CUresult cuDeviceRegisterAsyncNotification(CUdevice device, CUasyncCallback callbackFunc, void * userData, CUasyncCallbackHandle * callback) {
    HOOK_TRACE_PROFILE("cuDeviceRegisterAsyncNotification");
    using func_ptr = CUresult (*)(CUdevice, CUasyncCallback, void *, CUasyncCallbackHandle *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceRegisterAsyncNotification"));
    HOOK_CHECK(func_entry);
    return func_entry(device, callbackFunc, userData, callback);
}

CUresult cuDeviceUnregisterAsyncNotification(CUdevice device, CUasyncCallbackHandle callback) {
    HOOK_TRACE_PROFILE("cuDeviceUnregisterAsyncNotification");
    using func_ptr = CUresult (*)(CUdevice, CUasyncCallbackHandle);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceUnregisterAsyncNotification"));
    HOOK_CHECK(func_entry);
    return func_entry(device, callback);
}

CUresult cuDeviceGetByPCIBusId(CUdevice * dev, const char * pciBusId) {
    HOOK_TRACE_PROFILE("cuDeviceGetByPCIBusId");
    using func_ptr = CUresult (*)(CUdevice *, const char *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetByPCIBusId"));
    HOOK_CHECK(func_entry);
    return func_entry(dev, pciBusId);
}

CUresult cuDeviceGetPCIBusId(char * pciBusId, int len, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetPCIBusId");
    using func_ptr = CUresult (*)(char *, int, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetPCIBusId"));
    HOOK_CHECK(func_entry);
    return func_entry(pciBusId, len, dev);
}

CUresult cuIpcGetEventHandle(CUipcEventHandle * pHandle, CUevent event) {
    HOOK_TRACE_PROFILE("cuIpcGetEventHandle");
    using func_ptr = CUresult (*)(CUipcEventHandle *, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuIpcGetEventHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(pHandle, event);
}

CUresult cuIpcOpenEventHandle(CUevent * phEvent, CUipcEventHandle handle) {
    HOOK_TRACE_PROFILE("cuIpcOpenEventHandle");
    using func_ptr = CUresult (*)(CUevent *, CUipcEventHandle);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuIpcOpenEventHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(phEvent, handle);
}

CUresult cuIpcGetMemHandle(CUipcMemHandle * pHandle, CUdeviceptr dptr) {
    HOOK_TRACE_PROFILE("cuIpcGetMemHandle");
    using func_ptr = CUresult (*)(CUipcMemHandle *, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuIpcGetMemHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(pHandle, dptr);
}

CUresult cuIpcOpenMemHandle(CUdeviceptr * pdptr, CUipcMemHandle handle, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuIpcOpenMemHandle");
    using func_ptr = CUresult (*)(CUdeviceptr *, CUipcMemHandle, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuIpcOpenMemHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(pdptr, handle, Flags);
}

CUresult cuIpcCloseMemHandle(CUdeviceptr dptr) {
    HOOK_TRACE_PROFILE("cuIpcCloseMemHandle");
    using func_ptr = CUresult (*)(CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuIpcCloseMemHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr);
}

CUresult cuMemHostRegister(void * p, size_t bytesize, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuMemHostRegister");
    using func_ptr = CUresult (*)(void *, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemHostRegister"));
    HOOK_CHECK(func_entry);
    return func_entry(p, bytesize, Flags);
}

CUresult cuMemHostUnregister(void * p) {
    HOOK_TRACE_PROFILE("cuMemHostUnregister");
    using func_ptr = CUresult (*)(void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemHostUnregister"));
    HOOK_CHECK(func_entry);
    return func_entry(p);
}

CUresult cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpy");
    using func_ptr = CUresult (*)(CUdeviceptr, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy"));
    HOOK_CHECK(func_entry);
    return func_entry(dst, src, ByteCount);
}

CUresult cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyPeer");
    using func_ptr = CUresult (*)(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyPeer"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstContext, srcDevice, srcContext, ByteCount);
}

CUresult cuMemcpyHtoD(CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoD");
    using func_ptr = CUresult (*)(CUdeviceptr, const void *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoD"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcHost, ByteCount);
}

CUresult cuMemcpyDtoH(void * dstHost, CUdeviceptr srcDevice, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoH");
    using func_ptr = CUresult (*)(void *, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoH"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcDevice, ByteCount);
}

CUresult cuMemcpyDtoD(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoD");
    using func_ptr = CUresult (*)(CUdeviceptr, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoD"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcDevice, ByteCount);
}

CUresult cuMemcpyDtoA(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoA");
    using func_ptr = CUresult (*)(CUarray, size_t, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoA"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcDevice, ByteCount);
}

CUresult cuMemcpyAtoD(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoD");
    using func_ptr = CUresult (*)(CUdeviceptr, CUarray, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoD"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcArray, srcOffset, ByteCount);
}

CUresult cuMemcpyHtoA(CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoA");
    using func_ptr = CUresult (*)(CUarray, size_t, const void *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoA"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcHost, ByteCount);
}

CUresult cuMemcpyAtoH(void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoH");
    using func_ptr = CUresult (*)(void *, CUarray, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoH"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcArray, srcOffset, ByteCount);
}

CUresult cuMemcpyAtoA(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoA");
    using func_ptr = CUresult (*)(CUarray, size_t, CUarray, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoA"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcArray, srcOffset, ByteCount);
}

CUresult cuMemcpy2D(const CUDA_MEMCPY2D * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy2D");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY2D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy2D"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpy2DUnaligned(const CUDA_MEMCPY2D * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy2DUnaligned");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY2D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy2DUnaligned"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpy3D(const CUDA_MEMCPY3D * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy3D");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY3D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy3D"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy3DPeer");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY3D_PEER *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy3DPeer"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyAsync");
    using func_ptr = CUresult (*)(CUdeviceptr, CUdeviceptr, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dst, src, ByteCount, hStream);
}

CUresult cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyPeerAsync");
    using func_ptr = CUresult (*)(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyPeerAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstContext, srcDevice, srcContext, ByteCount, hStream);
}

CUresult cuMemcpyHtoDAsync(CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoDAsync");
    using func_ptr = CUresult (*)(CUdeviceptr, const void *, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoDAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcHost, ByteCount, hStream);
}

CUresult cuMemcpyDtoHAsync(void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoHAsync");
    using func_ptr = CUresult (*)(void *, CUdeviceptr, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoHAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcDevice, ByteCount, hStream);
}

CUresult cuMemcpyDtoDAsync(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoDAsync");
    using func_ptr = CUresult (*)(CUdeviceptr, CUdeviceptr, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoDAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcDevice, ByteCount, hStream);
}

CUresult cuMemcpyHtoAAsync(CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoAAsync");
    using func_ptr = CUresult (*)(CUarray, size_t, const void *, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoAAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcHost, ByteCount, hStream);
}

CUresult cuMemcpyAtoHAsync(void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoHAsync");
    using func_ptr = CUresult (*)(void *, CUarray, size_t, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoHAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcArray, srcOffset, ByteCount, hStream);
}

CUresult cuMemcpy2DAsync(const CUDA_MEMCPY2D * pCopy, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpy2DAsync");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY2D *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy2DAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy, hStream);
}

CUresult cuMemcpy3DAsync(const CUDA_MEMCPY3D * pCopy, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpy3DAsync");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY3D *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy3DAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy, hStream);
}

CUresult cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER * pCopy, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpy3DPeerAsync");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY3D_PEER *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy3DPeerAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy, hStream);
}

CUresult cuMemsetD8(CUdeviceptr dstDevice, unsigned char uc, size_t N) {
    HOOK_TRACE_PROFILE("cuMemsetD8");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned char, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD8"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, uc, N);
}

CUresult cuMemsetD16(CUdeviceptr dstDevice, unsigned short us, size_t N) {
    HOOK_TRACE_PROFILE("cuMemsetD16");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned short, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD16"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, us, N);
}

CUresult cuMemsetD32(CUdeviceptr dstDevice, unsigned int ui, size_t N) {
    HOOK_TRACE_PROFILE("cuMemsetD32");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned int, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD32"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, ui, N);
}

CUresult cuMemsetD2D8(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height) {
    HOOK_TRACE_PROFILE("cuMemsetD2D8");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned char, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D8"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, uc, Width, Height);
}

CUresult cuMemsetD2D16(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height) {
    HOOK_TRACE_PROFILE("cuMemsetD2D16");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned short, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D16"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, us, Width, Height);
}

CUresult cuMemsetD2D32(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height) {
    HOOK_TRACE_PROFILE("cuMemsetD2D32");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned int, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D32"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, ui, Width, Height);
}

CUresult cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemsetD8Async");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned char, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD8Async"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, uc, N, hStream);
}

CUresult cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemsetD16Async");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned short, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD16Async"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, us, N, hStream);
}

CUresult cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemsetD32Async");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned int, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD32Async"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, ui, N, hStream);
}

CUresult cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemsetD2D8Async");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned char, size_t, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D8Async"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, uc, Width, Height, hStream);
}

CUresult cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemsetD2D16Async");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned short, size_t, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D16Async"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, us, Width, Height, hStream);
}

CUresult cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemsetD2D32Async");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned int, size_t, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D32Async"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, ui, Width, Height, hStream);
}

CUresult cuArrayCreate(CUarray * pHandle, const CUDA_ARRAY_DESCRIPTOR * pAllocateArray) {
    HOOK_TRACE_PROFILE("cuArrayCreate");
    using func_ptr = CUresult (*)(CUarray *, const CUDA_ARRAY_DESCRIPTOR *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArrayCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pHandle, pAllocateArray);
}

CUresult cuArrayGetDescriptor(CUDA_ARRAY_DESCRIPTOR * pArrayDescriptor, CUarray hArray) {
    HOOK_TRACE_PROFILE("cuArrayGetDescriptor");
    using func_ptr = CUresult (*)(CUDA_ARRAY_DESCRIPTOR *, CUarray);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArrayGetDescriptor"));
    HOOK_CHECK(func_entry);
    return func_entry(pArrayDescriptor, hArray);
}

CUresult cuArrayGetSparseProperties(CUDA_ARRAY_SPARSE_PROPERTIES * sparseProperties, CUarray array) {
    HOOK_TRACE_PROFILE("cuArrayGetSparseProperties");
    using func_ptr = CUresult (*)(CUDA_ARRAY_SPARSE_PROPERTIES *, CUarray);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArrayGetSparseProperties"));
    HOOK_CHECK(func_entry);
    return func_entry(sparseProperties, array);
}

CUresult cuMipmappedArrayGetSparseProperties(CUDA_ARRAY_SPARSE_PROPERTIES * sparseProperties, CUmipmappedArray mipmap) {
    HOOK_TRACE_PROFILE("cuMipmappedArrayGetSparseProperties");
    using func_ptr = CUresult (*)(CUDA_ARRAY_SPARSE_PROPERTIES *, CUmipmappedArray);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMipmappedArrayGetSparseProperties"));
    HOOK_CHECK(func_entry);
    return func_entry(sparseProperties, mipmap);
}

CUresult cuArrayGetMemoryRequirements(CUDA_ARRAY_MEMORY_REQUIREMENTS * memoryRequirements, CUarray array, CUdevice device) {
    HOOK_TRACE_PROFILE("cuArrayGetMemoryRequirements");
    using func_ptr = CUresult (*)(CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUarray, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArrayGetMemoryRequirements"));
    HOOK_CHECK(func_entry);
    return func_entry(memoryRequirements, array, device);
}

CUresult cuMipmappedArrayGetMemoryRequirements(CUDA_ARRAY_MEMORY_REQUIREMENTS * memoryRequirements, CUmipmappedArray mipmap, CUdevice device) {
    HOOK_TRACE_PROFILE("cuMipmappedArrayGetMemoryRequirements");
    using func_ptr = CUresult (*)(CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUmipmappedArray, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMipmappedArrayGetMemoryRequirements"));
    HOOK_CHECK(func_entry);
    return func_entry(memoryRequirements, mipmap, device);
}

CUresult cuArrayGetPlane(CUarray * pPlaneArray, CUarray hArray, unsigned int planeIdx) {
    HOOK_TRACE_PROFILE("cuArrayGetPlane");
    using func_ptr = CUresult (*)(CUarray *, CUarray, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArrayGetPlane"));
    HOOK_CHECK(func_entry);
    return func_entry(pPlaneArray, hArray, planeIdx);
}

CUresult cuArrayDestroy(CUarray hArray) {
    HOOK_TRACE_PROFILE("cuArrayDestroy");
    using func_ptr = CUresult (*)(CUarray);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArrayDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hArray);
}

CUresult cuArray3DCreate(CUarray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pAllocateArray) {
    HOOK_TRACE_PROFILE("cuArray3DCreate");
    using func_ptr = CUresult (*)(CUarray *, const CUDA_ARRAY3D_DESCRIPTOR *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArray3DCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pHandle, pAllocateArray);
}

CUresult cuArray3DGetDescriptor(CUDA_ARRAY3D_DESCRIPTOR * pArrayDescriptor, CUarray hArray) {
    HOOK_TRACE_PROFILE("cuArray3DGetDescriptor");
    using func_ptr = CUresult (*)(CUDA_ARRAY3D_DESCRIPTOR *, CUarray);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuArray3DGetDescriptor"));
    HOOK_CHECK(func_entry);
    return func_entry(pArrayDescriptor, hArray);
}

CUresult cuMipmappedArrayCreate(CUmipmappedArray * pHandle, const CUDA_ARRAY3D_DESCRIPTOR * pMipmappedArrayDesc, unsigned int numMipmapLevels) {
    HOOK_TRACE_PROFILE("cuMipmappedArrayCreate");
    using func_ptr = CUresult (*)(CUmipmappedArray *, const CUDA_ARRAY3D_DESCRIPTOR *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMipmappedArrayCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pHandle, pMipmappedArrayDesc, numMipmapLevels);
}

CUresult cuMipmappedArrayGetLevel(CUarray * pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level) {
    HOOK_TRACE_PROFILE("cuMipmappedArrayGetLevel");
    using func_ptr = CUresult (*)(CUarray *, CUmipmappedArray, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMipmappedArrayGetLevel"));
    HOOK_CHECK(func_entry);
    return func_entry(pLevelArray, hMipmappedArray, level);
}

CUresult cuMipmappedArrayDestroy(CUmipmappedArray hMipmappedArray) {
    HOOK_TRACE_PROFILE("cuMipmappedArrayDestroy");
    using func_ptr = CUresult (*)(CUmipmappedArray);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMipmappedArrayDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hMipmappedArray);
}

CUresult cuMemGetHandleForAddressRange(void * handle, CUdeviceptr dptr, size_t size, CUmemRangeHandleType handleType, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemGetHandleForAddressRange");
    using func_ptr = CUresult (*)(void *, CUdeviceptr, size_t, CUmemRangeHandleType, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemGetHandleForAddressRange"));
    HOOK_CHECK(func_entry);
    return func_entry(handle, dptr, size, handleType, flags);
}

CUresult cuMemAddressReserve(CUdeviceptr * ptr, size_t size, size_t alignment, CUdeviceptr addr, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemAddressReserve");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t, size_t, CUdeviceptr, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAddressReserve"));
    HOOK_CHECK(func_entry);
    return func_entry(ptr, size, alignment, addr, flags);
}

CUresult cuMemAddressFree(CUdeviceptr ptr, size_t size) {
    HOOK_TRACE_PROFILE("cuMemAddressFree");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAddressFree"));
    HOOK_CHECK(func_entry);
    return func_entry(ptr, size);
}

CUresult cuMemCreate(CUmemGenericAllocationHandle * handle, size_t size, const CUmemAllocationProp * prop, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemCreate");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle *, size_t, const CUmemAllocationProp *, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(handle, size, prop, flags);
}

CUresult cuMemRelease(CUmemGenericAllocationHandle handle) {
    HOOK_TRACE_PROFILE("cuMemRelease");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemRelease"));
    HOOK_CHECK(func_entry);
    return func_entry(handle);
}

CUresult cuMemMap(CUdeviceptr ptr, size_t size, size_t offset, CUmemGenericAllocationHandle handle, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemMap");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, size_t, CUmemGenericAllocationHandle, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemMap"));
    HOOK_CHECK(func_entry);
    return func_entry(ptr, size, offset, handle, flags);
}

CUresult cuMemMapArrayAsync(CUarrayMapInfo * mapInfoList, unsigned int count, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemMapArrayAsync");
    using func_ptr = CUresult (*)(CUarrayMapInfo *, unsigned int, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemMapArrayAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(mapInfoList, count, hStream);
}

CUresult cuMemUnmap(CUdeviceptr ptr, size_t size) {
    HOOK_TRACE_PROFILE("cuMemUnmap");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemUnmap"));
    HOOK_CHECK(func_entry);
    return func_entry(ptr, size);
}

CUresult cuMemSetAccess(CUdeviceptr ptr, size_t size, const CUmemAccessDesc * desc, size_t count) {
    HOOK_TRACE_PROFILE("cuMemSetAccess");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, const CUmemAccessDesc *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemSetAccess"));
    HOOK_CHECK(func_entry);
    return func_entry(ptr, size, desc, count);
}

CUresult cuMemGetAccess(unsigned long long * flags, const CUmemLocation * location, CUdeviceptr ptr) {
    HOOK_TRACE_PROFILE("cuMemGetAccess");
    using func_ptr = CUresult (*)(unsigned long long *, const CUmemLocation *, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemGetAccess"));
    HOOK_CHECK(func_entry);
    return func_entry(flags, location, ptr);
}

CUresult cuMemExportToShareableHandle(void * shareableHandle, CUmemGenericAllocationHandle handle, CUmemAllocationHandleType handleType, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemExportToShareableHandle");
    using func_ptr = CUresult (*)(void *, CUmemGenericAllocationHandle, CUmemAllocationHandleType, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemExportToShareableHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(shareableHandle, handle, handleType, flags);
}

CUresult cuMemImportFromShareableHandle(CUmemGenericAllocationHandle * handle, void * osHandle, CUmemAllocationHandleType shHandleType) {
    HOOK_TRACE_PROFILE("cuMemImportFromShareableHandle");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle *, void *, CUmemAllocationHandleType);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemImportFromShareableHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(handle, osHandle, shHandleType);
}

CUresult cuMemGetAllocationGranularity(size_t * granularity, const CUmemAllocationProp * prop, CUmemAllocationGranularity_flags option) {
    HOOK_TRACE_PROFILE("cuMemGetAllocationGranularity");
    using func_ptr = CUresult (*)(size_t *, const CUmemAllocationProp *, CUmemAllocationGranularity_flags);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemGetAllocationGranularity"));
    HOOK_CHECK(func_entry);
    return func_entry(granularity, prop, option);
}

CUresult cuMemGetAllocationPropertiesFromHandle(CUmemAllocationProp * prop, CUmemGenericAllocationHandle handle) {
    HOOK_TRACE_PROFILE("cuMemGetAllocationPropertiesFromHandle");
    using func_ptr = CUresult (*)(CUmemAllocationProp *, CUmemGenericAllocationHandle);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemGetAllocationPropertiesFromHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(prop, handle);
}

CUresult cuMemRetainAllocationHandle(CUmemGenericAllocationHandle * handle, void * addr) {
    HOOK_TRACE_PROFILE("cuMemRetainAllocationHandle");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle *, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemRetainAllocationHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(handle, addr);
}

CUresult cuMemFreeAsync(CUdeviceptr dptr, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemFreeAsync");
    using func_ptr = CUresult (*)(CUdeviceptr, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemFreeAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, hStream);
}

CUresult cuMemAllocAsync(CUdeviceptr * dptr, size_t bytesize, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemAllocAsync");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAllocAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytesize, hStream);
}

CUresult cuMemPoolTrimTo(CUmemoryPool pool, size_t minBytesToKeep) {
    HOOK_TRACE_PROFILE("cuMemPoolTrimTo");
    using func_ptr = CUresult (*)(CUmemoryPool, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolTrimTo"));
    HOOK_CHECK(func_entry);
    return func_entry(pool, minBytesToKeep);
}

CUresult cuMemPoolSetAttribute(CUmemoryPool pool, CUmemPool_attribute attr, void * value) {
    HOOK_TRACE_PROFILE("cuMemPoolSetAttribute");
    using func_ptr = CUresult (*)(CUmemoryPool, CUmemPool_attribute, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(pool, attr, value);
}

CUresult cuMemPoolGetAttribute(CUmemoryPool pool, CUmemPool_attribute attr, void * value) {
    HOOK_TRACE_PROFILE("cuMemPoolGetAttribute");
    using func_ptr = CUresult (*)(CUmemoryPool, CUmemPool_attribute, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(pool, attr, value);
}

CUresult cuMemPoolSetAccess(CUmemoryPool pool, const CUmemAccessDesc * map, size_t count) {
    HOOK_TRACE_PROFILE("cuMemPoolSetAccess");
    using func_ptr = CUresult (*)(CUmemoryPool, const CUmemAccessDesc *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolSetAccess"));
    HOOK_CHECK(func_entry);
    return func_entry(pool, map, count);
}

CUresult cuMemPoolGetAccess(CUmemAccess_flags * flags, CUmemoryPool memPool, CUmemLocation * location) {
    HOOK_TRACE_PROFILE("cuMemPoolGetAccess");
    using func_ptr = CUresult (*)(CUmemAccess_flags *, CUmemoryPool, CUmemLocation *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolGetAccess"));
    HOOK_CHECK(func_entry);
    return func_entry(flags, memPool, location);
}

CUresult cuMemPoolCreate(CUmemoryPool * pool, const CUmemPoolProps * poolProps) {
    HOOK_TRACE_PROFILE("cuMemPoolCreate");
    using func_ptr = CUresult (*)(CUmemoryPool *, const CUmemPoolProps *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pool, poolProps);
}

CUresult cuMemPoolDestroy(CUmemoryPool pool) {
    HOOK_TRACE_PROFILE("cuMemPoolDestroy");
    using func_ptr = CUresult (*)(CUmemoryPool);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(pool);
}

CUresult cuMemAllocFromPoolAsync(CUdeviceptr * dptr, size_t bytesize, CUmemoryPool pool, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemAllocFromPoolAsync");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t, CUmemoryPool, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAllocFromPoolAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(dptr, bytesize, pool, hStream);
}

CUresult cuMemPoolExportToShareableHandle(void * handle_out, CUmemoryPool pool, CUmemAllocationHandleType handleType, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemPoolExportToShareableHandle");
    using func_ptr = CUresult (*)(void *, CUmemoryPool, CUmemAllocationHandleType, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolExportToShareableHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(handle_out, pool, handleType, flags);
}

CUresult cuMemPoolImportFromShareableHandle(CUmemoryPool * pool_out, void * handle, CUmemAllocationHandleType handleType, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMemPoolImportFromShareableHandle");
    using func_ptr = CUresult (*)(CUmemoryPool *, void *, CUmemAllocationHandleType, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolImportFromShareableHandle"));
    HOOK_CHECK(func_entry);
    return func_entry(pool_out, handle, handleType, flags);
}

CUresult cuMemPoolExportPointer(CUmemPoolPtrExportData * shareData_out, CUdeviceptr ptr) {
    HOOK_TRACE_PROFILE("cuMemPoolExportPointer");
    using func_ptr = CUresult (*)(CUmemPoolPtrExportData *, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolExportPointer"));
    HOOK_CHECK(func_entry);
    return func_entry(shareData_out, ptr);
}

CUresult cuMemPoolImportPointer(CUdeviceptr * ptr_out, CUmemoryPool pool, CUmemPoolPtrExportData * shareData) {
    HOOK_TRACE_PROFILE("cuMemPoolImportPointer");
    using func_ptr = CUresult (*)(CUdeviceptr *, CUmemoryPool, CUmemPoolPtrExportData *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPoolImportPointer"));
    HOOK_CHECK(func_entry);
    return func_entry(ptr_out, pool, shareData);
}

CUresult cuMulticastCreate(CUmemGenericAllocationHandle * mcHandle, const CUmulticastObjectProp * prop) {
    HOOK_TRACE_PROFILE("cuMulticastCreate");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle *, const CUmulticastObjectProp *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMulticastCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(mcHandle, prop);
}

CUresult cuMulticastAddDevice(CUmemGenericAllocationHandle mcHandle, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuMulticastAddDevice");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMulticastAddDevice"));
    HOOK_CHECK(func_entry);
    return func_entry(mcHandle, dev);
}

CUresult cuMulticastBindMem(CUmemGenericAllocationHandle mcHandle, size_t mcOffset, CUmemGenericAllocationHandle memHandle, size_t memOffset, size_t size, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMulticastBindMem");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle, size_t, CUmemGenericAllocationHandle, size_t, size_t, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMulticastBindMem"));
    HOOK_CHECK(func_entry);
    return func_entry(mcHandle, mcOffset, memHandle, memOffset, size, flags);
}

CUresult cuMulticastBindAddr(CUmemGenericAllocationHandle mcHandle, size_t mcOffset, CUdeviceptr memptr, size_t size, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuMulticastBindAddr");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle, size_t, CUdeviceptr, size_t, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMulticastBindAddr"));
    HOOK_CHECK(func_entry);
    return func_entry(mcHandle, mcOffset, memptr, size, flags);
}

CUresult cuMulticastUnbind(CUmemGenericAllocationHandle mcHandle, CUdevice dev, size_t mcOffset, size_t size) {
    HOOK_TRACE_PROFILE("cuMulticastUnbind");
    using func_ptr = CUresult (*)(CUmemGenericAllocationHandle, CUdevice, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMulticastUnbind"));
    HOOK_CHECK(func_entry);
    return func_entry(mcHandle, dev, mcOffset, size);
}

CUresult cuMulticastGetGranularity(size_t * granularity, const CUmulticastObjectProp * prop, CUmulticastGranularity_flags option) {
    HOOK_TRACE_PROFILE("cuMulticastGetGranularity");
    using func_ptr = CUresult (*)(size_t *, const CUmulticastObjectProp *, CUmulticastGranularity_flags);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMulticastGetGranularity"));
    HOOK_CHECK(func_entry);
    return func_entry(granularity, prop, option);
}

CUresult cuPointerGetAttribute(void * data, CUpointer_attribute attribute, CUdeviceptr ptr) {
    HOOK_TRACE_PROFILE("cuPointerGetAttribute");
    using func_ptr = CUresult (*)(void *, CUpointer_attribute, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuPointerGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(data, attribute, ptr);
}

CUresult cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemPrefetchAsync");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, CUdevice, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPrefetchAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(devPtr, count, dstDevice, hStream);
}

CUresult cuMemPrefetchAsync_v2(CUdeviceptr devPtr, size_t count, CUmemLocation location, unsigned int flags, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemPrefetchAsync_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, CUmemLocation, unsigned int, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemPrefetchAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(devPtr, count, location, flags, hStream);
}

CUresult cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device) {
    HOOK_TRACE_PROFILE("cuMemAdvise");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, CUmem_advise, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAdvise"));
    HOOK_CHECK(func_entry);
    return func_entry(devPtr, count, advice, device);
}

CUresult cuMemAdvise_v2(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUmemLocation location) {
    HOOK_TRACE_PROFILE("cuMemAdvise_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, CUmem_advise, CUmemLocation);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemAdvise_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(devPtr, count, advice, location);
}

CUresult cuMemRangeGetAttribute(void * data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count) {
    HOOK_TRACE_PROFILE("cuMemRangeGetAttribute");
    using func_ptr = CUresult (*)(void *, size_t, CUmem_range_attribute, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemRangeGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(data, dataSize, attribute, devPtr, count);
}

CUresult cuMemRangeGetAttributes(void * * data, size_t * dataSizes, CUmem_range_attribute * attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count) {
    HOOK_TRACE_PROFILE("cuMemRangeGetAttributes");
    using func_ptr = CUresult (*)(void * *, size_t *, CUmem_range_attribute *, size_t, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemRangeGetAttributes"));
    HOOK_CHECK(func_entry);
    return func_entry(data, dataSizes, attributes, numAttributes, devPtr, count);
}

CUresult cuPointerSetAttribute(const void * value, CUpointer_attribute attribute, CUdeviceptr ptr) {
    HOOK_TRACE_PROFILE("cuPointerSetAttribute");
    using func_ptr = CUresult (*)(const void *, CUpointer_attribute, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuPointerSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(value, attribute, ptr);
}

CUresult cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute * attributes, void * * data, CUdeviceptr ptr) {
    HOOK_TRACE_PROFILE("cuPointerGetAttributes");
    using func_ptr = CUresult (*)(unsigned int, CUpointer_attribute *, void * *, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuPointerGetAttributes"));
    HOOK_CHECK(func_entry);
    return func_entry(numAttributes, attributes, data, ptr);
}

CUresult cuStreamCreate(CUstream * phStream, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuStreamCreate");
    using func_ptr = CUresult (*)(CUstream *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(phStream, Flags);
}

CUresult cuStreamCreateWithPriority(CUstream * phStream, unsigned int flags, int priority) {
    HOOK_TRACE_PROFILE("cuStreamCreateWithPriority");
    using func_ptr = CUresult (*)(CUstream *, unsigned int, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamCreateWithPriority"));
    HOOK_CHECK(func_entry);
    return func_entry(phStream, flags, priority);
}

CUresult cuStreamGetPriority(CUstream hStream, int * priority) {
    HOOK_TRACE_PROFILE("cuStreamGetPriority");
    using func_ptr = CUresult (*)(CUstream, int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetPriority"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, priority);
}

CUresult cuStreamGetFlags(CUstream hStream, unsigned int * flags) {
    HOOK_TRACE_PROFILE("cuStreamGetFlags");
    using func_ptr = CUresult (*)(CUstream, unsigned int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, flags);
}

CUresult cuStreamGetId(CUstream hStream, unsigned long long * streamId) {
    HOOK_TRACE_PROFILE("cuStreamGetId");
    using func_ptr = CUresult (*)(CUstream, unsigned long long *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetId"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, streamId);
}

CUresult cuStreamGetCtx(CUstream hStream, CUcontext * pctx) {
    HOOK_TRACE_PROFILE("cuStreamGetCtx");
    using func_ptr = CUresult (*)(CUstream, CUcontext *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetCtx"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, pctx);
}

CUresult cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitEvent");
    using func_ptr = CUresult (*)(CUstream, CUevent, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, hEvent, Flags);
}

CUresult cuStreamAddCallback(CUstream hStream, CUstreamCallback callback, void * userData, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamAddCallback");
    using func_ptr = CUresult (*)(CUstream, CUstreamCallback, void *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamAddCallback"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, callback, userData, flags);
}

CUresult cuStreamBeginCapture(CUstream hStream, CUstreamCaptureMode mode) {
    HOOK_TRACE_PROFILE("cuStreamBeginCapture");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureMode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBeginCapture"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, mode);
}

CUresult cuStreamBeginCaptureToGraph(CUstream hStream, CUgraph hGraph, const CUgraphNode * dependencies, const CUgraphEdgeData * dependencyData, size_t numDependencies, CUstreamCaptureMode mode) {
    HOOK_TRACE_PROFILE("cuStreamBeginCaptureToGraph");
    using func_ptr = CUresult (*)(CUstream, CUgraph, const CUgraphNode *, const CUgraphEdgeData *, size_t, CUstreamCaptureMode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBeginCaptureToGraph"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, hGraph, dependencies, dependencyData, numDependencies, mode);
}

CUresult cuThreadExchangeStreamCaptureMode(CUstreamCaptureMode * mode) {
    HOOK_TRACE_PROFILE("cuThreadExchangeStreamCaptureMode");
    using func_ptr = CUresult (*)(CUstreamCaptureMode *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuThreadExchangeStreamCaptureMode"));
    HOOK_CHECK(func_entry);
    return func_entry(mode);
}

CUresult cuStreamEndCapture(CUstream hStream, CUgraph * phGraph) {
    HOOK_TRACE_PROFILE("cuStreamEndCapture");
    using func_ptr = CUresult (*)(CUstream, CUgraph *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamEndCapture"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, phGraph);
}

CUresult cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus * captureStatus) {
    HOOK_TRACE_PROFILE("cuStreamIsCapturing");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureStatus *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamIsCapturing"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, captureStatus);
}

CUresult cuStreamGetCaptureInfo(CUstream hStream, CUstreamCaptureStatus * captureStatus_out, cuuint64_t * id_out, CUgraph * graph_out, const CUgraphNode * * dependencies_out, size_t * numDependencies_out) {
    HOOK_TRACE_PROFILE("cuStreamGetCaptureInfo");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode * *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetCaptureInfo"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, captureStatus_out, id_out, graph_out, dependencies_out, numDependencies_out);
}

CUresult cuStreamGetCaptureInfo_v3(CUstream hStream, CUstreamCaptureStatus * captureStatus_out, cuuint64_t * id_out, CUgraph * graph_out, const CUgraphNode * * dependencies_out, const CUgraphEdgeData * * edgeData_out, size_t * numDependencies_out) {
    HOOK_TRACE_PROFILE("cuStreamGetCaptureInfo_v3");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode * *, const CUgraphEdgeData * *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetCaptureInfo_v3"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, captureStatus_out, id_out, graph_out, dependencies_out, edgeData_out, numDependencies_out);
}

CUresult cuStreamUpdateCaptureDependencies(CUstream hStream, CUgraphNode * dependencies, size_t numDependencies, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamUpdateCaptureDependencies");
    using func_ptr = CUresult (*)(CUstream, CUgraphNode *, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamUpdateCaptureDependencies"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, dependencies, numDependencies, flags);
}

CUresult cuStreamUpdateCaptureDependencies_v2(CUstream hStream, CUgraphNode * dependencies, const CUgraphEdgeData * dependencyData, size_t numDependencies, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamUpdateCaptureDependencies_v2");
    using func_ptr = CUresult (*)(CUstream, CUgraphNode *, const CUgraphEdgeData *, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamUpdateCaptureDependencies_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, dependencies, dependencyData, numDependencies, flags);
}

CUresult cuStreamAttachMemAsync(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamAttachMemAsync");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamAttachMemAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, dptr, length, flags);
}

CUresult cuStreamQuery(CUstream hStream) {
    HOOK_TRACE_PROFILE("cuStreamQuery");
    using func_ptr = CUresult (*)(CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamQuery"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream);
}

CUresult cuStreamSynchronize(CUstream hStream) {
    HOOK_TRACE_PROFILE("cuStreamSynchronize");
    using func_ptr = CUresult (*)(CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamSynchronize"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream);
}

CUresult cuStreamDestroy(CUstream hStream) {
    HOOK_TRACE_PROFILE("cuStreamDestroy");
    using func_ptr = CUresult (*)(CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream);
}

CUresult cuStreamCopyAttributes(CUstream dst, CUstream src) {
    HOOK_TRACE_PROFILE("cuStreamCopyAttributes");
    using func_ptr = CUresult (*)(CUstream, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamCopyAttributes"));
    HOOK_CHECK(func_entry);
    return func_entry(dst, src);
}

CUresult cuStreamGetAttribute(CUstream hStream, CUstreamAttrID attr, CUstreamAttrValue * value_out) {
    HOOK_TRACE_PROFILE("cuStreamGetAttribute");
    using func_ptr = CUresult (*)(CUstream, CUstreamAttrID, CUstreamAttrValue *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, attr, value_out);
}

CUresult cuStreamSetAttribute(CUstream hStream, CUstreamAttrID attr, const CUstreamAttrValue * value) {
    HOOK_TRACE_PROFILE("cuStreamSetAttribute");
    using func_ptr = CUresult (*)(CUstream, CUstreamAttrID, const CUstreamAttrValue *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, attr, value);
}

CUresult cuEventCreate(CUevent * phEvent, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuEventCreate");
    using func_ptr = CUresult (*)(CUevent *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(phEvent, Flags);
}

CUresult cuEventRecord(CUevent hEvent, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuEventRecord");
    using func_ptr = CUresult (*)(CUevent, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventRecord"));
    HOOK_CHECK(func_entry);
    return func_entry(hEvent, hStream);
}

CUresult cuEventRecordWithFlags(CUevent hEvent, CUstream hStream, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuEventRecordWithFlags");
    using func_ptr = CUresult (*)(CUevent, CUstream, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventRecordWithFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(hEvent, hStream, flags);
}

CUresult cuEventQuery(CUevent hEvent) {
    HOOK_TRACE_PROFILE("cuEventQuery");
    using func_ptr = CUresult (*)(CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventQuery"));
    HOOK_CHECK(func_entry);
    return func_entry(hEvent);
}

CUresult cuEventSynchronize(CUevent hEvent) {
    HOOK_TRACE_PROFILE("cuEventSynchronize");
    using func_ptr = CUresult (*)(CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventSynchronize"));
    HOOK_CHECK(func_entry);
    return func_entry(hEvent);
}

CUresult cuEventDestroy(CUevent hEvent) {
    HOOK_TRACE_PROFILE("cuEventDestroy");
    using func_ptr = CUresult (*)(CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hEvent);
}

CUresult cuEventElapsedTime(float * pMilliseconds, CUevent hStart, CUevent hEnd) {
    HOOK_TRACE_PROFILE("cuEventElapsedTime");
    using func_ptr = CUresult (*)(float *, CUevent, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuEventElapsedTime"));
    HOOK_CHECK(func_entry);
    return func_entry(pMilliseconds, hStart, hEnd);
}

CUresult cuImportExternalMemory(CUexternalMemory * extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC * memHandleDesc) {
    HOOK_TRACE_PROFILE("cuImportExternalMemory");
    using func_ptr = CUresult (*)(CUexternalMemory *, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuImportExternalMemory"));
    HOOK_CHECK(func_entry);
    return func_entry(extMem_out, memHandleDesc);
}

CUresult cuExternalMemoryGetMappedBuffer(CUdeviceptr * devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC * bufferDesc) {
    HOOK_TRACE_PROFILE("cuExternalMemoryGetMappedBuffer");
    using func_ptr = CUresult (*)(CUdeviceptr *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuExternalMemoryGetMappedBuffer"));
    HOOK_CHECK(func_entry);
    return func_entry(devPtr, extMem, bufferDesc);
}

CUresult cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray * mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC * mipmapDesc) {
    HOOK_TRACE_PROFILE("cuExternalMemoryGetMappedMipmappedArray");
    using func_ptr = CUresult (*)(CUmipmappedArray *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuExternalMemoryGetMappedMipmappedArray"));
    HOOK_CHECK(func_entry);
    return func_entry(mipmap, extMem, mipmapDesc);
}

CUresult cuDestroyExternalMemory(CUexternalMemory extMem) {
    HOOK_TRACE_PROFILE("cuDestroyExternalMemory");
    using func_ptr = CUresult (*)(CUexternalMemory);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDestroyExternalMemory"));
    HOOK_CHECK(func_entry);
    return func_entry(extMem);
}

CUresult cuImportExternalSemaphore(CUexternalSemaphore * extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC * semHandleDesc) {
    HOOK_TRACE_PROFILE("cuImportExternalSemaphore");
    using func_ptr = CUresult (*)(CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuImportExternalSemaphore"));
    HOOK_CHECK(func_entry);
    return func_entry(extSem_out, semHandleDesc);
}

CUresult cuSignalExternalSemaphoresAsync(const CUexternalSemaphore * extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS * paramsArray, unsigned int numExtSems, CUstream stream) {
    HOOK_TRACE_PROFILE("cuSignalExternalSemaphoresAsync");
    using func_ptr = CUresult (*)(const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *, unsigned int, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuSignalExternalSemaphoresAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(extSemArray, paramsArray, numExtSems, stream);
}

CUresult cuWaitExternalSemaphoresAsync(const CUexternalSemaphore * extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS * paramsArray, unsigned int numExtSems, CUstream stream) {
    HOOK_TRACE_PROFILE("cuWaitExternalSemaphoresAsync");
    using func_ptr = CUresult (*)(const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *, unsigned int, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuWaitExternalSemaphoresAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(extSemArray, paramsArray, numExtSems, stream);
}

CUresult cuDestroyExternalSemaphore(CUexternalSemaphore extSem) {
    HOOK_TRACE_PROFILE("cuDestroyExternalSemaphore");
    using func_ptr = CUresult (*)(CUexternalSemaphore);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDestroyExternalSemaphore"));
    HOOK_CHECK(func_entry);
    return func_entry(extSem);
}

CUresult cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitValue32");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitValue32"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWaitValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitValue64");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitValue64"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWriteValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWriteValue32");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWriteValue32"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWriteValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWriteValue64");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWriteValue64"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamBatchMemOp");
    using func_ptr = CUresult (*)(CUstream, unsigned int, CUstreamBatchMemOpParams *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBatchMemOp"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, count, paramArray, flags);
}

CUresult cuFuncGetAttribute(int * pi, CUfunction_attribute attrib, CUfunction hfunc) {
    HOOK_TRACE_PROFILE("cuFuncGetAttribute");
    using func_ptr = CUresult (*)(int *, CUfunction_attribute, CUfunction);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(pi, attrib, hfunc);
}

CUresult cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value) {
    HOOK_TRACE_PROFILE("cuFuncSetAttribute");
    using func_ptr = CUresult (*)(CUfunction, CUfunction_attribute, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, attrib, value);
}

CUresult cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config) {
    HOOK_TRACE_PROFILE("cuFuncSetCacheConfig");
    using func_ptr = CUresult (*)(CUfunction, CUfunc_cache);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncSetCacheConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, config);
}

CUresult cuFuncGetModule(CUmodule * hmod, CUfunction hfunc) {
    HOOK_TRACE_PROFILE("cuFuncGetModule");
    using func_ptr = CUresult (*)(CUmodule *, CUfunction);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncGetModule"));
    HOOK_CHECK(func_entry);
    return func_entry(hmod, hfunc);
}

CUresult cuFuncGetName(const char * * name, CUfunction hfunc) {
    HOOK_TRACE_PROFILE("cuFuncGetName");
    using func_ptr = CUresult (*)(const char * *, CUfunction);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncGetName"));
    HOOK_CHECK(func_entry);
    return func_entry(name, hfunc);
}

CUresult cuFuncGetParamInfo(CUfunction func, size_t paramIndex, size_t * paramOffset, size_t * paramSize) {
    HOOK_TRACE_PROFILE("cuFuncGetParamInfo");
    using func_ptr = CUresult (*)(CUfunction, size_t, size_t *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncGetParamInfo"));
    HOOK_CHECK(func_entry);
    return func_entry(func, paramIndex, paramOffset, paramSize);
}

CUresult cuFuncIsLoaded(CUfunctionLoadingState * state, CUfunction function) {
    HOOK_TRACE_PROFILE("cuFuncIsLoaded");
    using func_ptr = CUresult (*)(CUfunctionLoadingState *, CUfunction);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncIsLoaded"));
    HOOK_CHECK(func_entry);
    return func_entry(state, function);
}

CUresult cuFuncLoad(CUfunction function) {
    HOOK_TRACE_PROFILE("cuFuncLoad");
    using func_ptr = CUresult (*)(CUfunction);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncLoad"));
    HOOK_CHECK(func_entry);
    return func_entry(function);
}

CUresult cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra) {
    HOOK_TRACE_PROFILE("cuLaunchKernel");
    using func_ptr = CUresult (*)(CUfunction, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CUstream, void * *, void * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchKernel"));
    HOOK_CHECK(func_entry);
    return func_entry(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams, extra);
}

CUresult cuLaunchKernelEx(const CUlaunchConfig * config, CUfunction f, void * * kernelParams, void * * extra) {
    HOOK_TRACE_PROFILE("cuLaunchKernelEx");
    using func_ptr = CUresult (*)(const CUlaunchConfig *, CUfunction, void * *, void * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchKernelEx"));
    HOOK_CHECK(func_entry);
    return func_entry(config, f, kernelParams, extra);
}

CUresult cuLaunchCooperativeKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams) {
    HOOK_TRACE_PROFILE("cuLaunchCooperativeKernel");
    using func_ptr = CUresult (*)(CUfunction, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CUstream, void * *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchCooperativeKernel"));
    HOOK_CHECK(func_entry);
    return func_entry(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams);
}

CUresult cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS * launchParamsList, unsigned int numDevices, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuLaunchCooperativeKernelMultiDevice");
    using func_ptr = CUresult (*)(CUDA_LAUNCH_PARAMS *, unsigned int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchCooperativeKernelMultiDevice"));
    HOOK_CHECK(func_entry);
    return func_entry(launchParamsList, numDevices, flags);
}

CUresult cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void * userData) {
    HOOK_TRACE_PROFILE("cuLaunchHostFunc");
    using func_ptr = CUresult (*)(CUstream, CUhostFn, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchHostFunc"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, fn, userData);
}

CUresult cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z) {
    HOOK_TRACE_PROFILE("cuFuncSetBlockShape");
    using func_ptr = CUresult (*)(CUfunction, int, int, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncSetBlockShape"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, x, y, z);
}

CUresult cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes) {
    HOOK_TRACE_PROFILE("cuFuncSetSharedSize");
    using func_ptr = CUresult (*)(CUfunction, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncSetSharedSize"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, bytes);
}

CUresult cuParamSetSize(CUfunction hfunc, unsigned int numbytes) {
    HOOK_TRACE_PROFILE("cuParamSetSize");
    using func_ptr = CUresult (*)(CUfunction, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuParamSetSize"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, numbytes);
}

CUresult cuParamSeti(CUfunction hfunc, int offset, unsigned int value) {
    HOOK_TRACE_PROFILE("cuParamSeti");
    using func_ptr = CUresult (*)(CUfunction, int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuParamSeti"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, offset, value);
}

CUresult cuParamSetf(CUfunction hfunc, int offset, float value) {
    HOOK_TRACE_PROFILE("cuParamSetf");
    using func_ptr = CUresult (*)(CUfunction, int, float);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuParamSetf"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, offset, value);
}

CUresult cuParamSetv(CUfunction hfunc, int offset, void * ptr, unsigned int numbytes) {
    HOOK_TRACE_PROFILE("cuParamSetv");
    using func_ptr = CUresult (*)(CUfunction, int, void *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuParamSetv"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, offset, ptr, numbytes);
}

CUresult cuLaunch(CUfunction f) {
    HOOK_TRACE_PROFILE("cuLaunch");
    using func_ptr = CUresult (*)(CUfunction);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunch"));
    HOOK_CHECK(func_entry);
    return func_entry(f);
}

CUresult cuLaunchGrid(CUfunction f, int grid_width, int grid_height) {
    HOOK_TRACE_PROFILE("cuLaunchGrid");
    using func_ptr = CUresult (*)(CUfunction, int, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchGrid"));
    HOOK_CHECK(func_entry);
    return func_entry(f, grid_width, grid_height);
}

CUresult cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuLaunchGridAsync");
    using func_ptr = CUresult (*)(CUfunction, int, int, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuLaunchGridAsync"));
    HOOK_CHECK(func_entry);
    return func_entry(f, grid_width, grid_height, hStream);
}

CUresult cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuParamSetTexRef");
    using func_ptr = CUresult (*)(CUfunction, int, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuParamSetTexRef"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, texunit, hTexRef);
}

CUresult cuFuncSetSharedMemConfig(CUfunction hfunc, CUsharedconfig config) {
    HOOK_TRACE_PROFILE("cuFuncSetSharedMemConfig");
    using func_ptr = CUresult (*)(CUfunction, CUsharedconfig);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuFuncSetSharedMemConfig"));
    HOOK_CHECK(func_entry);
    return func_entry(hfunc, config);
}

CUresult cuGraphCreate(CUgraph * phGraph, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuGraphCreate");
    using func_ptr = CUresult (*)(CUgraph *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraph, flags);
}

CUresult cuGraphAddKernelNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddKernelNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_KERNEL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddKernelNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphKernelNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_KERNEL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphKernelNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphKernelNodeSetParams(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphKernelNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_KERNEL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphKernelNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphAddMemcpyNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_MEMCPY3D * copyParams, CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuGraphAddMemcpyNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_MEMCPY3D *, CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddMemcpyNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, copyParams, ctx);
}

CUresult cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphMemcpyNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_MEMCPY3D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphMemcpyNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphMemcpyNodeSetParams(CUgraphNode hNode, const CUDA_MEMCPY3D * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphMemcpyNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_MEMCPY3D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphMemcpyNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphAddMemsetNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS * memsetParams, CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuGraphAddMemsetNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_MEMSET_NODE_PARAMS *, CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddMemsetNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, memsetParams, ctx);
}

CUresult cuGraphMemsetNodeGetParams(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphMemsetNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_MEMSET_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphMemsetNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphMemsetNodeSetParams(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphMemsetNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_MEMSET_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphMemsetNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphAddHostNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddHostNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_HOST_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddHostNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphHostNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_HOST_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphHostNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphHostNodeSetParams(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphHostNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_HOST_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphHostNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphAddChildGraphNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, CUgraph childGraph) {
    HOOK_TRACE_PROFILE("cuGraphAddChildGraphNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUgraph);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddChildGraphNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, childGraph);
}

CUresult cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph * phGraph) {
    HOOK_TRACE_PROFILE("cuGraphChildGraphNodeGetGraph");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraph *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphChildGraphNodeGetGraph"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, phGraph);
}

CUresult cuGraphAddEmptyNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphAddEmptyNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddEmptyNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies);
}

CUresult cuGraphAddEventRecordNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, CUevent event) {
    HOOK_TRACE_PROFILE("cuGraphAddEventRecordNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddEventRecordNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, event);
}

CUresult cuGraphEventRecordNodeGetEvent(CUgraphNode hNode, CUevent * event_out) {
    HOOK_TRACE_PROFILE("cuGraphEventRecordNodeGetEvent");
    using func_ptr = CUresult (*)(CUgraphNode, CUevent *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphEventRecordNodeGetEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, event_out);
}

CUresult cuGraphEventRecordNodeSetEvent(CUgraphNode hNode, CUevent event) {
    HOOK_TRACE_PROFILE("cuGraphEventRecordNodeSetEvent");
    using func_ptr = CUresult (*)(CUgraphNode, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphEventRecordNodeSetEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, event);
}

CUresult cuGraphAddEventWaitNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, CUevent event) {
    HOOK_TRACE_PROFILE("cuGraphAddEventWaitNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddEventWaitNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, event);
}

CUresult cuGraphEventWaitNodeGetEvent(CUgraphNode hNode, CUevent * event_out) {
    HOOK_TRACE_PROFILE("cuGraphEventWaitNodeGetEvent");
    using func_ptr = CUresult (*)(CUgraphNode, CUevent *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphEventWaitNodeGetEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, event_out);
}

CUresult cuGraphEventWaitNodeSetEvent(CUgraphNode hNode, CUevent event) {
    HOOK_TRACE_PROFILE("cuGraphEventWaitNodeSetEvent");
    using func_ptr = CUresult (*)(CUgraphNode, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphEventWaitNodeSetEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, event);
}

CUresult cuGraphAddExternalSemaphoresSignalNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddExternalSemaphoresSignalNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddExternalSemaphoresSignalNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphExternalSemaphoresSignalNodeGetParams(CUgraphNode hNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS * params_out) {
    HOOK_TRACE_PROFILE("cuGraphExternalSemaphoresSignalNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExternalSemaphoresSignalNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, params_out);
}

CUresult cuGraphExternalSemaphoresSignalNodeSetParams(CUgraphNode hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExternalSemaphoresSignalNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExternalSemaphoresSignalNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphAddExternalSemaphoresWaitNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_EXT_SEM_WAIT_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddExternalSemaphoresWaitNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddExternalSemaphoresWaitNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphExternalSemaphoresWaitNodeGetParams(CUgraphNode hNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS * params_out) {
    HOOK_TRACE_PROFILE("cuGraphExternalSemaphoresWaitNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExternalSemaphoresWaitNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, params_out);
}

CUresult cuGraphExternalSemaphoresWaitNodeSetParams(CUgraphNode hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExternalSemaphoresWaitNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExternalSemaphoresWaitNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphAddBatchMemOpNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, const CUDA_BATCH_MEM_OP_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddBatchMemOpNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_BATCH_MEM_OP_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddBatchMemOpNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphBatchMemOpNodeGetParams(CUgraphNode hNode, CUDA_BATCH_MEM_OP_NODE_PARAMS * nodeParams_out) {
    HOOK_TRACE_PROFILE("cuGraphBatchMemOpNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_BATCH_MEM_OP_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphBatchMemOpNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams_out);
}

CUresult cuGraphBatchMemOpNodeSetParams(CUgraphNode hNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphBatchMemOpNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphBatchMemOpNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphExecBatchMemOpNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExecBatchMemOpNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecBatchMemOpNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, nodeParams);
}

CUresult cuGraphAddMemAllocNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, CUDA_MEM_ALLOC_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddMemAllocNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUDA_MEM_ALLOC_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddMemAllocNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphMemAllocNodeGetParams(CUgraphNode hNode, CUDA_MEM_ALLOC_NODE_PARAMS * params_out) {
    HOOK_TRACE_PROFILE("cuGraphMemAllocNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUDA_MEM_ALLOC_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphMemAllocNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, params_out);
}

CUresult cuGraphAddMemFreeNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, CUdeviceptr dptr) {
    HOOK_TRACE_PROFILE("cuGraphAddMemFreeNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUdeviceptr);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddMemFreeNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, dptr);
}

CUresult cuGraphMemFreeNodeGetParams(CUgraphNode hNode, CUdeviceptr * dptr_out) {
    HOOK_TRACE_PROFILE("cuGraphMemFreeNodeGetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUdeviceptr *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphMemFreeNodeGetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, dptr_out);
}

CUresult cuDeviceGraphMemTrim(CUdevice device) {
    HOOK_TRACE_PROFILE("cuDeviceGraphMemTrim");
    using func_ptr = CUresult (*)(CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGraphMemTrim"));
    HOOK_CHECK(func_entry);
    return func_entry(device);
}

CUresult cuDeviceGetGraphMemAttribute(CUdevice device, CUgraphMem_attribute attr, void * value) {
    HOOK_TRACE_PROFILE("cuDeviceGetGraphMemAttribute");
    using func_ptr = CUresult (*)(CUdevice, CUgraphMem_attribute, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetGraphMemAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(device, attr, value);
}

CUresult cuDeviceSetGraphMemAttribute(CUdevice device, CUgraphMem_attribute attr, void * value) {
    HOOK_TRACE_PROFILE("cuDeviceSetGraphMemAttribute");
    using func_ptr = CUresult (*)(CUdevice, CUgraphMem_attribute, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceSetGraphMemAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(device, attr, value);
}

CUresult cuGraphClone(CUgraph * phGraphClone, CUgraph originalGraph) {
    HOOK_TRACE_PROFILE("cuGraphClone");
    using func_ptr = CUresult (*)(CUgraph *, CUgraph);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphClone"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphClone, originalGraph);
}

CUresult cuGraphNodeFindInClone(CUgraphNode * phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph) {
    HOOK_TRACE_PROFILE("cuGraphNodeFindInClone");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraphNode, CUgraph);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeFindInClone"));
    HOOK_CHECK(func_entry);
    return func_entry(phNode, hOriginalNode, hClonedGraph);
}

CUresult cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType * type) {
    HOOK_TRACE_PROFILE("cuGraphNodeGetType");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNodeType *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeGetType"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, type);
}

CUresult cuGraphGetNodes(CUgraph hGraph, CUgraphNode * nodes, size_t * numNodes) {
    HOOK_TRACE_PROFILE("cuGraphGetNodes");
    using func_ptr = CUresult (*)(CUgraph, CUgraphNode *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphGetNodes"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, nodes, numNodes);
}

CUresult cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode * rootNodes, size_t * numRootNodes) {
    HOOK_TRACE_PROFILE("cuGraphGetRootNodes");
    using func_ptr = CUresult (*)(CUgraph, CUgraphNode *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphGetRootNodes"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, rootNodes, numRootNodes);
}

CUresult cuGraphGetEdges(CUgraph hGraph, CUgraphNode * from, CUgraphNode * to, size_t * numEdges) {
    HOOK_TRACE_PROFILE("cuGraphGetEdges");
    using func_ptr = CUresult (*)(CUgraph, CUgraphNode *, CUgraphNode *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphGetEdges"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, from, to, numEdges);
}

CUresult cuGraphGetEdges_v2(CUgraph hGraph, CUgraphNode * from, CUgraphNode * to, CUgraphEdgeData * edgeData, size_t * numEdges) {
    HOOK_TRACE_PROFILE("cuGraphGetEdges_v2");
    using func_ptr = CUresult (*)(CUgraph, CUgraphNode *, CUgraphNode *, CUgraphEdgeData *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphGetEdges_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, from, to, edgeData, numEdges);
}

CUresult cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode * dependencies, size_t * numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphNodeGetDependencies");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNode *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeGetDependencies"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, dependencies, numDependencies);
}

CUresult cuGraphNodeGetDependencies_v2(CUgraphNode hNode, CUgraphNode * dependencies, CUgraphEdgeData * edgeData, size_t * numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphNodeGetDependencies_v2");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNode *, CUgraphEdgeData *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeGetDependencies_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, dependencies, edgeData, numDependencies);
}

CUresult cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode * dependentNodes, size_t * numDependentNodes) {
    HOOK_TRACE_PROFILE("cuGraphNodeGetDependentNodes");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNode *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeGetDependentNodes"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, dependentNodes, numDependentNodes);
}

CUresult cuGraphNodeGetDependentNodes_v2(CUgraphNode hNode, CUgraphNode * dependentNodes, CUgraphEdgeData * edgeData, size_t * numDependentNodes) {
    HOOK_TRACE_PROFILE("cuGraphNodeGetDependentNodes_v2");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNode *, CUgraphEdgeData *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeGetDependentNodes_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, dependentNodes, edgeData, numDependentNodes);
}

CUresult cuGraphAddDependencies(CUgraph hGraph, const CUgraphNode * from, const CUgraphNode * to, size_t numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphAddDependencies");
    using func_ptr = CUresult (*)(CUgraph, const CUgraphNode *, const CUgraphNode *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddDependencies"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, from, to, numDependencies);
}

CUresult cuGraphAddDependencies_v2(CUgraph hGraph, const CUgraphNode * from, const CUgraphNode * to, const CUgraphEdgeData * edgeData, size_t numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphAddDependencies_v2");
    using func_ptr = CUresult (*)(CUgraph, const CUgraphNode *, const CUgraphNode *, const CUgraphEdgeData *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddDependencies_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, from, to, edgeData, numDependencies);
}

CUresult cuGraphRemoveDependencies(CUgraph hGraph, const CUgraphNode * from, const CUgraphNode * to, size_t numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphRemoveDependencies");
    using func_ptr = CUresult (*)(CUgraph, const CUgraphNode *, const CUgraphNode *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphRemoveDependencies"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, from, to, numDependencies);
}

CUresult cuGraphRemoveDependencies_v2(CUgraph hGraph, const CUgraphNode * from, const CUgraphNode * to, const CUgraphEdgeData * edgeData, size_t numDependencies) {
    HOOK_TRACE_PROFILE("cuGraphRemoveDependencies_v2");
    using func_ptr = CUresult (*)(CUgraph, const CUgraphNode *, const CUgraphNode *, const CUgraphEdgeData *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphRemoveDependencies_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, from, to, edgeData, numDependencies);
}

CUresult cuGraphDestroyNode(CUgraphNode hNode) {
    HOOK_TRACE_PROFILE("cuGraphDestroyNode");
    using func_ptr = CUresult (*)(CUgraphNode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphDestroyNode"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode);
}

CUresult cuGraphInstantiate(CUgraphExec * phGraphExec, CUgraph hGraph, unsigned long long flags) {
    HOOK_TRACE_PROFILE("cuGraphInstantiate");
    using func_ptr = CUresult (*)(CUgraphExec *, CUgraph, unsigned long long);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphInstantiate"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphExec, hGraph, flags);
}

CUresult cuGraphInstantiateWithParams(CUgraphExec * phGraphExec, CUgraph hGraph, CUDA_GRAPH_INSTANTIATE_PARAMS * instantiateParams) {
    HOOK_TRACE_PROFILE("cuGraphInstantiateWithParams");
    using func_ptr = CUresult (*)(CUgraphExec *, CUgraph, CUDA_GRAPH_INSTANTIATE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphInstantiateWithParams"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphExec, hGraph, instantiateParams);
}

CUresult cuGraphExecGetFlags(CUgraphExec hGraphExec, cuuint64_t * flags) {
    HOOK_TRACE_PROFILE("cuGraphExecGetFlags");
    using func_ptr = CUresult (*)(CUgraphExec, cuuint64_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecGetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, flags);
}

CUresult cuGraphExecKernelNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExecKernelNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_KERNEL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecKernelNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, nodeParams);
}

CUresult cuGraphExecMemcpyNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_MEMCPY3D * copyParams, CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuGraphExecMemcpyNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_MEMCPY3D *, CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecMemcpyNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, copyParams, ctx);
}

CUresult cuGraphExecMemsetNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS * memsetParams, CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuGraphExecMemsetNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_MEMSET_NODE_PARAMS *, CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecMemsetNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, memsetParams, ctx);
}

CUresult cuGraphExecHostNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExecHostNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_HOST_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecHostNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, nodeParams);
}

CUresult cuGraphExecChildGraphNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, CUgraph childGraph) {
    HOOK_TRACE_PROFILE("cuGraphExecChildGraphNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, CUgraph);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecChildGraphNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, childGraph);
}

CUresult cuGraphExecEventRecordNodeSetEvent(CUgraphExec hGraphExec, CUgraphNode hNode, CUevent event) {
    HOOK_TRACE_PROFILE("cuGraphExecEventRecordNodeSetEvent");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecEventRecordNodeSetEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, event);
}

CUresult cuGraphExecEventWaitNodeSetEvent(CUgraphExec hGraphExec, CUgraphNode hNode, CUevent event) {
    HOOK_TRACE_PROFILE("cuGraphExecEventWaitNodeSetEvent");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecEventWaitNodeSetEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, event);
}

CUresult cuGraphExecExternalSemaphoresSignalNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExecExternalSemaphoresSignalNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecExternalSemaphoresSignalNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, nodeParams);
}

CUresult cuGraphExecExternalSemaphoresWaitNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExecExternalSemaphoresWaitNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecExternalSemaphoresWaitNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, nodeParams);
}

CUresult cuGraphNodeSetEnabled(CUgraphExec hGraphExec, CUgraphNode hNode, unsigned int isEnabled) {
    HOOK_TRACE_PROFILE("cuGraphNodeSetEnabled");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeSetEnabled"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, isEnabled);
}

CUresult cuGraphNodeGetEnabled(CUgraphExec hGraphExec, CUgraphNode hNode, unsigned int * isEnabled) {
    HOOK_TRACE_PROFILE("cuGraphNodeGetEnabled");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, unsigned int *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeGetEnabled"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, isEnabled);
}

CUresult cuGraphUpload(CUgraphExec hGraphExec, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuGraphUpload");
    using func_ptr = CUresult (*)(CUgraphExec, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphUpload"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hStream);
}

CUresult cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuGraphLaunch");
    using func_ptr = CUresult (*)(CUgraphExec, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphLaunch"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hStream);
}

CUresult cuGraphExecDestroy(CUgraphExec hGraphExec) {
    HOOK_TRACE_PROFILE("cuGraphExecDestroy");
    using func_ptr = CUresult (*)(CUgraphExec);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec);
}

CUresult cuGraphDestroy(CUgraph hGraph) {
    HOOK_TRACE_PROFILE("cuGraphDestroy");
    using func_ptr = CUresult (*)(CUgraph);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph);
}

CUresult cuGraphExecUpdate(CUgraphExec hGraphExec, CUgraph hGraph, CUgraphExecUpdateResultInfo * resultInfo) {
    HOOK_TRACE_PROFILE("cuGraphExecUpdate");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraph, CUgraphExecUpdateResultInfo *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecUpdate"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hGraph, resultInfo);
}

CUresult cuGraphKernelNodeCopyAttributes(CUgraphNode dst, CUgraphNode src) {
    HOOK_TRACE_PROFILE("cuGraphKernelNodeCopyAttributes");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphKernelNodeCopyAttributes"));
    HOOK_CHECK(func_entry);
    return func_entry(dst, src);
}

CUresult cuGraphKernelNodeGetAttribute(CUgraphNode hNode, CUkernelNodeAttrID attr, CUkernelNodeAttrValue * value_out) {
    HOOK_TRACE_PROFILE("cuGraphKernelNodeGetAttribute");
    using func_ptr = CUresult (*)(CUgraphNode, CUkernelNodeAttrID, CUkernelNodeAttrValue *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphKernelNodeGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, attr, value_out);
}

CUresult cuGraphKernelNodeSetAttribute(CUgraphNode hNode, CUkernelNodeAttrID attr, const CUkernelNodeAttrValue * value) {
    HOOK_TRACE_PROFILE("cuGraphKernelNodeSetAttribute");
    using func_ptr = CUresult (*)(CUgraphNode, CUkernelNodeAttrID, const CUkernelNodeAttrValue *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphKernelNodeSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, attr, value);
}

CUresult cuGraphDebugDotPrint(CUgraph hGraph, const char * path, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuGraphDebugDotPrint");
    using func_ptr = CUresult (*)(CUgraph, const char *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphDebugDotPrint"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraph, path, flags);
}

CUresult cuUserObjectCreate(CUuserObject * object_out, void * ptr, CUhostFn destroy, unsigned int initialRefcount, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuUserObjectCreate");
    using func_ptr = CUresult (*)(CUuserObject *, void *, CUhostFn, unsigned int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuUserObjectCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(object_out, ptr, destroy, initialRefcount, flags);
}

CUresult cuUserObjectRetain(CUuserObject object, unsigned int count) {
    HOOK_TRACE_PROFILE("cuUserObjectRetain");
    using func_ptr = CUresult (*)(CUuserObject, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuUserObjectRetain"));
    HOOK_CHECK(func_entry);
    return func_entry(object, count);
}

CUresult cuUserObjectRelease(CUuserObject object, unsigned int count) {
    HOOK_TRACE_PROFILE("cuUserObjectRelease");
    using func_ptr = CUresult (*)(CUuserObject, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuUserObjectRelease"));
    HOOK_CHECK(func_entry);
    return func_entry(object, count);
}

CUresult cuGraphRetainUserObject(CUgraph graph, CUuserObject object, unsigned int count, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuGraphRetainUserObject");
    using func_ptr = CUresult (*)(CUgraph, CUuserObject, unsigned int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphRetainUserObject"));
    HOOK_CHECK(func_entry);
    return func_entry(graph, object, count, flags);
}

CUresult cuGraphReleaseUserObject(CUgraph graph, CUuserObject object, unsigned int count) {
    HOOK_TRACE_PROFILE("cuGraphReleaseUserObject");
    using func_ptr = CUresult (*)(CUgraph, CUuserObject, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphReleaseUserObject"));
    HOOK_CHECK(func_entry);
    return func_entry(graph, object, count);
}

CUresult cuGraphAddNode(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, size_t numDependencies, CUgraphNodeParams * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddNode");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUgraphNodeParams *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddNode"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
}

CUresult cuGraphAddNode_v2(CUgraphNode * phGraphNode, CUgraph hGraph, const CUgraphNode * dependencies, const CUgraphEdgeData * dependencyData, size_t numDependencies, CUgraphNodeParams * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphAddNode_v2");
    using func_ptr = CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, const CUgraphEdgeData *, size_t, CUgraphNodeParams *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphAddNode_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphNode, hGraph, dependencies, dependencyData, numDependencies, nodeParams);
}

CUresult cuGraphNodeSetParams(CUgraphNode hNode, CUgraphNodeParams * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphNode, CUgraphNodeParams *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hNode, nodeParams);
}

CUresult cuGraphExecNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, CUgraphNodeParams * nodeParams) {
    HOOK_TRACE_PROFILE("cuGraphExecNodeSetParams");
    using func_ptr = CUresult (*)(CUgraphExec, CUgraphNode, CUgraphNodeParams *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphExecNodeSetParams"));
    HOOK_CHECK(func_entry);
    return func_entry(hGraphExec, hNode, nodeParams);
}

CUresult cuGraphConditionalHandleCreate(CUgraphConditionalHandle * pHandle_out, CUgraph hGraph, CUcontext ctx, unsigned int defaultLaunchValue, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuGraphConditionalHandleCreate");
    using func_ptr = CUresult (*)(CUgraphConditionalHandle *, CUgraph, CUcontext, unsigned int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphConditionalHandleCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pHandle_out, hGraph, ctx, defaultLaunchValue, flags);
}

CUresult cuOccupancyMaxActiveBlocksPerMultiprocessor(int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize) {
    HOOK_TRACE_PROFILE("cuOccupancyMaxActiveBlocksPerMultiprocessor");
    using func_ptr = CUresult (*)(int *, CUfunction, int, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyMaxActiveBlocksPerMultiprocessor"));
    HOOK_CHECK(func_entry);
    return func_entry(numBlocks, func, blockSize, dynamicSMemSize);
}

CUresult cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int * numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
    using func_ptr = CUresult (*)(int *, CUfunction, int, size_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(numBlocks, func, blockSize, dynamicSMemSize, flags);
}

CUresult cuOccupancyMaxPotentialBlockSize(int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit) {
    HOOK_TRACE_PROFILE("cuOccupancyMaxPotentialBlockSize");
    using func_ptr = CUresult (*)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyMaxPotentialBlockSize"));
    HOOK_CHECK(func_entry);
    return func_entry(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit);
}

CUresult cuOccupancyMaxPotentialBlockSizeWithFlags(int * minGridSize, int * blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuOccupancyMaxPotentialBlockSizeWithFlags");
    using func_ptr = CUresult (*)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyMaxPotentialBlockSizeWithFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit, flags);
}

CUresult cuOccupancyAvailableDynamicSMemPerBlock(size_t * dynamicSmemSize, CUfunction func, int numBlocks, int blockSize) {
    HOOK_TRACE_PROFILE("cuOccupancyAvailableDynamicSMemPerBlock");
    using func_ptr = CUresult (*)(size_t *, CUfunction, int, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyAvailableDynamicSMemPerBlock"));
    HOOK_CHECK(func_entry);
    return func_entry(dynamicSmemSize, func, numBlocks, blockSize);
}

CUresult cuOccupancyMaxPotentialClusterSize(int * clusterSize, CUfunction func, const CUlaunchConfig * config) {
    HOOK_TRACE_PROFILE("cuOccupancyMaxPotentialClusterSize");
    using func_ptr = CUresult (*)(int *, CUfunction, const CUlaunchConfig *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyMaxPotentialClusterSize"));
    HOOK_CHECK(func_entry);
    return func_entry(clusterSize, func, config);
}

CUresult cuOccupancyMaxActiveClusters(int * numClusters, CUfunction func, const CUlaunchConfig * config) {
    HOOK_TRACE_PROFILE("cuOccupancyMaxActiveClusters");
    using func_ptr = CUresult (*)(int *, CUfunction, const CUlaunchConfig *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuOccupancyMaxActiveClusters"));
    HOOK_CHECK(func_entry);
    return func_entry(numClusters, func, config);
}

CUresult cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuTexRefSetArray");
    using func_ptr = CUresult (*)(CUtexref, CUarray, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetArray"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, hArray, Flags);
}

CUresult cuTexRefSetMipmappedArray(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuTexRefSetMipmappedArray");
    using func_ptr = CUresult (*)(CUtexref, CUmipmappedArray, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetMipmappedArray"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, hMipmappedArray, Flags);
}

CUresult cuTexRefSetAddress(size_t * ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes) {
    HOOK_TRACE_PROFILE("cuTexRefSetAddress");
    using func_ptr = CUresult (*)(size_t *, CUtexref, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetAddress"));
    HOOK_CHECK(func_entry);
    return func_entry(ByteOffset, hTexRef, dptr, bytes);
}

CUresult cuTexRefSetAddress2D(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch) {
    HOOK_TRACE_PROFILE("cuTexRefSetAddress2D");
    using func_ptr = CUresult (*)(CUtexref, const CUDA_ARRAY_DESCRIPTOR *, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetAddress2D"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, desc, dptr, Pitch);
}

CUresult cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents) {
    HOOK_TRACE_PROFILE("cuTexRefSetFormat");
    using func_ptr = CUresult (*)(CUtexref, CUarray_format, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetFormat"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, fmt, NumPackedComponents);
}

CUresult cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am) {
    HOOK_TRACE_PROFILE("cuTexRefSetAddressMode");
    using func_ptr = CUresult (*)(CUtexref, int, CUaddress_mode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetAddressMode"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, dim, am);
}

CUresult cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm) {
    HOOK_TRACE_PROFILE("cuTexRefSetFilterMode");
    using func_ptr = CUresult (*)(CUtexref, CUfilter_mode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetFilterMode"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, fm);
}

CUresult cuTexRefSetMipmapFilterMode(CUtexref hTexRef, CUfilter_mode fm) {
    HOOK_TRACE_PROFILE("cuTexRefSetMipmapFilterMode");
    using func_ptr = CUresult (*)(CUtexref, CUfilter_mode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetMipmapFilterMode"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, fm);
}

CUresult cuTexRefSetMipmapLevelBias(CUtexref hTexRef, float bias) {
    HOOK_TRACE_PROFILE("cuTexRefSetMipmapLevelBias");
    using func_ptr = CUresult (*)(CUtexref, float);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetMipmapLevelBias"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, bias);
}

CUresult cuTexRefSetMipmapLevelClamp(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp) {
    HOOK_TRACE_PROFILE("cuTexRefSetMipmapLevelClamp");
    using func_ptr = CUresult (*)(CUtexref, float, float);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetMipmapLevelClamp"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, minMipmapLevelClamp, maxMipmapLevelClamp);
}

CUresult cuTexRefSetMaxAnisotropy(CUtexref hTexRef, unsigned int maxAniso) {
    HOOK_TRACE_PROFILE("cuTexRefSetMaxAnisotropy");
    using func_ptr = CUresult (*)(CUtexref, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetMaxAnisotropy"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, maxAniso);
}

CUresult cuTexRefSetBorderColor(CUtexref hTexRef, float * pBorderColor) {
    HOOK_TRACE_PROFILE("cuTexRefSetBorderColor");
    using func_ptr = CUresult (*)(CUtexref, float *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetBorderColor"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, pBorderColor);
}

CUresult cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuTexRefSetFlags");
    using func_ptr = CUresult (*)(CUtexref, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, Flags);
}

CUresult cuTexRefGetAddress(CUdeviceptr * pdptr, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetAddress");
    using func_ptr = CUresult (*)(CUdeviceptr *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetAddress"));
    HOOK_CHECK(func_entry);
    return func_entry(pdptr, hTexRef);
}

CUresult cuTexRefGetArray(CUarray * phArray, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetArray");
    using func_ptr = CUresult (*)(CUarray *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetArray"));
    HOOK_CHECK(func_entry);
    return func_entry(phArray, hTexRef);
}

CUresult cuTexRefGetMipmappedArray(CUmipmappedArray * phMipmappedArray, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetMipmappedArray");
    using func_ptr = CUresult (*)(CUmipmappedArray *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetMipmappedArray"));
    HOOK_CHECK(func_entry);
    return func_entry(phMipmappedArray, hTexRef);
}

CUresult cuTexRefGetAddressMode(CUaddress_mode * pam, CUtexref hTexRef, int dim) {
    HOOK_TRACE_PROFILE("cuTexRefGetAddressMode");
    using func_ptr = CUresult (*)(CUaddress_mode *, CUtexref, int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetAddressMode"));
    HOOK_CHECK(func_entry);
    return func_entry(pam, hTexRef, dim);
}

CUresult cuTexRefGetFilterMode(CUfilter_mode * pfm, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetFilterMode");
    using func_ptr = CUresult (*)(CUfilter_mode *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetFilterMode"));
    HOOK_CHECK(func_entry);
    return func_entry(pfm, hTexRef);
}

CUresult cuTexRefGetFormat(CUarray_format * pFormat, int * pNumChannels, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetFormat");
    using func_ptr = CUresult (*)(CUarray_format *, int *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetFormat"));
    HOOK_CHECK(func_entry);
    return func_entry(pFormat, pNumChannels, hTexRef);
}

CUresult cuTexRefGetMipmapFilterMode(CUfilter_mode * pfm, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetMipmapFilterMode");
    using func_ptr = CUresult (*)(CUfilter_mode *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetMipmapFilterMode"));
    HOOK_CHECK(func_entry);
    return func_entry(pfm, hTexRef);
}

CUresult cuTexRefGetMipmapLevelBias(float * pbias, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetMipmapLevelBias");
    using func_ptr = CUresult (*)(float *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetMipmapLevelBias"));
    HOOK_CHECK(func_entry);
    return func_entry(pbias, hTexRef);
}

CUresult cuTexRefGetMipmapLevelClamp(float * pminMipmapLevelClamp, float * pmaxMipmapLevelClamp, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetMipmapLevelClamp");
    using func_ptr = CUresult (*)(float *, float *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetMipmapLevelClamp"));
    HOOK_CHECK(func_entry);
    return func_entry(pminMipmapLevelClamp, pmaxMipmapLevelClamp, hTexRef);
}

CUresult cuTexRefGetMaxAnisotropy(int * pmaxAniso, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetMaxAnisotropy");
    using func_ptr = CUresult (*)(int *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetMaxAnisotropy"));
    HOOK_CHECK(func_entry);
    return func_entry(pmaxAniso, hTexRef);
}

CUresult cuTexRefGetBorderColor(float * pBorderColor, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetBorderColor");
    using func_ptr = CUresult (*)(float *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetBorderColor"));
    HOOK_CHECK(func_entry);
    return func_entry(pBorderColor, hTexRef);
}

CUresult cuTexRefGetFlags(unsigned int * pFlags, CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefGetFlags");
    using func_ptr = CUresult (*)(unsigned int *, CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefGetFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(pFlags, hTexRef);
}

CUresult cuTexRefCreate(CUtexref * pTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefCreate");
    using func_ptr = CUresult (*)(CUtexref *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pTexRef);
}

CUresult cuTexRefDestroy(CUtexref hTexRef) {
    HOOK_TRACE_PROFILE("cuTexRefDestroy");
    using func_ptr = CUresult (*)(CUtexref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef);
}

CUresult cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuSurfRefSetArray");
    using func_ptr = CUresult (*)(CUsurfref, CUarray, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuSurfRefSetArray"));
    HOOK_CHECK(func_entry);
    return func_entry(hSurfRef, hArray, Flags);
}

CUresult cuSurfRefGetArray(CUarray * phArray, CUsurfref hSurfRef) {
    HOOK_TRACE_PROFILE("cuSurfRefGetArray");
    using func_ptr = CUresult (*)(CUarray *, CUsurfref);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuSurfRefGetArray"));
    HOOK_CHECK(func_entry);
    return func_entry(phArray, hSurfRef);
}

CUresult cuTexObjectCreate(CUtexObject * pTexObject, const CUDA_RESOURCE_DESC * pResDesc, const CUDA_TEXTURE_DESC * pTexDesc, const CUDA_RESOURCE_VIEW_DESC * pResViewDesc) {
    HOOK_TRACE_PROFILE("cuTexObjectCreate");
    using func_ptr = CUresult (*)(CUtexObject *, const CUDA_RESOURCE_DESC *, const CUDA_TEXTURE_DESC *, const CUDA_RESOURCE_VIEW_DESC *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexObjectCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pTexObject, pResDesc, pTexDesc, pResViewDesc);
}

CUresult cuTexObjectDestroy(CUtexObject texObject) {
    HOOK_TRACE_PROFILE("cuTexObjectDestroy");
    using func_ptr = CUresult (*)(CUtexObject);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexObjectDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(texObject);
}

CUresult cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC * pResDesc, CUtexObject texObject) {
    HOOK_TRACE_PROFILE("cuTexObjectGetResourceDesc");
    using func_ptr = CUresult (*)(CUDA_RESOURCE_DESC *, CUtexObject);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexObjectGetResourceDesc"));
    HOOK_CHECK(func_entry);
    return func_entry(pResDesc, texObject);
}

CUresult cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC * pTexDesc, CUtexObject texObject) {
    HOOK_TRACE_PROFILE("cuTexObjectGetTextureDesc");
    using func_ptr = CUresult (*)(CUDA_TEXTURE_DESC *, CUtexObject);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexObjectGetTextureDesc"));
    HOOK_CHECK(func_entry);
    return func_entry(pTexDesc, texObject);
}

CUresult cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC * pResViewDesc, CUtexObject texObject) {
    HOOK_TRACE_PROFILE("cuTexObjectGetResourceViewDesc");
    using func_ptr = CUresult (*)(CUDA_RESOURCE_VIEW_DESC *, CUtexObject);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexObjectGetResourceViewDesc"));
    HOOK_CHECK(func_entry);
    return func_entry(pResViewDesc, texObject);
}

CUresult cuSurfObjectCreate(CUsurfObject * pSurfObject, const CUDA_RESOURCE_DESC * pResDesc) {
    HOOK_TRACE_PROFILE("cuSurfObjectCreate");
    using func_ptr = CUresult (*)(CUsurfObject *, const CUDA_RESOURCE_DESC *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuSurfObjectCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(pSurfObject, pResDesc);
}

CUresult cuSurfObjectDestroy(CUsurfObject surfObject) {
    HOOK_TRACE_PROFILE("cuSurfObjectDestroy");
    using func_ptr = CUresult (*)(CUsurfObject);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuSurfObjectDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(surfObject);
}

CUresult cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC * pResDesc, CUsurfObject surfObject) {
    HOOK_TRACE_PROFILE("cuSurfObjectGetResourceDesc");
    using func_ptr = CUresult (*)(CUDA_RESOURCE_DESC *, CUsurfObject);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuSurfObjectGetResourceDesc"));
    HOOK_CHECK(func_entry);
    return func_entry(pResDesc, surfObject);
}

CUresult cuTensorMapEncodeTiled(CUtensorMap * tensorMap, CUtensorMapDataType tensorDataType, cuuint32_t tensorRank, void * globalAddress, const cuuint64_t * globalDim, const cuuint64_t * globalStrides, const cuuint32_t * boxDim, const cuuint32_t * elementStrides, CUtensorMapInterleave interleave, CUtensorMapSwizzle swizzle, CUtensorMapL2promotion l2Promotion, CUtensorMapFloatOOBfill oobFill) {
    HOOK_TRACE_PROFILE("cuTensorMapEncodeTiled");
    using func_ptr = CUresult (*)(CUtensorMap *, CUtensorMapDataType, cuuint32_t, void *, const cuuint64_t *, const cuuint64_t *, const cuuint32_t *, const cuuint32_t *, CUtensorMapInterleave, CUtensorMapSwizzle, CUtensorMapL2promotion, CUtensorMapFloatOOBfill);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTensorMapEncodeTiled"));
    HOOK_CHECK(func_entry);
    return func_entry(tensorMap, tensorDataType, tensorRank, globalAddress, globalDim, globalStrides, boxDim, elementStrides, interleave, swizzle, l2Promotion, oobFill);
}

CUresult cuTensorMapEncodeIm2col(CUtensorMap * tensorMap, CUtensorMapDataType tensorDataType, cuuint32_t tensorRank, void * globalAddress, const cuuint64_t * globalDim, const cuuint64_t * globalStrides, const int * pixelBoxLowerCorner, const int * pixelBoxUpperCorner, cuuint32_t channelsPerPixel, cuuint32_t pixelsPerColumn, const cuuint32_t * elementStrides, CUtensorMapInterleave interleave, CUtensorMapSwizzle swizzle, CUtensorMapL2promotion l2Promotion, CUtensorMapFloatOOBfill oobFill) {
    HOOK_TRACE_PROFILE("cuTensorMapEncodeIm2col");
    using func_ptr = CUresult (*)(CUtensorMap *, CUtensorMapDataType, cuuint32_t, void *, const cuuint64_t *, const cuuint64_t *, const int *, const int *, cuuint32_t, cuuint32_t, const cuuint32_t *, CUtensorMapInterleave, CUtensorMapSwizzle, CUtensorMapL2promotion, CUtensorMapFloatOOBfill);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTensorMapEncodeIm2col"));
    HOOK_CHECK(func_entry);
    return func_entry(tensorMap, tensorDataType, tensorRank, globalAddress, globalDim, globalStrides, pixelBoxLowerCorner, pixelBoxUpperCorner, channelsPerPixel, pixelsPerColumn, elementStrides, interleave, swizzle, l2Promotion, oobFill);
}

CUresult cuTensorMapReplaceAddress(CUtensorMap * tensorMap, void * globalAddress) {
    HOOK_TRACE_PROFILE("cuTensorMapReplaceAddress");
    using func_ptr = CUresult (*)(CUtensorMap *, void *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTensorMapReplaceAddress"));
    HOOK_CHECK(func_entry);
    return func_entry(tensorMap, globalAddress);
}

CUresult cuDeviceCanAccessPeer(int * canAccessPeer, CUdevice dev, CUdevice peerDev) {
    HOOK_TRACE_PROFILE("cuDeviceCanAccessPeer");
    using func_ptr = CUresult (*)(int *, CUdevice, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceCanAccessPeer"));
    HOOK_CHECK(func_entry);
    return func_entry(canAccessPeer, dev, peerDev);
}

CUresult cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags) {
    HOOK_TRACE_PROFILE("cuCtxEnablePeerAccess");
    using func_ptr = CUresult (*)(CUcontext, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxEnablePeerAccess"));
    HOOK_CHECK(func_entry);
    return func_entry(peerContext, Flags);
}

CUresult cuCtxDisablePeerAccess(CUcontext peerContext) {
    HOOK_TRACE_PROFILE("cuCtxDisablePeerAccess");
    using func_ptr = CUresult (*)(CUcontext);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxDisablePeerAccess"));
    HOOK_CHECK(func_entry);
    return func_entry(peerContext);
}

CUresult cuDeviceGetP2PAttribute(int * value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice) {
    HOOK_TRACE_PROFILE("cuDeviceGetP2PAttribute");
    using func_ptr = CUresult (*)(int *, CUdevice_P2PAttribute, CUdevice, CUdevice);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetP2PAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(value, attrib, srcDevice, dstDevice);
}

CUresult cuGraphicsUnregisterResource(CUgraphicsResource resource) {
    HOOK_TRACE_PROFILE("cuGraphicsUnregisterResource");
    using func_ptr = CUresult (*)(CUgraphicsResource);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsUnregisterResource"));
    HOOK_CHECK(func_entry);
    return func_entry(resource);
}

CUresult cuGraphicsSubResourceGetMappedArray(CUarray * pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel) {
    HOOK_TRACE_PROFILE("cuGraphicsSubResourceGetMappedArray");
    using func_ptr = CUresult (*)(CUarray *, CUgraphicsResource, unsigned int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsSubResourceGetMappedArray"));
    HOOK_CHECK(func_entry);
    return func_entry(pArray, resource, arrayIndex, mipLevel);
}

CUresult cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray * pMipmappedArray, CUgraphicsResource resource) {
    HOOK_TRACE_PROFILE("cuGraphicsResourceGetMappedMipmappedArray");
    using func_ptr = CUresult (*)(CUmipmappedArray *, CUgraphicsResource);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsResourceGetMappedMipmappedArray"));
    HOOK_CHECK(func_entry);
    return func_entry(pMipmappedArray, resource);
}

CUresult cuGraphicsResourceGetMappedPointer(CUdeviceptr * pDevPtr, size_t * pSize, CUgraphicsResource resource) {
    HOOK_TRACE_PROFILE("cuGraphicsResourceGetMappedPointer");
    using func_ptr = CUresult (*)(CUdeviceptr *, size_t *, CUgraphicsResource);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsResourceGetMappedPointer"));
    HOOK_CHECK(func_entry);
    return func_entry(pDevPtr, pSize, resource);
}

CUresult cuGraphicsResourceSetMapFlags(CUgraphicsResource resource, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuGraphicsResourceSetMapFlags");
    using func_ptr = CUresult (*)(CUgraphicsResource, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsResourceSetMapFlags"));
    HOOK_CHECK(func_entry);
    return func_entry(resource, flags);
}

CUresult cuGraphicsMapResources(unsigned int count, CUgraphicsResource * resources, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuGraphicsMapResources");
    using func_ptr = CUresult (*)(unsigned int, CUgraphicsResource *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsMapResources"));
    HOOK_CHECK(func_entry);
    return func_entry(count, resources, hStream);
}

CUresult cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource * resources, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuGraphicsUnmapResources");
    using func_ptr = CUresult (*)(unsigned int, CUgraphicsResource *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphicsUnmapResources"));
    HOOK_CHECK(func_entry);
    return func_entry(count, resources, hStream);
}

CUresult cuGetProcAddress(const char * symbol, void * * pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus) {
    HOOK_TRACE_PROFILE("cuGetProcAddress");
    using func_ptr = CUresult (*)(const char *, void * *, int, cuuint64_t, CUdriverProcAddressQueryResult *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGetProcAddress"));
    HOOK_CHECK(func_entry);
    return func_entry(symbol, pfn, cudaVersion, flags, symbolStatus);
}

CUresult cuCoredumpGetAttribute(CUcoredumpSettings attrib, void * value, size_t * size) {
    HOOK_TRACE_PROFILE("cuCoredumpGetAttribute");
    using func_ptr = CUresult (*)(CUcoredumpSettings, void *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCoredumpGetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(attrib, value, size);
}

CUresult cuCoredumpGetAttributeGlobal(CUcoredumpSettings attrib, void * value, size_t * size) {
    HOOK_TRACE_PROFILE("cuCoredumpGetAttributeGlobal");
    using func_ptr = CUresult (*)(CUcoredumpSettings, void *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCoredumpGetAttributeGlobal"));
    HOOK_CHECK(func_entry);
    return func_entry(attrib, value, size);
}

CUresult cuCoredumpSetAttribute(CUcoredumpSettings attrib, void * value, size_t * size) {
    HOOK_TRACE_PROFILE("cuCoredumpSetAttribute");
    using func_ptr = CUresult (*)(CUcoredumpSettings, void *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCoredumpSetAttribute"));
    HOOK_CHECK(func_entry);
    return func_entry(attrib, value, size);
}

CUresult cuCoredumpSetAttributeGlobal(CUcoredumpSettings attrib, void * value, size_t * size) {
    HOOK_TRACE_PROFILE("cuCoredumpSetAttributeGlobal");
    using func_ptr = CUresult (*)(CUcoredumpSettings, void *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCoredumpSetAttributeGlobal"));
    HOOK_CHECK(func_entry);
    return func_entry(attrib, value, size);
}

CUresult cuGetExportTable(const void * * ppExportTable, const CUuuid * pExportTableId) {
    HOOK_TRACE_PROFILE("cuGetExportTable");
    using func_ptr = CUresult (*)(const void * *, const CUuuid *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGetExportTable"));
    HOOK_CHECK(func_entry);
    return func_entry(ppExportTable, pExportTableId);
}



CUresult cuGreenCtxCreate(CUgreenCtx * phCtx, CUdevResourceDesc desc, CUdevice dev, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuGreenCtxCreate");
    using func_ptr = CUresult (*)(CUgreenCtx *, CUdevResourceDesc, CUdevice, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGreenCtxCreate"));
    HOOK_CHECK(func_entry);
    return func_entry(phCtx, desc, dev, flags);
}

CUresult cuGreenCtxDestroy(CUgreenCtx hCtx) {
    HOOK_TRACE_PROFILE("cuGreenCtxDestroy");
    using func_ptr = CUresult (*)(CUgreenCtx);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGreenCtxDestroy"));
    HOOK_CHECK(func_entry);
    return func_entry(hCtx);
}

CUresult cuCtxFromGreenCtx(CUcontext * pContext, CUgreenCtx hCtx) {
    HOOK_TRACE_PROFILE("cuCtxFromGreenCtx");
    using func_ptr = CUresult (*)(CUcontext *, CUgreenCtx);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxFromGreenCtx"));
    HOOK_CHECK(func_entry);
    return func_entry(pContext, hCtx);
}

CUresult cuDeviceGetDevResource(CUdevice device, CUdevResource * resource, CUdevResourceType type) {
    HOOK_TRACE_PROFILE("cuDeviceGetDevResource");
    using func_ptr = CUresult (*)(CUdevice, CUdevResource *, CUdevResourceType);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDeviceGetDevResource"));
    HOOK_CHECK(func_entry);
    return func_entry(device, resource, type);
}

CUresult cuCtxGetDevResource(CUcontext hCtx, CUdevResource * resource, CUdevResourceType type) {
    HOOK_TRACE_PROFILE("cuCtxGetDevResource");
    using func_ptr = CUresult (*)(CUcontext, CUdevResource *, CUdevResourceType);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuCtxGetDevResource"));
    HOOK_CHECK(func_entry);
    return func_entry(hCtx, resource, type);
}

CUresult cuGreenCtxGetDevResource(CUgreenCtx hCtx, CUdevResource * resource, CUdevResourceType type) {
    HOOK_TRACE_PROFILE("cuGreenCtxGetDevResource");
    using func_ptr = CUresult (*)(CUgreenCtx, CUdevResource *, CUdevResourceType);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGreenCtxGetDevResource"));
    HOOK_CHECK(func_entry);
    return func_entry(hCtx, resource, type);
}

CUresult cuDevSmResourceSplitByCount(CUdevResource * result, unsigned int * nbGroups, const CUdevResource * input, CUdevResource * remaining, unsigned int useFlags, unsigned int minCount) {
    HOOK_TRACE_PROFILE("cuDevSmResourceSplitByCount");
    using func_ptr = CUresult (*)(CUdevResource *, unsigned int *, const CUdevResource *, CUdevResource *, unsigned int, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevSmResourceSplitByCount"));
    HOOK_CHECK(func_entry);
    return func_entry(result, nbGroups, input, remaining, useFlags, minCount);
}

CUresult cuDevResourceGenerateDesc(CUdevResourceDesc * phDesc, CUdevResource * resources, unsigned int nbResources) {
    HOOK_TRACE_PROFILE("cuDevResourceGenerateDesc");
    using func_ptr = CUresult (*)(CUdevResourceDesc *, CUdevResource *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuDevResourceGenerateDesc"));
    HOOK_CHECK(func_entry);
    return func_entry(phDesc, resources, nbResources);
}

CUresult cuGreenCtxRecordEvent(CUgreenCtx hCtx, CUevent hEvent) {
    HOOK_TRACE_PROFILE("cuGreenCtxRecordEvent");
    using func_ptr = CUresult (*)(CUgreenCtx, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGreenCtxRecordEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hCtx, hEvent);
}

CUresult cuGreenCtxWaitEvent(CUgreenCtx hCtx, CUevent hEvent) {
    HOOK_TRACE_PROFILE("cuGreenCtxWaitEvent");
    using func_ptr = CUresult (*)(CUgreenCtx, CUevent);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGreenCtxWaitEvent"));
    HOOK_CHECK(func_entry);
    return func_entry(hCtx, hEvent);
}

CUresult cuStreamGetGreenCtx(CUstream hStream, CUgreenCtx * phCtx) {
    HOOK_TRACE_PROFILE("cuStreamGetGreenCtx");
    using func_ptr = CUresult (*)(CUstream, CUgreenCtx *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetGreenCtx"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, phCtx);
}

CUresult cuTexRefSetAddress2D_v2(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR * desc, CUdeviceptr dptr, size_t Pitch) {
    HOOK_TRACE_PROFILE("cuTexRefSetAddress2D_v2");
    using func_ptr = CUresult (*)(CUtexref, const CUDA_ARRAY_DESCRIPTOR *, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuTexRefSetAddress2D_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hTexRef, desc, dptr, Pitch);
}

CUresult cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoD_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, const void *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoD_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcHost, ByteCount);
}

CUresult cuMemcpyDtoH_v2(void * dstHost, CUdeviceptr srcDevice, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoH_v2");
    using func_ptr = CUresult (*)(void *, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoH_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcDevice, ByteCount);
}

CUresult cuMemcpyDtoD_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoD_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoD_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcDevice, ByteCount);
}

CUresult cuMemcpyDtoA_v2(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoA_v2");
    using func_ptr = CUresult (*)(CUarray, size_t, CUdeviceptr, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoA_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcDevice, ByteCount);
}

CUresult cuMemcpyAtoD_v2(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoD_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, CUarray, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoD_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcArray, srcOffset, ByteCount);
}

CUresult cuMemcpyHtoA_v2(CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoA_v2");
    using func_ptr = CUresult (*)(CUarray, size_t, const void *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoA_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcHost, ByteCount);
}

CUresult cuMemcpyAtoH_v2(void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoH_v2");
    using func_ptr = CUresult (*)(void *, CUarray, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoH_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcArray, srcOffset, ByteCount);
}

CUresult cuMemcpyAtoA_v2(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoA_v2");
    using func_ptr = CUresult (*)(CUarray, size_t, CUarray, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoA_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcArray, srcOffset, ByteCount);
}

CUresult cuMemcpyHtoAAsync_v2(CUarray dstArray, size_t dstOffset, const void * srcHost, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoAAsync_v2");
    using func_ptr = CUresult (*)(CUarray, size_t, const void *, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoAAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstArray, dstOffset, srcHost, ByteCount, hStream);
}

CUresult cuMemcpyAtoHAsync_v2(void * dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyAtoHAsync_v2");
    using func_ptr = CUresult (*)(void *, CUarray, size_t, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyAtoHAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcArray, srcOffset, ByteCount, hStream);
}

CUresult cuMemcpy2D_v2(const CUDA_MEMCPY2D * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy2D_v2");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY2D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy2D_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpy2DUnaligned_v2(const CUDA_MEMCPY2D * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy2DUnaligned_v2");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY2D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy2DUnaligned_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpy3D_v2(const CUDA_MEMCPY3D * pCopy) {
    HOOK_TRACE_PROFILE("cuMemcpy3D_v2");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY3D *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy3D_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy);
}

CUresult cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice, const void * srcHost, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyHtoDAsync_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, const void *, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyHtoDAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcHost, ByteCount, hStream);
}

CUresult cuMemcpyDtoHAsync_v2(void * dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoHAsync_v2");
    using func_ptr = CUresult (*)(void *, CUdeviceptr, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoHAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstHost, srcDevice, ByteCount, hStream);
}

CUresult cuMemcpyDtoDAsync_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpyDtoDAsync_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, CUdeviceptr, size_t, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpyDtoDAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, srcDevice, ByteCount, hStream);
}

CUresult cuMemcpy2DAsync_v2(const CUDA_MEMCPY2D * pCopy, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpy2DAsync_v2");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY2D *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy2DAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy, hStream);
}

CUresult cuMemcpy3DAsync_v2(const CUDA_MEMCPY3D * pCopy, CUstream hStream) {
    HOOK_TRACE_PROFILE("cuMemcpy3DAsync_v2");
    using func_ptr = CUresult (*)(const CUDA_MEMCPY3D *, CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemcpy3DAsync_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(pCopy, hStream);
}

CUresult cuMemsetD8_v2(CUdeviceptr dstDevice, unsigned char uc, size_t N) {
    HOOK_TRACE_PROFILE("cuMemsetD8_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned char, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD8_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, uc, N);
}

CUresult cuMemsetD16_v2(CUdeviceptr dstDevice, unsigned short us, size_t N) {
    HOOK_TRACE_PROFILE("cuMemsetD16_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned short, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD16_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, us, N);
}

CUresult cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui, size_t N) {
    HOOK_TRACE_PROFILE("cuMemsetD32_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, unsigned int, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD32_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, ui, N);
}

CUresult cuMemsetD2D8_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height) {
    HOOK_TRACE_PROFILE("cuMemsetD2D8_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned char, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D8_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, uc, Width, Height);
}

CUresult cuMemsetD2D16_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height) {
    HOOK_TRACE_PROFILE("cuMemsetD2D16_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned short, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D16_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, us, Width, Height);
}

CUresult cuMemsetD2D32_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height) {
    HOOK_TRACE_PROFILE("cuMemsetD2D32_v2");
    using func_ptr = CUresult (*)(CUdeviceptr, size_t, unsigned int, size_t, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuMemsetD2D32_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(dstDevice, dstPitch, ui, Width, Height);
}

CUresult cuStreamWriteValue32_ptsz(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWriteValue32_ptsz");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWriteValue32_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWaitValue32_ptsz(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitValue32_ptsz");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitValue32_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWriteValue64_ptsz(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWriteValue64_ptsz");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWriteValue64_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWaitValue64_ptsz(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitValue64_ptsz");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitValue64_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamBatchMemOp_ptsz(CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamBatchMemOp_ptsz");
    using func_ptr = CUresult (*)(CUstream, unsigned int, CUstreamBatchMemOpParams *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBatchMemOp_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, count, paramArray, flags);
}

CUresult cuStreamWriteValue32_v2(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWriteValue32_v2");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWriteValue32_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWaitValue32_v2(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitValue32_v2");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitValue32_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWriteValue64_v2(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWriteValue64_v2");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWriteValue64_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamWaitValue64_v2(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamWaitValue64_v2");
    using func_ptr = CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamWaitValue64_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, addr, value, flags);
}

CUresult cuStreamBatchMemOp_v2(CUstream stream, unsigned int count, CUstreamBatchMemOpParams * paramArray, unsigned int flags) {
    HOOK_TRACE_PROFILE("cuStreamBatchMemOp_v2");
    using func_ptr = CUresult (*)(CUstream, unsigned int, CUstreamBatchMemOpParams *, unsigned int);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBatchMemOp_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(stream, count, paramArray, flags);
}

CUresult cuStreamBeginCapture_ptsz(CUstream hStream) {
    HOOK_TRACE_PROFILE("cuStreamBeginCapture_ptsz");
    using func_ptr = CUresult (*)(CUstream);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBeginCapture_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream);
}

CUresult cuStreamBeginCapture_v2(CUstream hStream, CUstreamCaptureMode mode) {
    HOOK_TRACE_PROFILE("cuStreamBeginCapture_v2");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureMode);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamBeginCapture_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, mode);
}

CUresult cuStreamGetCaptureInfo_ptsz(CUstream hStream, CUstreamCaptureStatus * captureStatus_out, cuuint64_t * id_out) {
    HOOK_TRACE_PROFILE("cuStreamGetCaptureInfo_ptsz");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureStatus *, cuuint64_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetCaptureInfo_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, captureStatus_out, id_out);
}

CUresult cuStreamGetCaptureInfo_v2(CUstream hStream, CUstreamCaptureStatus * captureStatus_out, cuuint64_t * id_out, CUgraph * graph_out, const CUgraphNode * * dependencies_out, size_t * numDependencies_out) {
    HOOK_TRACE_PROFILE("cuStreamGetCaptureInfo_v2");
    using func_ptr = CUresult (*)(CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode * *, size_t *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuStreamGetCaptureInfo_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(hStream, captureStatus_out, id_out, graph_out, dependencies_out, numDependencies_out);
}

CUresult cuGraphInstantiate_v2(CUgraphExec * phGraphExec, CUgraph hGraph, CUgraphNode * phErrorNode, char * logBuffer, size_t bufferSize) {
    HOOK_TRACE_PROFILE("cuGraphInstantiate_v2");
    using func_ptr = CUresult (*)(CUgraphExec *, CUgraph, CUgraphNode *, char *, size_t);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGraphInstantiate_v2"));
    HOOK_CHECK(func_entry);
    return func_entry(phGraphExec, hGraph, phErrorNode, logBuffer, bufferSize);
}

 CUresult cuGetProcAddress_v2(const char * symbol, void * * funcPtr, int driverVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus) {
    HOOK_TRACE_PROFILE("cuGetProcAddress_v2");
    using func_ptr =  CUresult (*)(const char *, void * *, int, cuuint64_t, CUdriverProcAddressQueryResult *);
    static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("cuGetProcAddress_v2_ptsz"));
    HOOK_CHECK(func_entry);
    return func_entry(symbol, funcPtr, driverVersion, flags, symbolStatus);
}
