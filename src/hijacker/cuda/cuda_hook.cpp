#include <cstddef>
#include <cstring>
#include <cuda.h>
#include <cstdio>
#include "cuda_hook.h"

#include <string>
#include <unordered_map>
#include <elf.h>
#include <iostream>
#include "macro_common.h"
#include "communication.h"
#include "communicator.h"
#include "cpu-elf2.h"

std::unordered_map<std::string, CuDriverFunction> cuDriverFunctionTable;
// 定义一个普通函数指针来存储 cuInit 的拦截实现

list kernel_infos;
std::string getCUjitOptionName(CUjit_option option) {
    switch (option) {
        case CU_JIT_MAX_REGISTERS: return "CU_JIT_MAX_REGISTERS";
        case CU_JIT_THREADS_PER_BLOCK: return "CU_JIT_THREADS_PER_BLOCK";
        case CU_JIT_WALL_TIME: return "CU_JIT_WALL_TIME";
        case CU_JIT_INFO_LOG_BUFFER: return "CU_JIT_INFO_LOG_BUFFER";
        case CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES: return "CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES";
        case CU_JIT_ERROR_LOG_BUFFER: return "CU_JIT_ERROR_LOG_BUFFER";
        case CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES: return "CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES";
        case CU_JIT_OPTIMIZATION_LEVEL: return "CU_JIT_OPTIMIZATION_LEVEL";
        case CU_JIT_TARGET_FROM_CUCONTEXT: return "CU_JIT_TARGET_FROM_CUCONTEXT";
        case CU_JIT_TARGET: return "CU_JIT_TARGET";
        case CU_JIT_FALLBACK_STRATEGY: return "CU_JIT_FALLBACK_STRATEGY";
        case CU_JIT_GENERATE_DEBUG_INFO: return "CU_JIT_GENERATE_DEBUG_INFO";
        case CU_JIT_LOG_VERBOSE: return "CU_JIT_LOG_VERBOSE";
        case CU_JIT_GENERATE_LINE_INFO: return "CU_JIT_GENERATE_LINE_INFO";
        case CU_JIT_CACHE_MODE: return "CU_JIT_CACHE_MODE";
        case CU_JIT_NEW_SM3X_OPT: return "CU_JIT_NEW_SM3X_OPT";
        case CU_JIT_FAST_COMPILE: return "CU_JIT_FAST_COMPILE";
        case CU_JIT_GLOBAL_SYMBOL_NAMES: return "CU_JIT_GLOBAL_SYMBOL_NAMES";
        case CU_JIT_GLOBAL_SYMBOL_ADDRESSES: return "CU_JIT_GLOBAL_SYMBOL_ADDRESSES";
        case CU_JIT_GLOBAL_SYMBOL_COUNT: return "CU_JIT_GLOBAL_SYMBOL_COUNT";
        case CU_JIT_LTO: return "CU_JIT_LTO";
        case CU_JIT_FTZ: return "CU_JIT_FTZ";
        case CU_JIT_PREC_DIV: return "CU_JIT_PREC_DIV";
        case CU_JIT_PREC_SQRT: return "CU_JIT_PREC_SQRT";
        case CU_JIT_FMA: return "CU_JIT_FMA";
        case CU_JIT_REFERENCED_KERNEL_NAMES: return "CU_JIT_REFERENCED_KERNEL_NAMES";
        case CU_JIT_REFERENCED_KERNEL_COUNT: return "CU_JIT_REFERENCED_KERNEL_COUNT";
        case CU_JIT_REFERENCED_VARIABLE_NAMES: return "CU_JIT_REFERENCED_VARIABLE_NAMES";
        case CU_JIT_REFERENCED_VARIABLE_COUNT: return "CU_JIT_REFERENCED_VARIABLE_COUNT";
        case CU_JIT_OPTIMIZE_UNUSED_DEVICE_VARIABLES: return "CU_JIT_OPTIMIZE_UNUSED_DEVICE_VARIABLES";
        case CU_JIT_POSITION_INDEPENDENT_CODE: return "CU_JIT_POSITION_INDEPENDENT_CODE";
        case CU_JIT_MIN_CTA_PER_SM: return "CU_JIT_MIN_CTA_PER_SM";
        case CU_JIT_MAX_THREADS_PER_BLOCK: return "CU_JIT_MAX_THREADS_PER_BLOCK";
        case CU_JIT_OVERRIDE_DIRECTIVE_VALUES: return "CU_JIT_OVERRIDE_DIRECTIVE_VALUES";
        case CU_JIT_NUM_OPTIONS: return "CU_JIT_NUM_OPTIONS";
        default: return "Unknown Option";
    }
}


HOOK_C_API HOOK_DECL_EXPORT  CUresult cuInit(unsigned int Flags) {
    
    HOOK_TRACE_PROFILE("cuInit");

    CuDriverCallStructure request={
        .op= CuDriverCall::CuInit,
        .params={.cuInit{.flags=Flags}},
    };
    CuDriverCallReplyStructure reply;
    printf("[cuInit] flags:%u\n",Flags);
    communicate_with_server(NULL, &request, &reply);
    return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuModuleGetLoadingMode(CUmoduleLoadingMode * mode) {
    CuDriverCallStructure request{
        .op=CuDriverCall::CuModuleGetLoadingMode,
    };
    CuDriverCallReplyStructure reply;
    
    communicate_with_server(NULL, &request, &reply);
    *mode=reply.returnParams.mode;
    return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGetCount(int * count) {
    HOOK_TRACE_PROFILE("cuDeviceGetCount");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuDeviceGetCount,
        .params={.empty{}},
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
    *count=reply.returnParams.count;

    return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGetName(char * name, int len, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetName");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuDeviceGetName,
        .params={.cuDeviceGetName={.name=name,.len=len,.device=dev}}
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
	printf("[cuDeviceGetName] get name:%s\n",name);
    return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT CUresult cuDeviceGetUuid (CUuuid * uuid,CUdevice dev){
	HOOK_TRACE_PROFILE("cuDeviceGetUuid");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuDeviceGetUuid,
		.params={.cuDeviceGetUuid={.dev=dev}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	memcpy(uuid->bytes,reply.returnParams.uuid,16);
	printf("[cuDeviceGetUuid] get uuid:%s\n",uuid->bytes);
	return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDriverGetVersion(int * driverVersion) {
    HOOK_TRACE_PROFILE("cuDriverGetVersion");
    CuDriverCallStructure request={
        .op=CuDriverCall::CuDriverGetVersion,
        .params={.empty{}},
    };
    CuDriverCallReplyStructure reply;

    communicate_with_server(NULL, &request,&reply);
    
    *driverVersion=reply.returnParams.driverVersion;
    printf("[cuDriverGetVersion] get driverVersion: %d\n", *driverVersion);
    return reply.result;

}

HOOK_C_API HOOK_DECL_EXPORT CUresult cuMemAlloc(CUdeviceptr * dptr, size_t bytesize) {
	HOOK_TRACE_PROFILE("cuMemAlloc");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuMemAlloc,
		.params={.cuMemAlloc={.bytesize=bytesize}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	*dptr=reply.returnParams.dptr;
	printf("[cuMemAlloc] allocate %ld bytes memory at %p\n",bytesize,*dptr);
	return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT CUresult cuMemFree(CUdeviceptr dptr) {
	HOOK_TRACE_PROFILE("cuMemFree");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuMemFree,
		.params={.cuMemFree={.dptr=dptr}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	printf("[cuMemFree] free memory at %p\n",dptr);
	return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGet(CUdevice * device, int ordinal) {
    HOOK_TRACE_PROFILE("cuDeviceGet");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuDeviceGet,
        .params={.cuDeviceGet={.ordinal=ordinal}},
    };
    CuDriverCallReplyStructure reply;
    request.op=CuDriverCall::CuDeviceGet;
    communicate_with_server(nullptr, &request, &reply);

    *device=reply.returnParams.device;
	printf("[cuDeviceGet] get device:%d\n",*device);
    return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT CUresult cuDeviceTotalMem (size_t * bytes,CUdevice dev){
	HOOK_TRACE_PROFILE("cuDeviceTotalMem");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuDeviceTotalMem,
		.params={.cuDeviceTotalMem={.dev=dev}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	*bytes=reply.returnParams.bytes;
	printf("[cuDeviceTotalMem] dev[%d] total memory:%ld\n",dev,*bytes);
}


HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGetAttribute(int * pi, CUdevice_attribute attrib, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDeviceGetAttribute");
    CuDriverCallStructure request={
        .op=CuDriverCall::CuDeviceGetAttribute,
        .params={.cuDeviceGetAttribute={.attrib=attrib,.dev=dev}},
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
    *pi=reply.returnParams.pi;
	printf("[cuDeviceGetAttribute] get attribute:%d\n",*pi);
    return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuCtxSetCurrent(CUcontext ctx) {
    HOOK_TRACE_PROFILE("cuCtxSetCurrent");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuCtxSetCurrent,
        .params={.cuCtxSetCurrent={.ctx=ctx}},
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
	printf("[cuCtxSetCurrent] try to set current context:%p\n",ctx);
    return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuCtxGetCurrent(CUcontext * pctx) {
    HOOK_TRACE_PROFILE("cuCtxGetCurrent");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuCtxGetCurrent,
        .params={.empty{}},
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
    *pctx=reply.returnParams.ctx;
	printf("[cuCtxGetCurrent] get current context:%p\n",*pctx);
    return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDevicePrimaryCtxRetain(CUcontext * pctx, CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxRetain");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuDevicePrimaryCtxRetain,
        .params={.cuDevicePrimaryCtxRetain={.dev=dev}},
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
    *pctx=reply.returnParams.ctx;
	printf("[cuDevicePrimaryCtxRetain] retain device[%d] primary context:%p\n",dev,*pctx);
    return reply.result;
}
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDevicePrimaryCtxRelease(CUdevice dev) {
    HOOK_TRACE_PROFILE("cuDevicePrimaryCtxRelease");
    CuDriverCallStructure request{
        .op=CuDriverCall::CuDevicePrimaryCtxRelease,
        .params={.cuDevicePrimaryCtxRelease={.dev=dev}},
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server(nullptr, &request, &reply);
	printf("[cuDevicePrimaryCtxRelease] release device[%d] primary context\n",dev);
    return reply.result;
}


HOOK_C_API HOOK_DECL_EXPORT CUresult cuMemcpyHtoD( CUdeviceptr dstDevice,const void * srcHost,size_t ByteCount){
	HOOK_TRACE_PROFILE("cuMemcpyHtoD");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuMemcpyHtoD,
		.params={.cuMemcpyHtoD={.dstDevice=dstDevice,.srcHost=srcHost,.ByteCount=ByteCount}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	printf("[cuMemcpyHtoD] copy %ld bytes from %p to %p\n",ByteCount,srcHost,dstDevice);
	return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuLibraryGetModule(CUmodule * pMod, CUlibrary library) {
	CuDriverCallStructure request{
		.op=CuDriverCall::CuLibraryGetModule,
		.params={.cuLibraryGetModule={
			.library=library,
		}}
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	*pMod=reply.returnParams.mod;
	printf("[cuLibraryGetModule] get module from library[%p]:%p\n",library,*pMod);
	return reply.result;

}
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuModuleGetFunction(CUfunction * hfunc, CUmodule hmod, const char * name) {
	CuDriverCallStructure request{
		.op=CuDriverCall::CuModuleGetFunction,
		.params={.cuModuleGetFunction{
			.mod=hmod,
			.name=name,
			.nameLength=strlen(name)+1
		}}
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	*hfunc=reply.returnParams.hfunc;
	printf("[cuModuleGetFunction] get function %s from module[%p]:%p\n",name,hmod,*hfunc);
	return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra) {

    size_t i;
    char *buf;
    int found_kernel = 0;
    kernel_info_t *info;

    for (i=0; i < kernel_infos.length; ++i) {
        if (list_at(&kernel_infos, i, (void**)&info) != 0) {
            HLOG("error getting element at %d", i);
            return CUDA_ERROR_INVALID_DEVICE;
        }
        if (f != NULL && info != NULL && info->host_fun == f) {
            HLOG("calling kernel \"%s\" (param_size: %zd, param_num: %zd)", info->name, info->param_size, info->param_num);
            found_kernel = 1;
            break;
        }
    }

    if (!found_kernel) {
        HLOG("request to call unknown kernel.");
        return CUDA_ERROR_INVALID_VALUE;
    }


	
    size_t parameters_metadata_len = sizeof(size_t)+info->param_num*sizeof(uint16_t)+info->param_size;
    void * parameters_metadata = malloc(parameters_metadata_len);
    memcpy(parameters_metadata, &info->param_num, sizeof(size_t));
    memcpy(parameters_metadata + sizeof(size_t), info->param_offsets, info->param_num*sizeof(uint16_t));
    for (size_t j=0, size=0; j < info->param_num; ++j) {
        size = info->param_sizes[j];
        //printf("p%d - size: %d, offset: %d\n", j, size, infos[i].param_offsets[j]);
        memcpy(parameters_metadata + sizeof(size_t) + info->param_num*sizeof(uint16_t) +
               info->param_offsets[j],
        		kernelParams[j],
               size);
    }

	CuDriverCallStructure request{
		.op=CuDriverCall::CuLaunchKernel,
		.params={.cuLaunchKernel={
			.f=f,
			.gridDimX=gridDimX,
			.gridDimY=gridDimY,
			.gridDimZ=gridDimZ,
			.blockDimX=blockDimX,
			.blockDimY=blockDimY,
			.blockDimZ=blockDimZ,
			.sharedMemBytes=sharedMemBytes,
			.hStream=hStream,
			.parametersMetadataLen=parameters_metadata_len,
		}}
	};
	CuDriverCallReplyStructure reply;
	
	communicate_with_server_launchkernel(nullptr, &request, &reply , parameters_metadata);
    free(parameters_metadata);
    return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuLibraryLoadData(CUlibrary * library, const void * code, CUjit_option * jitOptions, void * * jitOptionsValues, unsigned int numJitOptions, CUlibraryOption * libraryOptions, void * * libraryOptionValues, unsigned int numLibraryOptions) {
	// FatBinaryWrapper *wrapper = (FatBinaryWrapper *)code;
	
	// printf("----------------------------------------------\n");
	// printf("code address = %p\n", code);
	// printf("fat binary wrapper's magic = %x\n", wrapper->magic);
	// printf("fat binary wrapper's version = %d\n", wrapper->version);
	// printf("fat binary wrapper's data = %p\n", wrapper->data);
	// printf("fat binary wrapper's filename_or_fatbins = %p\n", wrapper->filename_or_fatbins);
	// if (wrapper->version==2){
	// 	printf("fat binary wrapper's filename_or_fatbins = %s\n", wrapper->filename_or_fatbins);
	// }
	// printf("----------------------------------------------\n");
	// FatBinaryHeader *header = (FatBinaryHeader *)wrapper->data;
	// printf("fat binary's magic = %x\n", header->magic);
	// printf("fat binary's version: %d\n", header->version);
	// printf("fat binary's header size: %d\n", header->headerSize);
	// printf("fat binary's size: %ld\n", header->fatSize);
	// printf("----------------------------------------------\n");
	
	// unsigned long long codeAddress=	(unsigned long long)code;
	// unsigned long long fatbinAddress=	(unsigned long long)wrapper->data;


	// // printf("number of jit options: %d\n", numJitOptions);
	// // printf("number of jit option loading: %d\n", numLibraryOptions);
	// // printf(" LibraryOption:%d\n",libraryOptions[0]);
	// // printf(" LibraryOptionValues:%p\n",libraryOptionValues[0]);

	// printf("fatbin address = %p\n", wrapper->data);
	// printf("header size=%d\n",header->headerSize);
	// FatEntryHeader * fatbinEntry=(FatEntryHeader *) ((char *)wrapper->data+header->headerSize);
	// printf("fabin entry address:%p\n",fatbinEntry);
	// Elf64_Ehdr *ehdr = (Elf64_Ehdr*)((char *)fatbinEntry+fatbinEntry->headerSize);
	// printf("entry headersize:%d\n",fatbinEntry->headerSize);
	// printf("ehdr address:%p\n",ehdr);
	// printf("ehdr->e_ident:%s\n",ehdr->e_ident);

	// readFatbinaryEntryHeader((void *)wrapper->data);
	// printHex((void *)wrapper->data, 2000);
	
	uint8_t *code_data = new uint8_t;
	unsigned long  fatbin_size;
    if (elf2_get_fatbin_info((struct fat_header *)code,
                                &kernel_infos,
                                (uint8_t **)&code_data,
                                &fatbin_size) != 0) {

		printf("eeorrr\n");
    }
	free(code_data);
	FatBinaryWrapper *wrapper = (FatBinaryWrapper *)code;
	CuDriverCallStructure request{
		.op=CuDriverCall::CuLibraryLoadData,
		.params={
			.cuLibraryLoadData={
				.wrapper=*wrapper,
				.fatbinSize=fatbin_size,
				.numJitOptions=numJitOptions,
				.numLibraryOptions=numLibraryOptions,
			}	
		}
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server_extra(nullptr, &request, &reply,jitOptions,jitOptionsValues,libraryOptions,libraryOptionValues);
	return reply.result;
}
DEF_FN(CUresult,cuGetErrorString ,CUresult,error,const char * *,pStr);
DEF_FN(CUresult,cuGetErrorName ,CUresult,error,const char * *,pStr);
// DEF_FN(CUresult,cuDeviceGetUuid_v2 ,CUuuid *,uuid,CUdevice,dev);
DEF_FN(CUresult,cuDeviceGetLuid ,char *,luid,unsigned int *,deviceNodeMask,CUdevice,dev);
// DEF_FN(CUresult,cuDeviceTotalMem_v2 ,size_t *,bytes,CUdevice,dev);
DEF_FN(CUresult,cuDeviceGetTexture1DLinearMaxWidth ,size_t *,maxWidthInElements,CUarray_format,format,unsigned,numChannels,CUdevice,dev);
DEF_FN(CUresult,cuDeviceGetNvSciSyncAttributes ,void *,nvSciSyncAttrList,CUdevice,dev,int,flags);
DEF_FN(CUresult,cuDeviceSetMemPool ,CUdevice,dev,CUmemoryPool,pool);
DEF_FN(CUresult,cuDeviceGetMemPool ,CUmemoryPool *,pool,CUdevice,dev);
DEF_FN(CUresult,cuDeviceGetDefaultMemPool ,CUmemoryPool *,pool_out,CUdevice,dev);
DEF_FN(CUresult,cuDeviceGetExecAffinitySupport ,int *,pi,CUexecAffinityType,type,CUdevice,dev);
DEF_FN(CUresult,cuFlushGPUDirectRDMAWrites ,CUflushGPUDirectRDMAWritesTarget,target,CUflushGPUDirectRDMAWritesScope,scope);
DEF_FN(CUresult,cuDeviceGetProperties ,CUdevprop *,prop,CUdevice,dev);
DEF_FN(CUresult,cuDeviceComputeCapability ,int *,major,int *,minor,CUdevice,dev);
DEF_FN(CUresult,cuDevicePrimaryCtxSetFlags_v2 ,CUdevice,dev,unsigned int,flags);
DEF_FN(CUresult,cuDevicePrimaryCtxGetState ,CUdevice,dev,unsigned int *,flags,int *,active);
DEF_FN(CUresult,cuDevicePrimaryCtxReset_v2 ,CUdevice,dev);
DEF_FN(CUresult,cuCtxCreate_v2 ,CUcontext *,pctx,unsigned int,flags,CUdevice,dev);
DEF_FN(CUresult,cuCtxCreate_v3 ,CUcontext *,pctx,CUexecAffinityParam *,paramsArray,int,numParams,unsigned int,flags,CUdevice,dev);
DEF_FN(CUresult,cuCtxDestroy_v2 ,CUcontext,ctx);
DEF_FN(CUresult,cuCtxPushCurrent_v2 ,CUcontext,ctx);
DEF_FN(CUresult,cuCtxPopCurrent_v2 ,CUcontext *,pctx);
DEF_FN(CUresult,cuCtxGetDevice ,CUdevice *,device);
DEF_FN(CUresult,cuCtxGetFlags ,unsigned int *,flags);
DEF_FN(CUresult,cuCtxSetFlags ,unsigned int,flags);
DEF_FN(CUresult,cuCtxGetId ,CUcontext,ctx,unsigned long long *,ctxId);
DEF_FN(CUresult,cuCtxSynchronize ,void,);
DEF_FN(CUresult,cuCtxSetLimit ,CUlimit,limit,size_t,value);
DEF_FN(CUresult,cuCtxGetLimit ,size_t *,pvalue,CUlimit,limit);
DEF_FN(CUresult,cuCtxGetCacheConfig ,CUfunc_cache *,pconfig);
DEF_FN(CUresult,cuCtxSetCacheConfig ,CUfunc_cache,config);
DEF_FN(CUresult,cuCtxGetApiVersion ,CUcontext,ctx,unsigned int *,version);
DEF_FN(CUresult,cuCtxGetStreamPriorityRange ,int *,leastPriority,int *,greatestPriority);
DEF_FN(CUresult,cuCtxResetPersistingL2Cache ,void,);
DEF_FN(CUresult,cuCtxGetExecAffinity ,CUexecAffinityParam *,pExecAffinity,CUexecAffinityType,type);
DEF_FN(CUresult,cuCtxAttach ,CUcontext *,pctx,unsigned int,flags);
DEF_FN(CUresult,cuCtxDetach ,CUcontext,ctx);
DEF_FN(CUresult,cuCtxGetSharedMemConfig ,CUsharedconfig *,pConfig);
DEF_FN(CUresult,cuCtxSetSharedMemConfig ,CUsharedconfig,config);
DEF_FN(CUresult,cuModuleLoad ,CUmodule *,module,const char *,fname);
DEF_FN(CUresult,cuModuleLoadData ,CUmodule *,module,const void *,image);
DEF_FN(CUresult,cuModuleLoadDataEx ,CUmodule *,module,const void *,image,unsigned int,numOptions,CUjit_option *,options,void * *,optionValues);
DEF_FN(CUresult,cuModuleLoadFatBinary ,CUmodule *,module,const void *,fatCubin);
DEF_FN(CUresult,cuModuleGetFunctionCount ,unsigned int *,count,CUmodule,mod);
DEF_FN(CUresult,cuModuleEnumerateFunctions ,CUfunction *,functions,unsigned int,numFunctions,CUmodule,mod);
DEF_FN(CUresult,cuModuleGetGlobal_v2 ,CUdeviceptr *,dptr,size_t *,bytes,CUmodule,hmod,const char *,name);
DEF_FN(CUresult,cuLinkCreate_v2 ,unsigned int,numOptions,CUjit_option *,options,void * *,optionValues,CUlinkState *,stateOut);
DEF_FN(CUresult,cuLinkAddData_v2 ,CUlinkState,state,CUjitInputType,type,void *,data,size_t,size,const char *,name,unsigned int,numOptions,CUjit_option *,options,void * *,optionValues);
DEF_FN(CUresult,cuLinkAddFile_v2 ,CUlinkState,state,CUjitInputType,type,const char *,path,unsigned int,numOptions,CUjit_option *,options,void * *,optionValues);
DEF_FN(CUresult,cuLinkComplete ,CUlinkState,state,void * *,cubinOut,size_t *,sizeOut);
DEF_FN(CUresult,cuLinkDestroy ,CUlinkState,state);
DEF_FN(CUresult,cuModuleGetTexRef ,CUtexref *,pTexRef,CUmodule,hmod,const char *,name);
DEF_FN(CUresult,cuModuleGetSurfRef ,CUsurfref *,pSurfRef,CUmodule,hmod,const char *,name);
DEF_FN(CUresult,cuLibraryLoadFromFile ,CUlibrary *,library,const char *,fileName,CUjit_option *,jitOptions,void * *,jitOptionsValues,unsigned int,numJitOptions,CUlibraryOption *,libraryOptions,void * *,libraryOptionValues,unsigned int,numLibraryOptions);
DEF_FN(CUresult,cuLibraryUnload ,CUlibrary,library);
DEF_FN(CUresult,cuLibraryGetKernel ,CUkernel *,pKernel,CUlibrary,library,const char *,name);
DEF_FN(CUresult,cuLibraryGetKernelCount ,unsigned int *,count,CUlibrary,lib);
DEF_FN(CUresult,cuLibraryEnumerateKernels ,CUkernel *,kernels,unsigned int,numKernels,CUlibrary,lib);
DEF_FN(CUresult,cuKernelGetFunction ,CUfunction *,pFunc,CUkernel,kernel);
DEF_FN(CUresult,cuLibraryGetGlobal ,CUdeviceptr *,dptr,size_t *,bytes,CUlibrary,library,const char *,name);
DEF_FN(CUresult,cuLibraryGetManaged ,CUdeviceptr *,dptr,size_t *,bytes,CUlibrary,library,const char *,name);
DEF_FN(CUresult,cuLibraryGetUnifiedFunction ,void * *,fptr,CUlibrary,library,const char *,symbol);
DEF_FN(CUresult,cuKernelGetAttribute ,int *,pi,CUfunction_attribute,attrib,CUkernel,kernel,CUdevice,dev);
DEF_FN(CUresult,cuKernelSetAttribute ,CUfunction_attribute,attrib,int,val,CUkernel,kernel,CUdevice,dev);
DEF_FN(CUresult,cuKernelSetCacheConfig ,CUkernel,kernel,CUfunc_cache,config,CUdevice,dev);
DEF_FN(CUresult,cuKernelGetName ,const char * *,name,CUkernel,hfunc);
DEF_FN(CUresult,cuKernelGetParamInfo ,CUkernel,kernel,size_t,paramIndex,size_t *,paramOffset,size_t *,paramSize);
DEF_FN(CUresult,cuMemGetInfo_v2 ,size_t *,free,size_t *,total);
// DEF_FN(CUresult,cuMemAlloc_v2 ,CUdeviceptr *,dptr,size_t,bytesize);
DEF_FN(CUresult,cuMemAllocPitch_v2 ,CUdeviceptr *,dptr,size_t *,pPitch,size_t,WidthInBytes,size_t,Height,unsigned int,ElementSizeBytes);
// DEF_FN(CUresult,cuMemFree_v2 ,CUdeviceptr,dptr);
DEF_FN(CUresult,cuMemGetAddressRange_v2 ,CUdeviceptr *,pbase,size_t *,psize,CUdeviceptr,dptr);
DEF_FN(CUresult,cuMemAllocHost_v2 ,void * *,pp,size_t,bytesize);
DEF_FN(CUresult,cuMemFreeHost ,void *,p);
DEF_FN(CUresult,cuMemHostAlloc ,void * *,pp,size_t,bytesize,unsigned int,Flags);
DEF_FN(CUresult,cuMemHostGetDevicePointer_v2 ,CUdeviceptr *,pdptr,void *,p,unsigned int,Flags);
DEF_FN(CUresult,cuMemHostGetFlags ,unsigned int *,pFlags,void *,p);
DEF_FN(CUresult,cuMemAllocManaged ,CUdeviceptr *,dptr,size_t,bytesize,unsigned int,flags);
DEF_FN(CUresult,cuDeviceRegisterAsyncNotification ,CUdevice,device,CUasyncCallback,callbackFunc,void *,userData,CUasyncCallbackHandle *,callback);
DEF_FN(CUresult,cuDeviceUnregisterAsyncNotification ,CUdevice,device,CUasyncCallbackHandle,callback);
DEF_FN(CUresult,cuDeviceGetByPCIBusId ,CUdevice *,dev,const char *,pciBusId);
DEF_FN(CUresult,cuDeviceGetPCIBusId ,char *,pciBusId,int,len,CUdevice,dev);
DEF_FN(CUresult,cuIpcGetEventHandle ,CUipcEventHandle *,pHandle,CUevent,event);
DEF_FN(CUresult,cuIpcOpenEventHandle ,CUevent *,phEvent,CUipcEventHandle,handle);
DEF_FN(CUresult,cuIpcGetMemHandle ,CUipcMemHandle *,pHandle,CUdeviceptr,dptr);
DEF_FN(CUresult,cuIpcOpenMemHandle_v2 ,CUdeviceptr *,pdptr,CUipcMemHandle,handle,unsigned int,Flags);
DEF_FN(CUresult,cuIpcCloseMemHandle ,CUdeviceptr,dptr);
DEF_FN(CUresult,cuMemHostRegister_v2 ,void *,p,size_t,bytesize,unsigned int,Flags);
DEF_FN(CUresult,cuMemHostUnregister ,void *,p);
DEF_FN(CUresult,cuMemcpy ,CUdeviceptr,dst,CUdeviceptr,src,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyPeer ,CUdeviceptr,dstDevice,CUcontext,dstContext,CUdeviceptr,srcDevice,CUcontext,srcContext,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoH_v2 ,void *,dstHost,CUdeviceptr,srcDevice,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoD_v2 ,CUdeviceptr,dstDevice,CUdeviceptr,srcDevice,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoA_v2 ,CUarray,dstArray,size_t,dstOffset,CUdeviceptr,srcDevice,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoD_v2 ,CUdeviceptr,dstDevice,CUarray,srcArray,size_t,srcOffset,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyHtoA_v2 ,CUarray,dstArray,size_t,dstOffset,const void *,srcHost,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoH_v2 ,void *,dstHost,CUarray,srcArray,size_t,srcOffset,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoA_v2 ,CUarray,dstArray,size_t,dstOffset,CUarray,srcArray,size_t,srcOffset,size_t,ByteCount);
DEF_FN(CUresult,cuMemcpy2D_v2 ,const CUDA_MEMCPY2D *,pCopy);
DEF_FN(CUresult,cuMemcpy2DUnaligned_v2 ,const CUDA_MEMCPY2D *,pCopy);
DEF_FN(CUresult,cuMemcpy3D_v2 ,const CUDA_MEMCPY3D *,pCopy);
DEF_FN(CUresult,cuMemcpy3DPeer ,const CUDA_MEMCPY3D_PEER *,pCopy);
DEF_FN(CUresult,cuMemcpyAsync ,CUdeviceptr,dst,CUdeviceptr,src,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpyPeerAsync ,CUdeviceptr,dstDevice,CUcontext,dstContext,CUdeviceptr,srcDevice,CUcontext,srcContext,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpyHtoDAsync_v2 ,CUdeviceptr,dstDevice,const void *,srcHost,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpyDtoHAsync_v2 ,void *,dstHost,CUdeviceptr,srcDevice,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpyDtoDAsync_v2 ,CUdeviceptr,dstDevice,CUdeviceptr,srcDevice,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpyHtoAAsync_v2 ,CUarray,dstArray,size_t,dstOffset,const void *,srcHost,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpyAtoHAsync_v2 ,void *,dstHost,CUarray,srcArray,size_t,srcOffset,size_t,ByteCount,CUstream,hStream);
DEF_FN(CUresult,cuMemcpy2DAsync_v2 ,const CUDA_MEMCPY2D *,pCopy,CUstream,hStream);
DEF_FN(CUresult,cuMemcpy3DAsync_v2 ,const CUDA_MEMCPY3D *,pCopy,CUstream,hStream);
DEF_FN(CUresult,cuMemcpy3DPeerAsync ,const CUDA_MEMCPY3D_PEER *,pCopy,CUstream,hStream);
DEF_FN(CUresult,cuMemsetD8_v2 ,CUdeviceptr,dstDevice,unsigned char,uc,size_t,N);
DEF_FN(CUresult,cuMemsetD16_v2 ,CUdeviceptr,dstDevice,unsigned short,us,size_t,N);
DEF_FN(CUresult,cuMemsetD32_v2 ,CUdeviceptr,dstDevice,unsigned int,ui,size_t,N);
DEF_FN(CUresult,cuMemsetD2D8_v2 ,CUdeviceptr,dstDevice,size_t,dstPitch,unsigned char,uc,size_t,Width,size_t,Height);
DEF_FN(CUresult,cuMemsetD2D16_v2 ,CUdeviceptr,dstDevice,size_t,dstPitch,unsigned short,us,size_t,Width,size_t,Height);
DEF_FN(CUresult,cuMemsetD2D32_v2 ,CUdeviceptr,dstDevice,size_t,dstPitch,unsigned int,ui,size_t,Width,size_t,Height);
DEF_FN(CUresult,cuMemsetD8Async ,CUdeviceptr,dstDevice,unsigned char,uc,size_t,N,CUstream,hStream);
DEF_FN(CUresult,cuMemsetD16Async ,CUdeviceptr,dstDevice,unsigned short,us,size_t,N,CUstream,hStream);
DEF_FN(CUresult,cuMemsetD32Async ,CUdeviceptr,dstDevice,unsigned int,ui,size_t,N,CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D8Async ,CUdeviceptr,dstDevice,size_t,dstPitch,unsigned char,uc,size_t,Width,size_t,Height,CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D16Async ,CUdeviceptr,dstDevice,size_t,dstPitch,unsigned short,us,size_t,Width,size_t,Height,CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D32Async ,CUdeviceptr,dstDevice,size_t,dstPitch,unsigned int,ui,size_t,Width,size_t,Height,CUstream,hStream);
DEF_FN(CUresult,cuArrayCreate_v2 ,CUarray *,pHandle,const CUDA_ARRAY_DESCRIPTOR *,pAllocateArray);
DEF_FN(CUresult,cuArrayGetDescriptor_v2 ,CUDA_ARRAY_DESCRIPTOR *,pArrayDescriptor,CUarray,hArray);
DEF_FN(CUresult,cuArrayGetSparseProperties ,CUDA_ARRAY_SPARSE_PROPERTIES *,sparseProperties,CUarray,array);
DEF_FN(CUresult,cuMipmappedArrayGetSparseProperties ,CUDA_ARRAY_SPARSE_PROPERTIES *,sparseProperties,CUmipmappedArray,mipmap);
DEF_FN(CUresult,cuArrayGetMemoryRequirements ,CUDA_ARRAY_MEMORY_REQUIREMENTS *,memoryRequirements,CUarray,array,CUdevice,device);
DEF_FN(CUresult,cuMipmappedArrayGetMemoryRequirements ,CUDA_ARRAY_MEMORY_REQUIREMENTS *,memoryRequirements,CUmipmappedArray,mipmap,CUdevice,device);
DEF_FN(CUresult,cuArrayGetPlane ,CUarray *,pPlaneArray,CUarray,hArray,unsigned int,planeIdx);
DEF_FN(CUresult,cuArrayDestroy ,CUarray,hArray);
DEF_FN(CUresult,cuArray3DCreate_v2 ,CUarray *,pHandle,const CUDA_ARRAY3D_DESCRIPTOR *,pAllocateArray);
DEF_FN(CUresult,cuArray3DGetDescriptor_v2 ,CUDA_ARRAY3D_DESCRIPTOR *,pArrayDescriptor,CUarray,hArray);
DEF_FN(CUresult,cuMipmappedArrayCreate ,CUmipmappedArray *,pHandle,const CUDA_ARRAY3D_DESCRIPTOR *,pMipmappedArrayDesc,unsigned int,numMipmapLevels);
DEF_FN(CUresult,cuMipmappedArrayGetLevel ,CUarray *,pLevelArray,CUmipmappedArray,hMipmappedArray,unsigned int,level);
DEF_FN(CUresult,cuMipmappedArrayDestroy ,CUmipmappedArray,hMipmappedArray);
DEF_FN(CUresult,cuMemGetHandleForAddressRange ,void *,handle,CUdeviceptr,dptr,size_t,size,CUmemRangeHandleType,handleType,unsigned long long,flags);
DEF_FN(CUresult,cuMemAddressReserve ,CUdeviceptr *,ptr,size_t,size,size_t,alignment,CUdeviceptr,addr,unsigned long long,flags);
DEF_FN(CUresult,cuMemAddressFree ,CUdeviceptr,ptr,size_t,size);
DEF_FN(CUresult,cuMemCreate ,CUmemGenericAllocationHandle *,handle,size_t,size,const CUmemAllocationProp *,prop,unsigned long long,flags);
DEF_FN(CUresult,cuMemRelease ,CUmemGenericAllocationHandle,handle);
DEF_FN(CUresult,cuMemMap ,CUdeviceptr,ptr,size_t,size,size_t,offset,CUmemGenericAllocationHandle,handle,unsigned long long,flags);
DEF_FN(CUresult,cuMemMapArrayAsync ,CUarrayMapInfo *,mapInfoList,unsigned int,count,CUstream,hStream);
DEF_FN(CUresult,cuMemUnmap ,CUdeviceptr,ptr,size_t,size);
DEF_FN(CUresult,cuMemSetAccess ,CUdeviceptr,ptr,size_t,size,const CUmemAccessDesc *,desc,size_t,count);
DEF_FN(CUresult,cuMemGetAccess ,unsigned long long *,flags,const CUmemLocation *,location,CUdeviceptr,ptr);
DEF_FN(CUresult,cuMemExportToShareableHandle ,void *,shareableHandle,CUmemGenericAllocationHandle,handle,CUmemAllocationHandleType,handleType,unsigned long long,flags);
DEF_FN(CUresult,cuMemImportFromShareableHandle ,CUmemGenericAllocationHandle *,handle,void *,osHandle,CUmemAllocationHandleType,shHandleType);
DEF_FN(CUresult,cuMemGetAllocationGranularity ,size_t *,granularity,const CUmemAllocationProp *,prop,CUmemAllocationGranularity_flags,option);
DEF_FN(CUresult,cuMemGetAllocationPropertiesFromHandle ,CUmemAllocationProp *,prop,CUmemGenericAllocationHandle,handle);
DEF_FN(CUresult,cuMemRetainAllocationHandle ,CUmemGenericAllocationHandle *,handle,void *,addr);
DEF_FN(CUresult,cuMemFreeAsync ,CUdeviceptr,dptr,CUstream,hStream);
DEF_FN(CUresult,cuMemAllocAsync ,CUdeviceptr *,dptr,size_t,bytesize,CUstream,hStream);
DEF_FN(CUresult,cuMemPoolTrimTo ,CUmemoryPool,pool,size_t,minBytesToKeep);
DEF_FN(CUresult,cuMemPoolSetAttribute ,CUmemoryPool,pool,CUmemPool_attribute,attr,void *,value);
DEF_FN(CUresult,cuMemPoolGetAttribute ,CUmemoryPool,pool,CUmemPool_attribute,attr,void *,value);
DEF_FN(CUresult,cuMemPoolSetAccess ,CUmemoryPool,pool,const CUmemAccessDesc *,map,size_t,count);
DEF_FN(CUresult,cuMemPoolGetAccess ,CUmemAccess_flags *,flags,CUmemoryPool,memPool,CUmemLocation *,location);
DEF_FN(CUresult,cuMemPoolCreate ,CUmemoryPool *,pool,const CUmemPoolProps *,poolProps);
DEF_FN(CUresult,cuMemPoolDestroy ,CUmemoryPool,pool);
DEF_FN(CUresult,cuMemAllocFromPoolAsync ,CUdeviceptr *,dptr,size_t,bytesize,CUmemoryPool,pool,CUstream,hStream);
DEF_FN(CUresult,cuMemPoolExportToShareableHandle ,void *,handle_out,CUmemoryPool,pool,CUmemAllocationHandleType,handleType,unsigned long long,flags);
DEF_FN(CUresult,cuMemPoolImportFromShareableHandle ,CUmemoryPool *,pool_out,void *,handle,CUmemAllocationHandleType,handleType,unsigned long long,flags);
DEF_FN(CUresult,cuMemPoolExportPointer ,CUmemPoolPtrExportData *,shareData_out,CUdeviceptr,ptr);
DEF_FN(CUresult,cuMemPoolImportPointer ,CUdeviceptr *,ptr_out,CUmemoryPool,pool,CUmemPoolPtrExportData *,shareData);
DEF_FN(CUresult,cuMulticastCreate ,CUmemGenericAllocationHandle *,mcHandle,const CUmulticastObjectProp *,prop);
DEF_FN(CUresult,cuMulticastAddDevice ,CUmemGenericAllocationHandle,mcHandle,CUdevice,dev);
DEF_FN(CUresult,cuMulticastBindMem ,CUmemGenericAllocationHandle,mcHandle,size_t,mcOffset,CUmemGenericAllocationHandle,memHandle,size_t,memOffset,size_t,size,unsigned long long,flags);
DEF_FN(CUresult,cuMulticastBindAddr ,CUmemGenericAllocationHandle,mcHandle,size_t,mcOffset,CUdeviceptr,memptr,size_t,size,unsigned long long,flags);
DEF_FN(CUresult,cuMulticastUnbind ,CUmemGenericAllocationHandle,mcHandle,CUdevice,dev,size_t,mcOffset,size_t,size);
DEF_FN(CUresult,cuMulticastGetGranularity ,size_t *,granularity,const CUmulticastObjectProp *,prop,CUmulticastGranularity_flags,option);
DEF_FN(CUresult,cuPointerGetAttribute ,void *,data,CUpointer_attribute,attribute,CUdeviceptr,ptr);
DEF_FN(CUresult,cuMemPrefetchAsync ,CUdeviceptr,devPtr,size_t,count,CUdevice,dstDevice,CUstream,hStream);
DEF_FN(CUresult,cuMemPrefetchAsync_v2 ,CUdeviceptr,devPtr,size_t,count,CUmemLocation,location,unsigned int,flags,CUstream,hStream);
DEF_FN(CUresult,cuMemAdvise ,CUdeviceptr,devPtr,size_t,count,CUmem_advise,advice,CUdevice,device);
DEF_FN(CUresult,cuMemAdvise_v2 ,CUdeviceptr,devPtr,size_t,count,CUmem_advise,advice,CUmemLocation,location);
DEF_FN(CUresult,cuMemRangeGetAttribute ,void *,data,size_t,dataSize,CUmem_range_attribute,attribute,CUdeviceptr,devPtr,size_t,count);
DEF_FN(CUresult,cuMemRangeGetAttributes ,void * *,data,size_t *,dataSizes,CUmem_range_attribute *,attributes,size_t,numAttributes,CUdeviceptr,devPtr,size_t,count);
DEF_FN(CUresult,cuPointerSetAttribute ,const void *,value,CUpointer_attribute,attribute,CUdeviceptr,ptr);
DEF_FN(CUresult,cuPointerGetAttributes ,unsigned int,numAttributes,CUpointer_attribute *,attributes,void * *,data,CUdeviceptr,ptr);
DEF_FN(CUresult,cuStreamCreate ,CUstream *,phStream,unsigned int,Flags);
DEF_FN(CUresult,cuStreamCreateWithPriority ,CUstream *,phStream,unsigned int,flags,int,priority);
DEF_FN(CUresult,cuStreamGetPriority ,CUstream,hStream,int *,priority);
DEF_FN(CUresult,cuStreamGetFlags ,CUstream,hStream,unsigned int *,flags);
DEF_FN(CUresult,cuStreamGetId ,CUstream,hStream,unsigned long long *,streamId);
DEF_FN(CUresult,cuStreamGetCtx ,CUstream,hStream,CUcontext *,pctx);
DEF_FN(CUresult,cuStreamWaitEvent ,CUstream,hStream,CUevent,hEvent,unsigned int,Flags);
DEF_FN(CUresult,cuStreamAddCallback ,CUstream,hStream,CUstreamCallback,callback,void *,userData,unsigned int,flags);
DEF_FN(CUresult,cuStreamBeginCapture_v2 ,CUstream,hStream,CUstreamCaptureMode,mode);
DEF_FN(CUresult,cuStreamBeginCaptureToGraph ,CUstream,hStream,CUgraph,hGraph,const CUgraphNode *,dependencies,const CUgraphEdgeData *,dependencyData,size_t,numDependencies,CUstreamCaptureMode,mode);
DEF_FN(CUresult,cuThreadExchangeStreamCaptureMode ,CUstreamCaptureMode *,mode);
DEF_FN(CUresult,cuStreamEndCapture ,CUstream,hStream,CUgraph *,phGraph);
DEF_FN(CUresult,cuStreamIsCapturing ,CUstream,hStream,CUstreamCaptureStatus *,captureStatus);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v2 ,CUstream,hStream,CUstreamCaptureStatus *,captureStatus_out,cuuint64_t *,id_out,CUgraph *,graph_out,const CUgraphNode * *,dependencies_out,size_t *,numDependencies_out);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v3 ,CUstream,hStream,CUstreamCaptureStatus *,captureStatus_out,cuuint64_t *,id_out,CUgraph *,graph_out,const CUgraphNode * *,dependencies_out,const CUgraphEdgeData * *,edgeData_out,size_t *,numDependencies_out);
DEF_FN(CUresult,cuStreamUpdateCaptureDependencies ,CUstream,hStream,CUgraphNode *,dependencies,size_t,numDependencies,unsigned int,flags);
DEF_FN(CUresult,cuStreamUpdateCaptureDependencies_v2 ,CUstream,hStream,CUgraphNode *,dependencies,const CUgraphEdgeData *,dependencyData,size_t,numDependencies,unsigned int,flags);
DEF_FN(CUresult,cuStreamAttachMemAsync ,CUstream,hStream,CUdeviceptr,dptr,size_t,length,unsigned int,flags);
DEF_FN(CUresult,cuStreamQuery ,CUstream,hStream);
DEF_FN(CUresult,cuStreamSynchronize ,CUstream,hStream);
DEF_FN(CUresult,cuStreamDestroy_v2 ,CUstream,hStream);
DEF_FN(CUresult,cuStreamCopyAttributes ,CUstream,dst,CUstream,src);
DEF_FN(CUresult,cuStreamGetAttribute ,CUstream,hStream,CUstreamAttrID,attr,CUstreamAttrValue *,value_out);
DEF_FN(CUresult,cuStreamSetAttribute ,CUstream,hStream,CUstreamAttrID,attr,const CUstreamAttrValue *,value);
DEF_FN(CUresult,cuEventCreate ,CUevent *,phEvent,unsigned int,Flags);
DEF_FN(CUresult,cuEventRecord ,CUevent,hEvent,CUstream,hStream);
DEF_FN(CUresult,cuEventRecordWithFlags ,CUevent,hEvent,CUstream,hStream,unsigned int,flags);
DEF_FN(CUresult,cuEventQuery ,CUevent,hEvent);
DEF_FN(CUresult,cuEventSynchronize ,CUevent,hEvent);
DEF_FN(CUresult,cuEventDestroy_v2 ,CUevent,hEvent);
DEF_FN(CUresult,cuEventElapsedTime ,float *,pMilliseconds,CUevent,hStart,CUevent,hEnd);
DEF_FN(CUresult,cuImportExternalMemory ,CUexternalMemory *,extMem_out,const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *,memHandleDesc);
DEF_FN(CUresult,cuExternalMemoryGetMappedBuffer ,CUdeviceptr *,devPtr,CUexternalMemory,extMem,const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *,bufferDesc);
DEF_FN(CUresult,cuExternalMemoryGetMappedMipmappedArray ,CUmipmappedArray *,mipmap,CUexternalMemory,extMem,const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *,mipmapDesc);
DEF_FN(CUresult,cuDestroyExternalMemory ,CUexternalMemory,extMem);
DEF_FN(CUresult,cuImportExternalSemaphore ,CUexternalSemaphore *,extSem_out,const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *,semHandleDesc);
DEF_FN(CUresult,cuSignalExternalSemaphoresAsync ,const CUexternalSemaphore *,extSemArray,const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *,paramsArray,unsigned int,numExtSems,CUstream,stream);
DEF_FN(CUresult,cuWaitExternalSemaphoresAsync ,const CUexternalSemaphore *,extSemArray,const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *,paramsArray,unsigned int,numExtSems,CUstream,stream);
DEF_FN(CUresult,cuDestroyExternalSemaphore ,CUexternalSemaphore,extSem);
DEF_FN(CUresult,cuStreamWaitValue32_v2 ,CUstream,stream,CUdeviceptr,addr,cuuint32_t,value,unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue64_v2 ,CUstream,stream,CUdeviceptr,addr,cuuint64_t,value,unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue32_v2 ,CUstream,stream,CUdeviceptr,addr,cuuint32_t,value,unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue64_v2 ,CUstream,stream,CUdeviceptr,addr,cuuint64_t,value,unsigned int,flags);
DEF_FN(CUresult,cuStreamBatchMemOp_v2 ,CUstream,stream,unsigned int,count,CUstreamBatchMemOpParams *,paramArray,unsigned int,flags);
DEF_FN(CUresult,cuFuncGetAttribute ,int *,pi,CUfunction_attribute,attrib,CUfunction,hfunc);
DEF_FN(CUresult,cuFuncSetAttribute ,CUfunction,hfunc,CUfunction_attribute,attrib,int,value);
DEF_FN(CUresult,cuFuncSetCacheConfig ,CUfunction,hfunc,CUfunc_cache,config);
DEF_FN(CUresult,cuFuncGetModule ,CUmodule *,hmod,CUfunction,hfunc);
DEF_FN(CUresult,cuFuncGetName ,const char * *,name,CUfunction,hfunc);
DEF_FN(CUresult,cuFuncGetParamInfo ,CUfunction,func,size_t,paramIndex,size_t *,paramOffset,size_t *,paramSize);
DEF_FN(CUresult,cuFuncIsLoaded ,CUfunctionLoadingState *,state,CUfunction,function);
DEF_FN(CUresult,cuFuncLoad ,CUfunction,function);
DEF_FN(CUresult,cuLaunchKernelEx ,const CUlaunchConfig *,config,CUfunction,f,void * *,kernelParams,void * *,extra);
DEF_FN(CUresult,cuLaunchCooperativeKernel ,CUfunction,f,unsigned int,gridDimX,unsigned int,gridDimY,unsigned int,gridDimZ,unsigned int,blockDimX,unsigned int,blockDimY,unsigned int,blockDimZ,unsigned int,sharedMemBytes,CUstream,hStream,void * *,kernelParams);
DEF_FN(CUresult,cuLaunchCooperativeKernelMultiDevice ,CUDA_LAUNCH_PARAMS *,launchParamsList,unsigned int,numDevices,unsigned int,flags);
DEF_FN(CUresult,cuLaunchHostFunc ,CUstream,hStream,CUhostFn,fn,void *,userData);
DEF_FN(CUresult,cuFuncSetBlockShape ,CUfunction,hfunc,int,x,int,y,int,z);
DEF_FN(CUresult,cuFuncSetSharedSize ,CUfunction,hfunc,unsigned int,bytes);
DEF_FN(CUresult,cuParamSetSize ,CUfunction,hfunc,unsigned int,numbytes);
DEF_FN(CUresult,cuParamSeti ,CUfunction,hfunc,int,offset,unsigned int,value);
DEF_FN(CUresult,cuParamSetf ,CUfunction,hfunc,int,offset,float,value);
DEF_FN(CUresult,cuParamSetv ,CUfunction,hfunc,int,offset,void *,ptr,unsigned int,numbytes);
DEF_FN(CUresult,cuLaunch ,CUfunction,f);
DEF_FN(CUresult,cuLaunchGrid ,CUfunction,f,int,grid_width,int,grid_height);
DEF_FN(CUresult,cuLaunchGridAsync ,CUfunction,f,int,grid_width,int,grid_height,CUstream,hStream);
DEF_FN(CUresult,cuParamSetTexRef ,CUfunction,hfunc,int,texunit,CUtexref,hTexRef);
DEF_FN(CUresult,cuFuncSetSharedMemConfig ,CUfunction,hfunc,CUsharedconfig,config);
DEF_FN(CUresult,cuGraphCreate ,CUgraph *,phGraph,unsigned int,flags);
DEF_FN(CUresult,cuGraphAddKernelNode_v2 ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_KERNEL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphKernelNodeGetParams_v2 ,CUgraphNode,hNode,CUDA_KERNEL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphKernelNodeSetParams_v2 ,CUgraphNode,hNode,const CUDA_KERNEL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphAddMemcpyNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_MEMCPY3D *,copyParams,CUcontext,ctx);
DEF_FN(CUresult,cuGraphMemcpyNodeGetParams ,CUgraphNode,hNode,CUDA_MEMCPY3D *,nodeParams);
DEF_FN(CUresult,cuGraphMemcpyNodeSetParams ,CUgraphNode,hNode,const CUDA_MEMCPY3D *,nodeParams);
DEF_FN(CUresult,cuGraphAddMemsetNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_MEMSET_NODE_PARAMS *,memsetParams,CUcontext,ctx);
DEF_FN(CUresult,cuGraphMemsetNodeGetParams ,CUgraphNode,hNode,CUDA_MEMSET_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphMemsetNodeSetParams ,CUgraphNode,hNode,const CUDA_MEMSET_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphAddHostNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_HOST_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphHostNodeGetParams ,CUgraphNode,hNode,CUDA_HOST_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphHostNodeSetParams ,CUgraphNode,hNode,const CUDA_HOST_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphAddChildGraphNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,CUgraph,childGraph);
DEF_FN(CUresult,cuGraphChildGraphNodeGetGraph ,CUgraphNode,hNode,CUgraph *,phGraph);
DEF_FN(CUresult,cuGraphAddEmptyNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies);
DEF_FN(CUresult,cuGraphAddEventRecordNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,CUevent,event);
DEF_FN(CUresult,cuGraphEventRecordNodeGetEvent ,CUgraphNode,hNode,CUevent *,event_out);
DEF_FN(CUresult,cuGraphEventRecordNodeSetEvent ,CUgraphNode,hNode,CUevent,event);
DEF_FN(CUresult,cuGraphAddEventWaitNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,CUevent,event);
DEF_FN(CUresult,cuGraphEventWaitNodeGetEvent ,CUgraphNode,hNode,CUevent *,event_out);
DEF_FN(CUresult,cuGraphEventWaitNodeSetEvent ,CUgraphNode,hNode,CUevent,event);
DEF_FN(CUresult,cuGraphAddExternalSemaphoresSignalNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphExternalSemaphoresSignalNodeGetParams ,CUgraphNode,hNode,CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *,params_out);
DEF_FN(CUresult,cuGraphExternalSemaphoresSignalNodeSetParams ,CUgraphNode,hNode,const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphAddExternalSemaphoresWaitNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_EXT_SEM_WAIT_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphExternalSemaphoresWaitNodeGetParams ,CUgraphNode,hNode,CUDA_EXT_SEM_WAIT_NODE_PARAMS *,params_out);
DEF_FN(CUresult,cuGraphExternalSemaphoresWaitNodeSetParams ,CUgraphNode,hNode,const CUDA_EXT_SEM_WAIT_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphAddBatchMemOpNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,const CUDA_BATCH_MEM_OP_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphBatchMemOpNodeGetParams ,CUgraphNode,hNode,CUDA_BATCH_MEM_OP_NODE_PARAMS *,nodeParams_out);
DEF_FN(CUresult,cuGraphBatchMemOpNodeSetParams ,CUgraphNode,hNode,const CUDA_BATCH_MEM_OP_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphExecBatchMemOpNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_BATCH_MEM_OP_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphAddMemAllocNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,CUDA_MEM_ALLOC_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphMemAllocNodeGetParams ,CUgraphNode,hNode,CUDA_MEM_ALLOC_NODE_PARAMS *,params_out);
DEF_FN(CUresult,cuGraphAddMemFreeNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,CUdeviceptr,dptr);
DEF_FN(CUresult,cuGraphMemFreeNodeGetParams ,CUgraphNode,hNode,CUdeviceptr *,dptr_out);
DEF_FN(CUresult,cuDeviceGraphMemTrim ,CUdevice,device);
DEF_FN(CUresult,cuDeviceGetGraphMemAttribute ,CUdevice,device,CUgraphMem_attribute,attr,void *,value);
DEF_FN(CUresult,cuDeviceSetGraphMemAttribute ,CUdevice,device,CUgraphMem_attribute,attr,void *,value);
DEF_FN(CUresult,cuGraphClone ,CUgraph *,phGraphClone,CUgraph,originalGraph);
DEF_FN(CUresult,cuGraphNodeFindInClone ,CUgraphNode *,phNode,CUgraphNode,hOriginalNode,CUgraph,hClonedGraph);
DEF_FN(CUresult,cuGraphNodeGetType ,CUgraphNode,hNode,CUgraphNodeType *,type);
DEF_FN(CUresult,cuGraphGetNodes ,CUgraph,hGraph,CUgraphNode *,nodes,size_t *,numNodes);
DEF_FN(CUresult,cuGraphGetRootNodes ,CUgraph,hGraph,CUgraphNode *,rootNodes,size_t *,numRootNodes);
DEF_FN(CUresult,cuGraphGetEdges ,CUgraph,hGraph,CUgraphNode *,from,CUgraphNode *,to,size_t *,numEdges);
DEF_FN(CUresult,cuGraphGetEdges_v2 ,CUgraph,hGraph,CUgraphNode *,from,CUgraphNode *,to,CUgraphEdgeData *,edgeData,size_t *,numEdges);
DEF_FN(CUresult,cuGraphNodeGetDependencies ,CUgraphNode,hNode,CUgraphNode *,dependencies,size_t *,numDependencies);
DEF_FN(CUresult,cuGraphNodeGetDependencies_v2 ,CUgraphNode,hNode,CUgraphNode *,dependencies,CUgraphEdgeData *,edgeData,size_t *,numDependencies);
DEF_FN(CUresult,cuGraphNodeGetDependentNodes ,CUgraphNode,hNode,CUgraphNode *,dependentNodes,size_t *,numDependentNodes);
DEF_FN(CUresult,cuGraphNodeGetDependentNodes_v2 ,CUgraphNode,hNode,CUgraphNode *,dependentNodes,CUgraphEdgeData *,edgeData,size_t *,numDependentNodes);
DEF_FN(CUresult,cuGraphAddDependencies ,CUgraph,hGraph,const CUgraphNode *,from,const CUgraphNode *,to,size_t,numDependencies);
DEF_FN(CUresult,cuGraphAddDependencies_v2 ,CUgraph,hGraph,const CUgraphNode *,from,const CUgraphNode *,to,const CUgraphEdgeData *,edgeData,size_t,numDependencies);
DEF_FN(CUresult,cuGraphRemoveDependencies ,CUgraph,hGraph,const CUgraphNode *,from,const CUgraphNode *,to,size_t,numDependencies);
DEF_FN(CUresult,cuGraphRemoveDependencies_v2 ,CUgraph,hGraph,const CUgraphNode *,from,const CUgraphNode *,to,const CUgraphEdgeData *,edgeData,size_t,numDependencies);
DEF_FN(CUresult,cuGraphDestroyNode ,CUgraphNode,hNode);
DEF_FN(CUresult,cuGraphInstantiateWithFlags ,CUgraphExec *,phGraphExec,CUgraph,hGraph,unsigned long long,flags);
DEF_FN(CUresult,cuGraphInstantiateWithParams ,CUgraphExec *,phGraphExec,CUgraph,hGraph,CUDA_GRAPH_INSTANTIATE_PARAMS *,instantiateParams);
DEF_FN(CUresult,cuGraphExecGetFlags ,CUgraphExec,hGraphExec,cuuint64_t *,flags);
DEF_FN(CUresult,cuGraphExecKernelNodeSetParams_v2 ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_KERNEL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphExecMemcpyNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_MEMCPY3D *,copyParams,CUcontext,ctx);
DEF_FN(CUresult,cuGraphExecMemsetNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_MEMSET_NODE_PARAMS *,memsetParams,CUcontext,ctx);
DEF_FN(CUresult,cuGraphExecHostNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_HOST_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphExecChildGraphNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,CUgraph,childGraph);
DEF_FN(CUresult,cuGraphExecEventRecordNodeSetEvent ,CUgraphExec,hGraphExec,CUgraphNode,hNode,CUevent,event);
DEF_FN(CUresult,cuGraphExecEventWaitNodeSetEvent ,CUgraphExec,hGraphExec,CUgraphNode,hNode,CUevent,event);
DEF_FN(CUresult,cuGraphExecExternalSemaphoresSignalNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphExecExternalSemaphoresWaitNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,const CUDA_EXT_SEM_WAIT_NODE_PARAMS *,nodeParams);
DEF_FN(CUresult,cuGraphNodeSetEnabled ,CUgraphExec,hGraphExec,CUgraphNode,hNode,unsigned int,isEnabled);
DEF_FN(CUresult,cuGraphNodeGetEnabled ,CUgraphExec,hGraphExec,CUgraphNode,hNode,unsigned int *,isEnabled);
DEF_FN(CUresult,cuGraphUpload ,CUgraphExec,hGraphExec,CUstream,hStream);
DEF_FN(CUresult,cuGraphLaunch ,CUgraphExec,hGraphExec,CUstream,hStream);
DEF_FN(CUresult,cuGraphExecDestroy ,CUgraphExec,hGraphExec);
DEF_FN(CUresult,cuGraphDestroy ,CUgraph,hGraph);
DEF_FN(CUresult,cuGraphExecUpdate_v2 ,CUgraphExec,hGraphExec,CUgraph,hGraph,CUgraphExecUpdateResultInfo *,resultInfo);
DEF_FN(CUresult,cuGraphKernelNodeCopyAttributes ,CUgraphNode,dst,CUgraphNode,src);
DEF_FN(CUresult,cuGraphKernelNodeGetAttribute ,CUgraphNode,hNode,CUkernelNodeAttrID,attr,CUkernelNodeAttrValue *,value_out);
DEF_FN(CUresult,cuGraphKernelNodeSetAttribute ,CUgraphNode,hNode,CUkernelNodeAttrID,attr,const CUkernelNodeAttrValue *,value);
DEF_FN(CUresult,cuGraphDebugDotPrint ,CUgraph,hGraph,const char *,path,unsigned int,flags);
DEF_FN(CUresult,cuUserObjectCreate ,CUuserObject *,object_out,void *,ptr,CUhostFn,destroy,unsigned int,initialRefcount,unsigned int,flags);
DEF_FN(CUresult,cuUserObjectRetain ,CUuserObject,object,unsigned int,count);
DEF_FN(CUresult,cuUserObjectRelease ,CUuserObject,object,unsigned int,count);
DEF_FN(CUresult,cuGraphRetainUserObject ,CUgraph,graph,CUuserObject,object,unsigned int,count,unsigned int,flags);
DEF_FN(CUresult,cuGraphReleaseUserObject ,CUgraph,graph,CUuserObject,object,unsigned int,count);
DEF_FN(CUresult,cuGraphAddNode ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,size_t,numDependencies,CUgraphNodeParams *,nodeParams);
DEF_FN(CUresult,cuGraphAddNode_v2 ,CUgraphNode *,phGraphNode,CUgraph,hGraph,const CUgraphNode *,dependencies,const CUgraphEdgeData *,dependencyData,size_t,numDependencies,CUgraphNodeParams *,nodeParams);
DEF_FN(CUresult,cuGraphNodeSetParams ,CUgraphNode,hNode,CUgraphNodeParams *,nodeParams);
DEF_FN(CUresult,cuGraphExecNodeSetParams ,CUgraphExec,hGraphExec,CUgraphNode,hNode,CUgraphNodeParams *,nodeParams);
DEF_FN(CUresult,cuGraphConditionalHandleCreate ,CUgraphConditionalHandle *,pHandle_out,CUgraph,hGraph,CUcontext,ctx,unsigned int,defaultLaunchValue,unsigned int,flags);
DEF_FN(CUresult,cuOccupancyMaxActiveBlocksPerMultiprocessor ,int *,numBlocks,CUfunction,func,int,blockSize,size_t,dynamicSMemSize);
DEF_FN(CUresult,cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags ,int *,numBlocks,CUfunction,func,int,blockSize,size_t,dynamicSMemSize,unsigned int,flags);
DEF_FN(CUresult,cuOccupancyMaxPotentialBlockSize ,int *,minGridSize,int *,blockSize,CUfunction,func,CUoccupancyB2DSize,blockSizeToDynamicSMemSize,size_t,dynamicSMemSize,int,blockSizeLimit);
DEF_FN(CUresult,cuOccupancyMaxPotentialBlockSizeWithFlags ,int *,minGridSize,int *,blockSize,CUfunction,func,CUoccupancyB2DSize,blockSizeToDynamicSMemSize,size_t,dynamicSMemSize,int,blockSizeLimit,unsigned int,flags);
DEF_FN(CUresult,cuOccupancyAvailableDynamicSMemPerBlock ,size_t *,dynamicSmemSize,CUfunction,func,int,numBlocks,int,blockSize);
DEF_FN(CUresult,cuOccupancyMaxPotentialClusterSize ,int *,clusterSize,CUfunction,func,const CUlaunchConfig *,config);
DEF_FN(CUresult,cuOccupancyMaxActiveClusters ,int *,numClusters,CUfunction,func,const CUlaunchConfig *,config);
DEF_FN(CUresult,cuTexRefSetArray ,CUtexref,hTexRef,CUarray,hArray,unsigned int,Flags);
DEF_FN(CUresult,cuTexRefSetMipmappedArray ,CUtexref,hTexRef,CUmipmappedArray,hMipmappedArray,unsigned int,Flags);
DEF_FN(CUresult,cuTexRefSetAddress_v2 ,size_t *,ByteOffset,CUtexref,hTexRef,CUdeviceptr,dptr,size_t,bytes);
DEF_FN(CUresult,cuTexRefSetAddress2D_v3 ,CUtexref,hTexRef,const CUDA_ARRAY_DESCRIPTOR *,desc,CUdeviceptr,dptr,size_t,Pitch);
DEF_FN(CUresult,cuTexRefSetFormat ,CUtexref,hTexRef,CUarray_format,fmt,int,NumPackedComponents);
DEF_FN(CUresult,cuTexRefSetAddressMode ,CUtexref,hTexRef,int,dim,CUaddress_mode,am);
DEF_FN(CUresult,cuTexRefSetFilterMode ,CUtexref,hTexRef,CUfilter_mode,fm);
DEF_FN(CUresult,cuTexRefSetMipmapFilterMode ,CUtexref,hTexRef,CUfilter_mode,fm);
DEF_FN(CUresult,cuTexRefSetMipmapLevelBias ,CUtexref,hTexRef,float,bias);
DEF_FN(CUresult,cuTexRefSetMipmapLevelClamp ,CUtexref,hTexRef,float,minMipmapLevelClamp,float,maxMipmapLevelClamp);
DEF_FN(CUresult,cuTexRefSetMaxAnisotropy ,CUtexref,hTexRef,unsigned int,maxAniso);
DEF_FN(CUresult,cuTexRefSetBorderColor ,CUtexref,hTexRef,float *,pBorderColor);
DEF_FN(CUresult,cuTexRefSetFlags ,CUtexref,hTexRef,unsigned int,Flags);
DEF_FN(CUresult,cuTexRefGetAddress_v2 ,CUdeviceptr *,pdptr,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetArray ,CUarray *,phArray,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmappedArray ,CUmipmappedArray *,phMipmappedArray,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetAddressMode ,CUaddress_mode *,pam,CUtexref,hTexRef,int,dim);
DEF_FN(CUresult,cuTexRefGetFilterMode ,CUfilter_mode *,pfm,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetFormat ,CUarray_format *,pFormat,int *,pNumChannels,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmapFilterMode ,CUfilter_mode *,pfm,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmapLevelBias ,float *,pbias,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmapLevelClamp ,float *,pminMipmapLevelClamp,float *,pmaxMipmapLevelClamp,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMaxAnisotropy ,int *,pmaxAniso,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetBorderColor ,float *,pBorderColor,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetFlags ,unsigned int *,pFlags,CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefCreate ,CUtexref *,pTexRef);
DEF_FN(CUresult,cuTexRefDestroy ,CUtexref,hTexRef);
DEF_FN(CUresult,cuSurfRefSetArray ,CUsurfref,hSurfRef,CUarray,hArray,unsigned int,Flags);
DEF_FN(CUresult,cuSurfRefGetArray ,CUarray *,phArray,CUsurfref,hSurfRef);
DEF_FN(CUresult,cuTexObjectCreate ,CUtexObject *,pTexObject,const CUDA_RESOURCE_DESC *,pResDesc,const CUDA_TEXTURE_DESC *,pTexDesc,const CUDA_RESOURCE_VIEW_DESC *,pResViewDesc);
DEF_FN(CUresult,cuTexObjectDestroy ,CUtexObject,texObject);
DEF_FN(CUresult,cuTexObjectGetResourceDesc ,CUDA_RESOURCE_DESC *,pResDesc,CUtexObject,texObject);
DEF_FN(CUresult,cuTexObjectGetTextureDesc ,CUDA_TEXTURE_DESC *,pTexDesc,CUtexObject,texObject);
DEF_FN(CUresult,cuTexObjectGetResourceViewDesc ,CUDA_RESOURCE_VIEW_DESC *,pResViewDesc,CUtexObject,texObject);
DEF_FN(CUresult,cuSurfObjectCreate ,CUsurfObject *,pSurfObject,const CUDA_RESOURCE_DESC *,pResDesc);
DEF_FN(CUresult,cuSurfObjectDestroy ,CUsurfObject,surfObject);
DEF_FN(CUresult,cuSurfObjectGetResourceDesc ,CUDA_RESOURCE_DESC *,pResDesc,CUsurfObject,surfObject);
DEF_FN(CUresult,cuTensorMapEncodeTiled ,CUtensorMap *,tensorMap,CUtensorMapDataType,tensorDataType,cuuint32_t,tensorRank,void *,globalAddress,const cuuint64_t *,globalDim,const cuuint64_t *,globalStrides,const cuuint32_t *,boxDim,const cuuint32_t *,elementStrides,CUtensorMapInterleave,interleave,CUtensorMapSwizzle,swizzle,CUtensorMapL2promotion,l2Promotion,CUtensorMapFloatOOBfill,oobFill);
DEF_FN(CUresult,cuTensorMapEncodeIm2col ,CUtensorMap *,tensorMap,CUtensorMapDataType,tensorDataType,cuuint32_t,tensorRank,void *,globalAddress,const cuuint64_t *,globalDim,const cuuint64_t *,globalStrides,const int *,pixelBoxLowerCorner,const int *,pixelBoxUpperCorner,cuuint32_t,channelsPerPixel,cuuint32_t,pixelsPerColumn,const cuuint32_t *,elementStrides,CUtensorMapInterleave,interleave,CUtensorMapSwizzle,swizzle,CUtensorMapL2promotion,l2Promotion,CUtensorMapFloatOOBfill,oobFill);
DEF_FN(CUresult,cuTensorMapReplaceAddress ,CUtensorMap *,tensorMap,void *,globalAddress);
DEF_FN(CUresult,cuDeviceCanAccessPeer ,int *,canAccessPeer,CUdevice,dev,CUdevice,peerDev);
DEF_FN(CUresult,cuCtxEnablePeerAccess ,CUcontext,peerContext,unsigned int,Flags);
DEF_FN(CUresult,cuCtxDisablePeerAccess ,CUcontext,peerContext);
DEF_FN(CUresult,cuDeviceGetP2PAttribute ,int *,value,CUdevice_P2PAttribute,attrib,CUdevice,srcDevice,CUdevice,dstDevice);
DEF_FN(CUresult,cuGraphicsUnregisterResource ,CUgraphicsResource,resource);
DEF_FN(CUresult,cuGraphicsSubResourceGetMappedArray ,CUarray *,pArray,CUgraphicsResource,resource,unsigned int,arrayIndex,unsigned int,mipLevel);
DEF_FN(CUresult,cuGraphicsResourceGetMappedMipmappedArray ,CUmipmappedArray *,pMipmappedArray,CUgraphicsResource,resource);
DEF_FN(CUresult,cuGraphicsResourceGetMappedPointer_v2 ,CUdeviceptr *,pDevPtr,size_t *,pSize,CUgraphicsResource,resource);
DEF_FN(CUresult,cuGraphicsResourceSetMapFlags_v2 ,CUgraphicsResource,resource,unsigned int,flags);
DEF_FN(CUresult,cuGraphicsMapResources ,unsigned int,count,CUgraphicsResource *,resources,CUstream,hStream);
DEF_FN(CUresult,cuGraphicsUnmapResources ,unsigned int,count,CUgraphicsResource *,resources,CUstream,hStream);
DEF_FN(CUresult,cuCoredumpGetAttribute ,CUcoredumpSettings,attrib,void *,value,size_t *,size);
DEF_FN(CUresult,cuCoredumpGetAttributeGlobal ,CUcoredumpSettings,attrib,void *,value,size_t *,size);
DEF_FN(CUresult,cuCoredumpSetAttribute ,CUcoredumpSettings,attrib,void *,value,size_t *,size);
DEF_FN(CUresult,cuCoredumpSetAttributeGlobal ,CUcoredumpSettings,attrib,void *,value,size_t *,size);
DEF_FN(CUresult,cuGetExportTable ,const void * *,ppExportTable,const CUuuid *,pExportTableId);
DEF_FN(CUresult,cuGreenCtxCreate ,CUgreenCtx *,phCtx,CUdevResourceDesc,desc,CUdevice,dev,unsigned int,flags);
DEF_FN(CUresult,cuGreenCtxDestroy ,CUgreenCtx,hCtx);
DEF_FN(CUresult,cuCtxFromGreenCtx ,CUcontext *,pContext,CUgreenCtx,hCtx);
DEF_FN(CUresult,cuDeviceGetDevResource ,CUdevice,device,CUdevResource *,resource,CUdevResourceType,type);
DEF_FN(CUresult,cuCtxGetDevResource ,CUcontext,hCtx,CUdevResource *,resource,CUdevResourceType,type);
DEF_FN(CUresult,cuGreenCtxGetDevResource ,CUgreenCtx,hCtx,CUdevResource *,resource,CUdevResourceType,type);
DEF_FN(CUresult,cuDevSmResourceSplitByCount ,CUdevResource *,result,unsigned int *,nbGroups,const CUdevResource *,input,CUdevResource *,remaining,unsigned int,useFlags,unsigned int,minCount);
DEF_FN(CUresult,cuDevResourceGenerateDesc ,CUdevResourceDesc *,phDesc,CUdevResource *,resources,unsigned int,nbResources);
DEF_FN(CUresult,cuGreenCtxRecordEvent ,CUgreenCtx,hCtx,CUevent,hEvent);
DEF_FN(CUresult,cuGreenCtxWaitEvent ,CUgreenCtx,hCtx,CUevent,hEvent);
DEF_FN(CUresult,cuStreamGetGreenCtx ,CUstream,hStream,CUgreenCtx *,phCtx);

CUresult cuGetProcAddress(const char * symbol, void **pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus) {
    CUresult result = realCuGetProcAddress(symbol, pfn, cudaVersion, flags, symbolStatus);
    printf("Intercepted cuGetProcAddress: Requesting symbol %s (flags=%lu, version=%d): %p\n", symbol, flags, cudaVersion, *pfn);

	if (cuDriverFunctionTable.empty()){
		cuDriverFunctionTable.insert({
		{"cuDeviceGetName", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDeviceGetName))},
		{"cuInit", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuInit))},
		{"cuModuleGetLoadingMode", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuModuleGetLoadingMode))},
		{"cuDeviceGetCount", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDeviceGetCount))},
		{"cuDeviceGetUuid",CuDriverFunction(0,0,reinterpret_cast<void *>(&cuDeviceGetUuid))},
		{"cuDriverGetVersion", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDriverGetVersion))},
		{"cuDeviceGet", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDeviceGet))},
		{"cuDeviceGetAttribute", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDeviceGetAttribute))},
		{"cuCtxSetCurrent", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuCtxSetCurrent))},
		{"cuCtxGetCurrent", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuCtxGetCurrent))},
		{"cuDevicePrimaryCtxRetain", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDevicePrimaryCtxRetain))},
		{"cuDevicePrimaryCtxRelease", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuDevicePrimaryCtxRelease))},
		{"cuMemcpyHtoD", CuDriverFunction(0, 0, reinterpret_cast<void*>(&cuMemcpyHtoD))},
		{"cuLibraryLoadData",CuDriverFunction(0,0,reinterpret_cast<void*>(&cuLibraryLoadData))},
		{"cuLibraryGetModule",CuDriverFunction(0,0,reinterpret_cast<void*>(&cuLibraryGetModule))},
		{"cuModuleGetFunction",CuDriverFunction(0,0,reinterpret_cast<void*>(&cuModuleGetFunction))},
		{"cuMemAlloc",CuDriverFunction(0,0,reinterpret_cast<void*>(&cuMemAlloc))},
		{"cuMemFree",CuDriverFunction(0,0,reinterpret_cast<void*>(&cuMemFree))},

	});
	}
    if (strcmp(symbol, "cuGetProcAddress") == 0) {
        *pfn = (void*)&cuGetProcAddress;  // 拦截自身

    }
	else if(cuDriverFunctionTable.find(symbol)!=cuDriverFunctionTable.end()){
		printf("cuGetProcAddress read from cuDiverFunctionTable: Requesting symbol %s (flags=%lu, version=%d): %p\n", symbol,cuDriverFunctionTable[symbol].flags, cuDriverFunctionTable[symbol].cudaVersion, cuDriverFunctionTable[symbol].funcPtr);
		*pfn=(void*)cuDriverFunctionTable[symbol].funcPtr;
	}

	ELSE_IF(cuGetErrorString,CUresult, const char * *)
	ELSE_IF(cuGetErrorName,CUresult, const char * *)
	// ELSE_IF(cuDeviceGetUuid,CUuuid *, CUdevice)
	// ELSE_IF(cuDeviceGetUuid_v2,CUuuid *, CUdevice)
	ELSE_IF(cuDeviceGetLuid,char *, unsigned int *, CUdevice)
	// ELSE_IF(cuDeviceTotalMem_v2,size_t *, CUdevice)
	ELSE_IF(cuDeviceGetTexture1DLinearMaxWidth,size_t *, CUarray_format, unsigned, CUdevice)
	ELSE_IF(cuDeviceGetNvSciSyncAttributes,void *, CUdevice, int)
	ELSE_IF(cuDeviceSetMemPool,CUdevice, CUmemoryPool)
	ELSE_IF(cuDeviceGetMemPool,CUmemoryPool *, CUdevice)
	ELSE_IF(cuDeviceGetDefaultMemPool,CUmemoryPool *, CUdevice)
	ELSE_IF(cuDeviceGetExecAffinitySupport,int *, CUexecAffinityType, CUdevice)
	ELSE_IF(cuFlushGPUDirectRDMAWrites,CUflushGPUDirectRDMAWritesTarget, CUflushGPUDirectRDMAWritesScope)
	ELSE_IF(cuDeviceGetProperties,CUdevprop *, CUdevice)
	ELSE_IF(cuDeviceComputeCapability,int *, int *, CUdevice)
	ELSE_IF(cuDevicePrimaryCtxSetFlags_v2,CUdevice, unsigned int)
	ELSE_IF(cuDevicePrimaryCtxGetState,CUdevice, unsigned int *, int *)
	ELSE_IF(cuDevicePrimaryCtxReset_v2,CUdevice)
	ELSE_IF(cuCtxCreate_v2,CUcontext *, unsigned int, CUdevice)
	ELSE_IF(cuCtxCreate_v3,CUcontext *, CUexecAffinityParam *, int, unsigned int, CUdevice)
	ELSE_IF(cuCtxDestroy_v2,CUcontext)
	ELSE_IF(cuCtxPushCurrent_v2,CUcontext)
	ELSE_IF(cuCtxPopCurrent_v2,CUcontext *)
	ELSE_IF(cuCtxGetDevice,CUdevice *)
	ELSE_IF(cuCtxGetFlags,unsigned int *)
	ELSE_IF(cuCtxSetFlags,unsigned int)
	ELSE_IF(cuCtxGetId,CUcontext, unsigned long long *)
	ELSE_IF(cuCtxSynchronize,void)
	ELSE_IF(cuCtxSetLimit,CUlimit, size_t)
	ELSE_IF(cuCtxGetLimit,size_t *, CUlimit)
	ELSE_IF(cuCtxGetCacheConfig,CUfunc_cache *)
	ELSE_IF(cuCtxSetCacheConfig,CUfunc_cache)
	ELSE_IF(cuCtxGetApiVersion,CUcontext, unsigned int *)
	ELSE_IF(cuCtxGetStreamPriorityRange,int *, int *)
	ELSE_IF(cuCtxResetPersistingL2Cache,void)
	ELSE_IF(cuCtxGetExecAffinity,CUexecAffinityParam *, CUexecAffinityType)
	ELSE_IF(cuCtxAttach,CUcontext *, unsigned int)
	ELSE_IF(cuCtxDetach,CUcontext)
	ELSE_IF(cuCtxGetSharedMemConfig,CUsharedconfig *)
	ELSE_IF(cuCtxSetSharedMemConfig,CUsharedconfig)
	ELSE_IF(cuModuleLoad,CUmodule *, const char *)
	ELSE_IF(cuModuleLoadData,CUmodule *, const void *)
	ELSE_IF(cuModuleLoadDataEx,CUmodule *, const void *, unsigned int, CUjit_option *, void * *)
	ELSE_IF(cuModuleLoadFatBinary,CUmodule *, const void *)
	ELSE_IF(cuModuleGetFunctionCount,unsigned int *, CUmodule)
	ELSE_IF(cuModuleEnumerateFunctions,CUfunction *, unsigned int, CUmodule)
	ELSE_IF(cuModuleGetGlobal_v2,CUdeviceptr *, size_t *, CUmodule, const char *)
	ELSE_IF(cuLinkCreate_v2,unsigned int, CUjit_option *, void * *, CUlinkState *)
	ELSE_IF(cuLinkAddData_v2,CUlinkState, CUjitInputType, void *, size_t, const char *, unsigned int, CUjit_option *, void * *)
	ELSE_IF(cuLinkAddFile_v2,CUlinkState, CUjitInputType, const char *, unsigned int, CUjit_option *, void * *)
	ELSE_IF(cuLinkComplete,CUlinkState, void * *, size_t *)
	ELSE_IF(cuLinkDestroy,CUlinkState)
	ELSE_IF(cuModuleGetTexRef,CUtexref *, CUmodule, const char *)
	ELSE_IF(cuModuleGetSurfRef,CUsurfref *, CUmodule, const char *)
	ELSE_IF(cuLibraryLoadFromFile,CUlibrary *, const char *, CUjit_option *, void * *, unsigned int, CUlibraryOption *, void * *, unsigned int)
	ELSE_IF(cuLibraryUnload,CUlibrary)
	ELSE_IF(cuLibraryGetKernel,CUkernel *, CUlibrary, const char *)
	ELSE_IF(cuLibraryGetKernelCount,unsigned int *, CUlibrary)
	ELSE_IF(cuLibraryEnumerateKernels,CUkernel *, unsigned int, CUlibrary)
	ELSE_IF(cuKernelGetFunction,CUfunction *, CUkernel)
	ELSE_IF(cuLibraryGetGlobal,CUdeviceptr *, size_t *, CUlibrary, const char *)
	ELSE_IF(cuLibraryGetManaged,CUdeviceptr *, size_t *, CUlibrary, const char *)
	ELSE_IF(cuLibraryGetUnifiedFunction,void * *, CUlibrary, const char *)
	ELSE_IF(cuKernelGetAttribute,int *, CUfunction_attribute, CUkernel, CUdevice)
	ELSE_IF(cuKernelSetAttribute,CUfunction_attribute, int, CUkernel, CUdevice)
	ELSE_IF(cuKernelSetCacheConfig,CUkernel, CUfunc_cache, CUdevice)
	ELSE_IF(cuKernelGetName,const char * *, CUkernel)
	ELSE_IF(cuKernelGetParamInfo,CUkernel, size_t, size_t *, size_t *)
	ELSE_IF(cuMemGetInfo_v2,size_t *, size_t *)
	// ELSE_IF(cuMemAlloc_v2,CUdeviceptr *, size_t)
	ELSE_IF(cuMemAllocPitch_v2,CUdeviceptr *, size_t *, size_t, size_t, unsigned int)
	// ELSE_IF(cuMemFree_v2,CUdeviceptr)
	ELSE_IF(cuMemGetAddressRange_v2,CUdeviceptr *, size_t *, CUdeviceptr)
	ELSE_IF(cuMemAllocHost_v2,void * *, size_t)
	ELSE_IF(cuMemFreeHost,void *)
	ELSE_IF(cuMemHostAlloc,void * *, size_t, unsigned int)
	ELSE_IF(cuMemHostGetDevicePointer_v2,CUdeviceptr *, void *, unsigned int)
	ELSE_IF(cuMemHostGetFlags,unsigned int *, void *)
	ELSE_IF(cuMemAllocManaged,CUdeviceptr *, size_t, unsigned int)
	ELSE_IF(cuDeviceRegisterAsyncNotification,CUdevice, CUasyncCallback, void *, CUasyncCallbackHandle *)
	ELSE_IF(cuDeviceUnregisterAsyncNotification,CUdevice, CUasyncCallbackHandle)
	ELSE_IF(cuDeviceGetByPCIBusId,CUdevice *, const char *)
	ELSE_IF(cuDeviceGetPCIBusId,char *, int, CUdevice)
	ELSE_IF(cuIpcGetEventHandle,CUipcEventHandle *, CUevent)
	ELSE_IF(cuIpcOpenEventHandle,CUevent *, CUipcEventHandle)
	ELSE_IF(cuIpcGetMemHandle,CUipcMemHandle *, CUdeviceptr)
	ELSE_IF(cuIpcOpenMemHandle_v2,CUdeviceptr *, CUipcMemHandle, unsigned int)
	ELSE_IF(cuIpcCloseMemHandle,CUdeviceptr)
	ELSE_IF(cuMemHostRegister_v2,void *, size_t, unsigned int)
	ELSE_IF(cuMemHostUnregister,void *)
	ELSE_IF(cuMemcpy,CUdeviceptr, CUdeviceptr, size_t)
	ELSE_IF(cuMemcpyPeer,CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t)
	// ELSE_IF(cuMemcpyHtoD_v2,CUdeviceptr, const void *, size_t)
	ELSE_IF(cuMemcpyDtoH_v2,void *, CUdeviceptr, size_t)
	ELSE_IF(cuMemcpyDtoD_v2,CUdeviceptr, CUdeviceptr, size_t)
	ELSE_IF(cuMemcpyDtoA_v2,CUarray, size_t, CUdeviceptr, size_t)
	ELSE_IF(cuMemcpyAtoD_v2,CUdeviceptr, CUarray, size_t, size_t)
	ELSE_IF(cuMemcpyHtoA_v2,CUarray, size_t, const void *, size_t)
	ELSE_IF(cuMemcpyAtoH_v2,void *, CUarray, size_t, size_t)
	ELSE_IF(cuMemcpyAtoA_v2,CUarray, size_t, CUarray, size_t, size_t)
	ELSE_IF(cuMemcpy2D_v2,const CUDA_MEMCPY2D *)
	ELSE_IF(cuMemcpy2DUnaligned_v2,const CUDA_MEMCPY2D *)
	ELSE_IF(cuMemcpy3D_v2,const CUDA_MEMCPY3D *)
	ELSE_IF(cuMemcpy3DPeer,const CUDA_MEMCPY3D_PEER *)
	ELSE_IF(cuMemcpyAsync,CUdeviceptr, CUdeviceptr, size_t, CUstream)
	ELSE_IF(cuMemcpyPeerAsync,CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t, CUstream)
	ELSE_IF(cuMemcpyHtoDAsync_v2,CUdeviceptr, const void *, size_t, CUstream)
	ELSE_IF(cuMemcpyDtoHAsync_v2,void *, CUdeviceptr, size_t, CUstream)
	ELSE_IF(cuMemcpyDtoDAsync_v2,CUdeviceptr, CUdeviceptr, size_t, CUstream)
	ELSE_IF(cuMemcpyHtoAAsync_v2,CUarray, size_t, const void *, size_t, CUstream)
	ELSE_IF(cuMemcpyAtoHAsync_v2,void *, CUarray, size_t, size_t, CUstream)
	ELSE_IF(cuMemcpy2DAsync_v2,const CUDA_MEMCPY2D *, CUstream)
	ELSE_IF(cuMemcpy3DAsync_v2,const CUDA_MEMCPY3D *, CUstream)
	ELSE_IF(cuMemcpy3DPeerAsync,const CUDA_MEMCPY3D_PEER *, CUstream)
	ELSE_IF(cuMemsetD8_v2,CUdeviceptr, unsigned char, size_t)
	ELSE_IF(cuMemsetD16_v2,CUdeviceptr, unsigned short, size_t)
	ELSE_IF(cuMemsetD32_v2,CUdeviceptr, unsigned int, size_t)
	ELSE_IF(cuMemsetD2D8_v2,CUdeviceptr, size_t, unsigned char, size_t, size_t)
	ELSE_IF(cuMemsetD2D16_v2,CUdeviceptr, size_t, unsigned short, size_t, size_t)
	ELSE_IF(cuMemsetD2D32_v2,CUdeviceptr, size_t, unsigned int, size_t, size_t)
	ELSE_IF(cuMemsetD8Async,CUdeviceptr, unsigned char, size_t, CUstream)
	ELSE_IF(cuMemsetD16Async,CUdeviceptr, unsigned short, size_t, CUstream)
	ELSE_IF(cuMemsetD32Async,CUdeviceptr, unsigned int, size_t, CUstream)
	ELSE_IF(cuMemsetD2D8Async,CUdeviceptr, size_t, unsigned char, size_t, size_t, CUstream)
	ELSE_IF(cuMemsetD2D16Async,CUdeviceptr, size_t, unsigned short, size_t, size_t, CUstream)
	ELSE_IF(cuMemsetD2D32Async,CUdeviceptr, size_t, unsigned int, size_t, size_t, CUstream)
	ELSE_IF(cuArrayCreate_v2,CUarray *, const CUDA_ARRAY_DESCRIPTOR *)
	ELSE_IF(cuArrayGetDescriptor_v2,CUDA_ARRAY_DESCRIPTOR *, CUarray)
	ELSE_IF(cuArrayGetSparseProperties,CUDA_ARRAY_SPARSE_PROPERTIES *, CUarray)
	ELSE_IF(cuMipmappedArrayGetSparseProperties,CUDA_ARRAY_SPARSE_PROPERTIES *, CUmipmappedArray)
	ELSE_IF(cuArrayGetMemoryRequirements,CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUarray, CUdevice)
	ELSE_IF(cuMipmappedArrayGetMemoryRequirements,CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUmipmappedArray, CUdevice)
	ELSE_IF(cuArrayGetPlane,CUarray *, CUarray, unsigned int)
	ELSE_IF(cuArrayDestroy,CUarray)
	ELSE_IF(cuArray3DCreate_v2,CUarray *, const CUDA_ARRAY3D_DESCRIPTOR *)
	ELSE_IF(cuArray3DGetDescriptor_v2,CUDA_ARRAY3D_DESCRIPTOR *, CUarray)
	ELSE_IF(cuMipmappedArrayCreate,CUmipmappedArray *, const CUDA_ARRAY3D_DESCRIPTOR *, unsigned int)
	ELSE_IF(cuMipmappedArrayGetLevel,CUarray *, CUmipmappedArray, unsigned int)
	ELSE_IF(cuMipmappedArrayDestroy,CUmipmappedArray)
	ELSE_IF(cuMemGetHandleForAddressRange,void *, CUdeviceptr, size_t, CUmemRangeHandleType, unsigned long long)
	ELSE_IF(cuMemAddressReserve,CUdeviceptr *, size_t, size_t, CUdeviceptr, unsigned long long)
	ELSE_IF(cuMemAddressFree,CUdeviceptr, size_t)
	ELSE_IF(cuMemCreate,CUmemGenericAllocationHandle *, size_t, const CUmemAllocationProp *, unsigned long long)
	ELSE_IF(cuMemRelease,CUmemGenericAllocationHandle)
	ELSE_IF(cuMemMap,CUdeviceptr, size_t, size_t, CUmemGenericAllocationHandle, unsigned long long)
	ELSE_IF(cuMemMapArrayAsync,CUarrayMapInfo *, unsigned int, CUstream)
	ELSE_IF(cuMemUnmap,CUdeviceptr, size_t)
	ELSE_IF(cuMemSetAccess,CUdeviceptr, size_t, const CUmemAccessDesc *, size_t)
	ELSE_IF(cuMemGetAccess,unsigned long long *, const CUmemLocation *, CUdeviceptr)
	ELSE_IF(cuMemExportToShareableHandle,void *, CUmemGenericAllocationHandle, CUmemAllocationHandleType, unsigned long long)
	ELSE_IF(cuMemImportFromShareableHandle,CUmemGenericAllocationHandle *, void *, CUmemAllocationHandleType)
	ELSE_IF(cuMemGetAllocationGranularity,size_t *, const CUmemAllocationProp *, CUmemAllocationGranularity_flags)
	ELSE_IF(cuMemGetAllocationPropertiesFromHandle,CUmemAllocationProp *, CUmemGenericAllocationHandle)
	ELSE_IF(cuMemRetainAllocationHandle,CUmemGenericAllocationHandle *, void *)
	ELSE_IF(cuMemFreeAsync,CUdeviceptr, CUstream)
	ELSE_IF(cuMemAllocAsync,CUdeviceptr *, size_t, CUstream)
	ELSE_IF(cuMemPoolTrimTo,CUmemoryPool, size_t)
	ELSE_IF(cuMemPoolSetAttribute,CUmemoryPool, CUmemPool_attribute, void *)
	ELSE_IF(cuMemPoolGetAttribute,CUmemoryPool, CUmemPool_attribute, void *)
	ELSE_IF(cuMemPoolSetAccess,CUmemoryPool, const CUmemAccessDesc *, size_t)
	ELSE_IF(cuMemPoolGetAccess,CUmemAccess_flags *, CUmemoryPool, CUmemLocation *)
	ELSE_IF(cuMemPoolCreate,CUmemoryPool *, const CUmemPoolProps *)
	ELSE_IF(cuMemPoolDestroy,CUmemoryPool)
	ELSE_IF(cuMemAllocFromPoolAsync,CUdeviceptr *, size_t, CUmemoryPool, CUstream)
	ELSE_IF(cuMemPoolExportToShareableHandle,void *, CUmemoryPool, CUmemAllocationHandleType, unsigned long long)
	ELSE_IF(cuMemPoolImportFromShareableHandle,CUmemoryPool *, void *, CUmemAllocationHandleType, unsigned long long)
	ELSE_IF(cuMemPoolExportPointer,CUmemPoolPtrExportData *, CUdeviceptr)
	ELSE_IF(cuMemPoolImportPointer,CUdeviceptr *, CUmemoryPool, CUmemPoolPtrExportData *)
	ELSE_IF(cuMulticastCreate,CUmemGenericAllocationHandle *, const CUmulticastObjectProp *)
	ELSE_IF(cuMulticastAddDevice,CUmemGenericAllocationHandle, CUdevice)
	ELSE_IF(cuMulticastBindMem,CUmemGenericAllocationHandle, size_t, CUmemGenericAllocationHandle, size_t, size_t, unsigned long long)
	ELSE_IF(cuMulticastBindAddr,CUmemGenericAllocationHandle, size_t, CUdeviceptr, size_t, unsigned long long)
	ELSE_IF(cuMulticastUnbind,CUmemGenericAllocationHandle, CUdevice, size_t, size_t)
	ELSE_IF(cuMulticastGetGranularity,size_t *, const CUmulticastObjectProp *, CUmulticastGranularity_flags)
	ELSE_IF(cuPointerGetAttribute,void *, CUpointer_attribute, CUdeviceptr)
	ELSE_IF(cuMemPrefetchAsync,CUdeviceptr, size_t, CUdevice, CUstream)
	ELSE_IF(cuMemPrefetchAsync_v2,CUdeviceptr, size_t, CUmemLocation, unsigned int, CUstream)
	ELSE_IF(cuMemAdvise,CUdeviceptr, size_t, CUmem_advise, CUdevice)
	ELSE_IF(cuMemAdvise_v2,CUdeviceptr, size_t, CUmem_advise, CUmemLocation)
	ELSE_IF(cuMemRangeGetAttribute,void *, size_t, CUmem_range_attribute, CUdeviceptr, size_t)
	ELSE_IF(cuMemRangeGetAttributes,void * *, size_t *, CUmem_range_attribute *, size_t, CUdeviceptr, size_t)
	ELSE_IF(cuPointerSetAttribute,const void *, CUpointer_attribute, CUdeviceptr)
	ELSE_IF(cuPointerGetAttributes,unsigned int, CUpointer_attribute *, void * *, CUdeviceptr)
	ELSE_IF(cuStreamCreate,CUstream *, unsigned int)
	ELSE_IF(cuStreamCreateWithPriority,CUstream *, unsigned int, int)
	ELSE_IF(cuStreamGetPriority,CUstream, int *)
	ELSE_IF(cuStreamGetFlags,CUstream, unsigned int *)
	ELSE_IF(cuStreamGetId,CUstream, unsigned long long *)
	ELSE_IF(cuStreamGetCtx,CUstream, CUcontext *)
	ELSE_IF(cuStreamWaitEvent,CUstream, CUevent, unsigned int)
	ELSE_IF(cuStreamAddCallback,CUstream, CUstreamCallback, void *, unsigned int)
	ELSE_IF(cuStreamBeginCapture_v2,CUstream, CUstreamCaptureMode)
	ELSE_IF(cuStreamBeginCaptureToGraph,CUstream, CUgraph, const CUgraphNode *, const CUgraphEdgeData *, size_t, CUstreamCaptureMode)
	ELSE_IF(cuThreadExchangeStreamCaptureMode,CUstreamCaptureMode *)
	ELSE_IF(cuStreamEndCapture,CUstream, CUgraph *)
	ELSE_IF(cuStreamIsCapturing,CUstream, CUstreamCaptureStatus *)
	ELSE_IF(cuStreamGetCaptureInfo_v2,CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode * *, size_t *)
	ELSE_IF(cuStreamGetCaptureInfo_v3,CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode * *, const CUgraphEdgeData * *, size_t *)
	ELSE_IF(cuStreamUpdateCaptureDependencies,CUstream, CUgraphNode *, size_t, unsigned int)
	ELSE_IF(cuStreamUpdateCaptureDependencies_v2,CUstream, CUgraphNode *, const CUgraphEdgeData *, size_t, unsigned int)
	ELSE_IF(cuStreamAttachMemAsync,CUstream, CUdeviceptr, size_t, unsigned int)
	ELSE_IF(cuStreamQuery,CUstream)
	ELSE_IF(cuStreamSynchronize,CUstream)
	ELSE_IF(cuStreamDestroy_v2,CUstream)
	ELSE_IF(cuStreamCopyAttributes,CUstream, CUstream)
	ELSE_IF(cuStreamGetAttribute,CUstream, CUstreamAttrID, CUstreamAttrValue *)
	ELSE_IF(cuStreamSetAttribute,CUstream, CUstreamAttrID, const CUstreamAttrValue *)
	ELSE_IF(cuEventCreate,CUevent *, unsigned int)
	ELSE_IF(cuEventRecord,CUevent, CUstream)
	ELSE_IF(cuEventRecordWithFlags,CUevent, CUstream, unsigned int)
	ELSE_IF(cuEventQuery,CUevent)
	ELSE_IF(cuEventSynchronize,CUevent)
	ELSE_IF(cuEventDestroy_v2,CUevent)
	ELSE_IF(cuEventElapsedTime,float *, CUevent, CUevent)
	ELSE_IF(cuImportExternalMemory,CUexternalMemory *, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *)
	ELSE_IF(cuExternalMemoryGetMappedBuffer,CUdeviceptr *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *)
	ELSE_IF(cuExternalMemoryGetMappedMipmappedArray,CUmipmappedArray *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *)
	ELSE_IF(cuDestroyExternalMemory,CUexternalMemory)
	ELSE_IF(cuImportExternalSemaphore,CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *)
	ELSE_IF(cuSignalExternalSemaphoresAsync,const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *, unsigned int, CUstream)
	ELSE_IF(cuWaitExternalSemaphoresAsync,const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *, unsigned int, CUstream)
	ELSE_IF(cuDestroyExternalSemaphore,CUexternalSemaphore)
	ELSE_IF(cuStreamWaitValue32_v2,CUstream, CUdeviceptr, cuuint32_t, unsigned int)
	ELSE_IF(cuStreamWaitValue64_v2,CUstream, CUdeviceptr, cuuint64_t, unsigned int)
	ELSE_IF(cuStreamWriteValue32_v2,CUstream, CUdeviceptr, cuuint32_t, unsigned int)
	ELSE_IF(cuStreamWriteValue64_v2,CUstream, CUdeviceptr, cuuint64_t, unsigned int)
	ELSE_IF(cuStreamBatchMemOp_v2,CUstream, unsigned int, CUstreamBatchMemOpParams *, unsigned int)
	ELSE_IF(cuFuncGetAttribute,int *, CUfunction_attribute, CUfunction)
	ELSE_IF(cuFuncSetAttribute,CUfunction, CUfunction_attribute, int)
	ELSE_IF(cuFuncSetCacheConfig,CUfunction, CUfunc_cache)
	ELSE_IF(cuFuncGetModule,CUmodule *, CUfunction)
	ELSE_IF(cuFuncGetName,const char * *, CUfunction)
	ELSE_IF(cuFuncGetParamInfo,CUfunction, size_t, size_t *, size_t *)
	ELSE_IF(cuFuncIsLoaded,CUfunctionLoadingState *, CUfunction)
	ELSE_IF(cuFuncLoad,CUfunction)

	ELSE_IF(cuLaunchKernelEx,const CUlaunchConfig *, CUfunction, void * *, void * *)
	ELSE_IF(cuLaunchCooperativeKernel,CUfunction, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CUstream, void * *)
	ELSE_IF(cuLaunchCooperativeKernelMultiDevice,CUDA_LAUNCH_PARAMS *, unsigned int, unsigned int)
	ELSE_IF(cuLaunchHostFunc,CUstream, CUhostFn, void *)
	ELSE_IF(cuFuncSetBlockShape,CUfunction, int, int, int)
	ELSE_IF(cuFuncSetSharedSize,CUfunction, unsigned int)
	ELSE_IF(cuParamSetSize,CUfunction, unsigned int)
	ELSE_IF(cuParamSeti,CUfunction, int, unsigned int)
	ELSE_IF(cuParamSetf,CUfunction, int, float)
	ELSE_IF(cuParamSetv,CUfunction, int, void *, unsigned int)
	ELSE_IF(cuLaunch,CUfunction)
	ELSE_IF(cuLaunchGrid,CUfunction, int, int)
	ELSE_IF(cuLaunchGridAsync,CUfunction, int, int, CUstream)
	ELSE_IF(cuParamSetTexRef,CUfunction, int, CUtexref)
	ELSE_IF(cuFuncSetSharedMemConfig,CUfunction, CUsharedconfig)
	ELSE_IF(cuGraphCreate,CUgraph *, unsigned int)
	ELSE_IF(cuGraphAddKernelNode_v2,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_KERNEL_NODE_PARAMS *)
	ELSE_IF(cuGraphKernelNodeGetParams_v2,CUgraphNode, CUDA_KERNEL_NODE_PARAMS *)
	ELSE_IF(cuGraphKernelNodeSetParams_v2,CUgraphNode, const CUDA_KERNEL_NODE_PARAMS *)
	ELSE_IF(cuGraphAddMemcpyNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_MEMCPY3D *, CUcontext)
	ELSE_IF(cuGraphMemcpyNodeGetParams,CUgraphNode, CUDA_MEMCPY3D *)
	ELSE_IF(cuGraphMemcpyNodeSetParams,CUgraphNode, const CUDA_MEMCPY3D *)
	ELSE_IF(cuGraphAddMemsetNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_MEMSET_NODE_PARAMS *, CUcontext)
	ELSE_IF(cuGraphMemsetNodeGetParams,CUgraphNode, CUDA_MEMSET_NODE_PARAMS *)
	ELSE_IF(cuGraphMemsetNodeSetParams,CUgraphNode, const CUDA_MEMSET_NODE_PARAMS *)
	ELSE_IF(cuGraphAddHostNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_HOST_NODE_PARAMS *)
	ELSE_IF(cuGraphHostNodeGetParams,CUgraphNode, CUDA_HOST_NODE_PARAMS *)
	ELSE_IF(cuGraphHostNodeSetParams,CUgraphNode, const CUDA_HOST_NODE_PARAMS *)
	ELSE_IF(cuGraphAddChildGraphNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUgraph)
	ELSE_IF(cuGraphChildGraphNodeGetGraph,CUgraphNode, CUgraph *)
	ELSE_IF(cuGraphAddEmptyNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t)
	ELSE_IF(cuGraphAddEventRecordNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent)
	ELSE_IF(cuGraphEventRecordNodeGetEvent,CUgraphNode, CUevent *)
	ELSE_IF(cuGraphEventRecordNodeSetEvent,CUgraphNode, CUevent)
	ELSE_IF(cuGraphAddEventWaitNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent)
	ELSE_IF(cuGraphEventWaitNodeGetEvent,CUgraphNode, CUevent *)
	ELSE_IF(cuGraphEventWaitNodeSetEvent,CUgraphNode, CUevent)
	ELSE_IF(cuGraphAddExternalSemaphoresSignalNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)
	ELSE_IF(cuGraphExternalSemaphoresSignalNodeGetParams,CUgraphNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)
	ELSE_IF(cuGraphExternalSemaphoresSignalNodeSetParams,CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)
	ELSE_IF(cuGraphAddExternalSemaphoresWaitNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *)
	ELSE_IF(cuGraphExternalSemaphoresWaitNodeGetParams,CUgraphNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS *)
	ELSE_IF(cuGraphExternalSemaphoresWaitNodeSetParams,CUgraphNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *)
	ELSE_IF(cuGraphAddBatchMemOpNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_BATCH_MEM_OP_NODE_PARAMS *)
	ELSE_IF(cuGraphBatchMemOpNodeGetParams,CUgraphNode, CUDA_BATCH_MEM_OP_NODE_PARAMS *)
	ELSE_IF(cuGraphBatchMemOpNodeSetParams,CUgraphNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS *)
	ELSE_IF(cuGraphExecBatchMemOpNodeSetParams,CUgraphExec, CUgraphNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS *)
	ELSE_IF(cuGraphAddMemAllocNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUDA_MEM_ALLOC_NODE_PARAMS *)
	ELSE_IF(cuGraphMemAllocNodeGetParams,CUgraphNode, CUDA_MEM_ALLOC_NODE_PARAMS *)
	ELSE_IF(cuGraphAddMemFreeNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUdeviceptr)
	ELSE_IF(cuGraphMemFreeNodeGetParams,CUgraphNode, CUdeviceptr *)
	ELSE_IF(cuDeviceGraphMemTrim,CUdevice)
	ELSE_IF(cuDeviceGetGraphMemAttribute,CUdevice, CUgraphMem_attribute, void *)
	ELSE_IF(cuDeviceSetGraphMemAttribute,CUdevice, CUgraphMem_attribute, void *)
	ELSE_IF(cuGraphClone,CUgraph *, CUgraph)
	ELSE_IF(cuGraphNodeFindInClone,CUgraphNode *, CUgraphNode, CUgraph)
	ELSE_IF(cuGraphNodeGetType,CUgraphNode, CUgraphNodeType *)
	ELSE_IF(cuGraphGetNodes,CUgraph, CUgraphNode *, size_t *)
	ELSE_IF(cuGraphGetRootNodes,CUgraph, CUgraphNode *, size_t *)
	ELSE_IF(cuGraphGetEdges,CUgraph, CUgraphNode *, CUgraphNode *, size_t *)
	ELSE_IF(cuGraphGetEdges_v2,CUgraph, CUgraphNode *, CUgraphNode *, CUgraphEdgeData *, size_t *)
	ELSE_IF(cuGraphNodeGetDependencies,CUgraphNode, CUgraphNode *, size_t *)
	ELSE_IF(cuGraphNodeGetDependencies_v2,CUgraphNode, CUgraphNode *, CUgraphEdgeData *, size_t *)
	ELSE_IF(cuGraphNodeGetDependentNodes,CUgraphNode, CUgraphNode *, size_t *)
	ELSE_IF(cuGraphNodeGetDependentNodes_v2,CUgraphNode, CUgraphNode *, CUgraphEdgeData *, size_t *)
	ELSE_IF(cuGraphAddDependencies,CUgraph, const CUgraphNode *, const CUgraphNode *, size_t)
	ELSE_IF(cuGraphAddDependencies_v2,CUgraph, const CUgraphNode *, const CUgraphNode *, const CUgraphEdgeData *, size_t)
	ELSE_IF(cuGraphRemoveDependencies,CUgraph, const CUgraphNode *, const CUgraphNode *, size_t)
	ELSE_IF(cuGraphRemoveDependencies_v2,CUgraph, const CUgraphNode *, const CUgraphNode *, const CUgraphEdgeData *, size_t)
	ELSE_IF(cuGraphDestroyNode,CUgraphNode)
	ELSE_IF(cuGraphInstantiateWithFlags,CUgraphExec *, CUgraph, unsigned long long)
	ELSE_IF(cuGraphInstantiateWithParams,CUgraphExec *, CUgraph, CUDA_GRAPH_INSTANTIATE_PARAMS *)
	ELSE_IF(cuGraphExecGetFlags,CUgraphExec, cuuint64_t *)
	ELSE_IF(cuGraphExecKernelNodeSetParams_v2,CUgraphExec, CUgraphNode, const CUDA_KERNEL_NODE_PARAMS *)
	ELSE_IF(cuGraphExecMemcpyNodeSetParams,CUgraphExec, CUgraphNode, const CUDA_MEMCPY3D *, CUcontext)
	ELSE_IF(cuGraphExecMemsetNodeSetParams,CUgraphExec, CUgraphNode, const CUDA_MEMSET_NODE_PARAMS *, CUcontext)
	ELSE_IF(cuGraphExecHostNodeSetParams,CUgraphExec, CUgraphNode, const CUDA_HOST_NODE_PARAMS *)
	ELSE_IF(cuGraphExecChildGraphNodeSetParams,CUgraphExec, CUgraphNode, CUgraph)
	ELSE_IF(cuGraphExecEventRecordNodeSetEvent,CUgraphExec, CUgraphNode, CUevent)
	ELSE_IF(cuGraphExecEventWaitNodeSetEvent,CUgraphExec, CUgraphNode, CUevent)
	ELSE_IF(cuGraphExecExternalSemaphoresSignalNodeSetParams,CUgraphExec, CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)
	ELSE_IF(cuGraphExecExternalSemaphoresWaitNodeSetParams,CUgraphExec, CUgraphNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *)
	ELSE_IF(cuGraphNodeSetEnabled,CUgraphExec, CUgraphNode, unsigned int)
	ELSE_IF(cuGraphNodeGetEnabled,CUgraphExec, CUgraphNode, unsigned int *)
	ELSE_IF(cuGraphUpload,CUgraphExec, CUstream)
	ELSE_IF(cuGraphLaunch,CUgraphExec, CUstream)
	ELSE_IF(cuGraphExecDestroy,CUgraphExec)
	ELSE_IF(cuGraphDestroy,CUgraph)
	ELSE_IF(cuGraphExecUpdate_v2,CUgraphExec, CUgraph, CUgraphExecUpdateResultInfo *)
	ELSE_IF(cuGraphKernelNodeCopyAttributes,CUgraphNode, CUgraphNode)
	ELSE_IF(cuGraphKernelNodeGetAttribute,CUgraphNode, CUkernelNodeAttrID, CUkernelNodeAttrValue *)
	ELSE_IF(cuGraphKernelNodeSetAttribute,CUgraphNode, CUkernelNodeAttrID, const CUkernelNodeAttrValue *)
	ELSE_IF(cuGraphDebugDotPrint,CUgraph, const char *, unsigned int)
	ELSE_IF(cuUserObjectCreate,CUuserObject *, void *, CUhostFn, unsigned int, unsigned int)
	ELSE_IF(cuUserObjectRetain,CUuserObject, unsigned int)
	ELSE_IF(cuUserObjectRelease,CUuserObject, unsigned int)
	ELSE_IF(cuGraphRetainUserObject,CUgraph, CUuserObject, unsigned int, unsigned int)
	ELSE_IF(cuGraphReleaseUserObject,CUgraph, CUuserObject, unsigned int)
	ELSE_IF(cuGraphAddNode,CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUgraphNodeParams *)
	ELSE_IF(cuGraphAddNode_v2,CUgraphNode *, CUgraph, const CUgraphNode *, const CUgraphEdgeData *, size_t, CUgraphNodeParams *)
	ELSE_IF(cuGraphNodeSetParams,CUgraphNode, CUgraphNodeParams *)
	ELSE_IF(cuGraphExecNodeSetParams,CUgraphExec, CUgraphNode, CUgraphNodeParams *)
	ELSE_IF(cuGraphConditionalHandleCreate,CUgraphConditionalHandle *, CUgraph, CUcontext, unsigned int, unsigned int)
	ELSE_IF(cuOccupancyMaxActiveBlocksPerMultiprocessor,int *, CUfunction, int, size_t)
	ELSE_IF(cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags,int *, CUfunction, int, size_t, unsigned int)
	ELSE_IF(cuOccupancyMaxPotentialBlockSize,int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int)
	ELSE_IF(cuOccupancyMaxPotentialBlockSizeWithFlags,int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int, unsigned int)
	ELSE_IF(cuOccupancyAvailableDynamicSMemPerBlock,size_t *, CUfunction, int, int)
	ELSE_IF(cuOccupancyMaxPotentialClusterSize,int *, CUfunction, const CUlaunchConfig *)
	ELSE_IF(cuOccupancyMaxActiveClusters,int *, CUfunction, const CUlaunchConfig *)
	ELSE_IF(cuTexRefSetArray,CUtexref, CUarray, unsigned int)
	ELSE_IF(cuTexRefSetMipmappedArray,CUtexref, CUmipmappedArray, unsigned int)
	ELSE_IF(cuTexRefSetAddress_v2,size_t *, CUtexref, CUdeviceptr, size_t)
	ELSE_IF(cuTexRefSetAddress2D_v3,CUtexref, const CUDA_ARRAY_DESCRIPTOR *, CUdeviceptr, size_t)
	ELSE_IF(cuTexRefSetFormat,CUtexref, CUarray_format, int)
	ELSE_IF(cuTexRefSetAddressMode,CUtexref, int, CUaddress_mode)
	ELSE_IF(cuTexRefSetFilterMode,CUtexref, CUfilter_mode)
	ELSE_IF(cuTexRefSetMipmapFilterMode,CUtexref, CUfilter_mode)
	ELSE_IF(cuTexRefSetMipmapLevelBias,CUtexref, float)
	ELSE_IF(cuTexRefSetMipmapLevelClamp,CUtexref, float, float)
	ELSE_IF(cuTexRefSetMaxAnisotropy,CUtexref, unsigned int)
	ELSE_IF(cuTexRefSetBorderColor,CUtexref, float *)
	ELSE_IF(cuTexRefSetFlags,CUtexref, unsigned int)
	ELSE_IF(cuTexRefGetAddress_v2,CUdeviceptr *, CUtexref)
	ELSE_IF(cuTexRefGetArray,CUarray *, CUtexref)
	ELSE_IF(cuTexRefGetMipmappedArray,CUmipmappedArray *, CUtexref)
	ELSE_IF(cuTexRefGetAddressMode,CUaddress_mode *, CUtexref, int)
	ELSE_IF(cuTexRefGetFilterMode,CUfilter_mode *, CUtexref)
	ELSE_IF(cuTexRefGetFormat,CUarray_format *, int *, CUtexref)
	ELSE_IF(cuTexRefGetMipmapFilterMode,CUfilter_mode *, CUtexref)
	ELSE_IF(cuTexRefGetMipmapLevelBias,float *, CUtexref)
	ELSE_IF(cuTexRefGetMipmapLevelClamp,float *, float *, CUtexref)
	ELSE_IF(cuTexRefGetMaxAnisotropy,int *, CUtexref)
	ELSE_IF(cuTexRefGetBorderColor,float *, CUtexref)
	ELSE_IF(cuTexRefGetFlags,unsigned int *, CUtexref)
	ELSE_IF(cuTexRefCreate,CUtexref *)
	ELSE_IF(cuTexRefDestroy,CUtexref)
	ELSE_IF(cuSurfRefSetArray,CUsurfref, CUarray, unsigned int)
	ELSE_IF(cuSurfRefGetArray,CUarray *, CUsurfref)
	ELSE_IF(cuTexObjectCreate,CUtexObject *, const CUDA_RESOURCE_DESC *, const CUDA_TEXTURE_DESC *, const CUDA_RESOURCE_VIEW_DESC *)
	ELSE_IF(cuTexObjectDestroy,CUtexObject)
	ELSE_IF(cuTexObjectGetResourceDesc,CUDA_RESOURCE_DESC *, CUtexObject)
	ELSE_IF(cuTexObjectGetTextureDesc,CUDA_TEXTURE_DESC *, CUtexObject)
	ELSE_IF(cuTexObjectGetResourceViewDesc,CUDA_RESOURCE_VIEW_DESC *, CUtexObject)
	ELSE_IF(cuSurfObjectCreate,CUsurfObject *, const CUDA_RESOURCE_DESC *)
	ELSE_IF(cuSurfObjectDestroy,CUsurfObject)
	ELSE_IF(cuSurfObjectGetResourceDesc,CUDA_RESOURCE_DESC *, CUsurfObject)
	ELSE_IF(cuTensorMapEncodeTiled,CUtensorMap *, CUtensorMapDataType, cuuint32_t, void *, const cuuint64_t *, const cuuint64_t *, const cuuint32_t *, const cuuint32_t *, CUtensorMapInterleave, CUtensorMapSwizzle, CUtensorMapL2promotion, CUtensorMapFloatOOBfill)
	ELSE_IF(cuTensorMapEncodeIm2col,CUtensorMap *, CUtensorMapDataType, cuuint32_t, void *, const cuuint64_t *, const cuuint64_t *, const int *, const int *, cuuint32_t, cuuint32_t, const cuuint32_t *, CUtensorMapInterleave, CUtensorMapSwizzle, CUtensorMapL2promotion, CUtensorMapFloatOOBfill)
	ELSE_IF(cuTensorMapReplaceAddress,CUtensorMap *, void *)
	ELSE_IF(cuDeviceCanAccessPeer,int *, CUdevice, CUdevice)
	ELSE_IF(cuCtxEnablePeerAccess,CUcontext, unsigned int)
	ELSE_IF(cuCtxDisablePeerAccess,CUcontext)
	ELSE_IF(cuDeviceGetP2PAttribute,int *, CUdevice_P2PAttribute, CUdevice, CUdevice)
	ELSE_IF(cuGraphicsUnregisterResource,CUgraphicsResource)
	ELSE_IF(cuGraphicsSubResourceGetMappedArray,CUarray *, CUgraphicsResource, unsigned int, unsigned int)
	ELSE_IF(cuGraphicsResourceGetMappedMipmappedArray,CUmipmappedArray *, CUgraphicsResource)
	ELSE_IF(cuGraphicsResourceGetMappedPointer_v2,CUdeviceptr *, size_t *, CUgraphicsResource)
	ELSE_IF(cuGraphicsResourceSetMapFlags_v2,CUgraphicsResource, unsigned int)
	ELSE_IF(cuGraphicsMapResources,unsigned int, CUgraphicsResource *, CUstream)
	ELSE_IF(cuGraphicsUnmapResources,unsigned int, CUgraphicsResource *, CUstream)
	ELSE_IF(cuCoredumpGetAttribute,CUcoredumpSettings, void *, size_t *)
	ELSE_IF(cuCoredumpGetAttributeGlobal,CUcoredumpSettings, void *, size_t *)
	ELSE_IF(cuCoredumpSetAttribute,CUcoredumpSettings, void *, size_t *)
	ELSE_IF(cuCoredumpSetAttributeGlobal,CUcoredumpSettings, void *, size_t *)
	ELSE_IF(cuGetExportTable,const void * *, const CUuuid *)
	ELSE_IF(cuGreenCtxCreate,CUgreenCtx *, CUdevResourceDesc, CUdevice, unsigned int)
	ELSE_IF(cuGreenCtxDestroy,CUgreenCtx)
	ELSE_IF(cuCtxFromGreenCtx,CUcontext *, CUgreenCtx)
	ELSE_IF(cuDeviceGetDevResource,CUdevice, CUdevResource *, CUdevResourceType)
	ELSE_IF(cuCtxGetDevResource,CUcontext, CUdevResource *, CUdevResourceType)
	ELSE_IF(cuGreenCtxGetDevResource,CUgreenCtx, CUdevResource *, CUdevResourceType)
	ELSE_IF(cuDevSmResourceSplitByCount,CUdevResource *, unsigned int *, const CUdevResource *, CUdevResource *, unsigned int, unsigned int)
	ELSE_IF(cuDevResourceGenerateDesc,CUdevResourceDesc *, CUdevResource *, unsigned int)
	ELSE_IF(cuGreenCtxRecordEvent,CUgreenCtx, CUevent)
	ELSE_IF(cuGreenCtxWaitEvent,CUgreenCtx, CUevent)
	ELSE_IF(cuStreamGetGreenCtx,CUstream, CUgreenCtx *)
	else{
		printf("CUDA Driver API NOT HOOK:%s\n",symbol);
	}



    return result;
}
