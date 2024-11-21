#include <cstddef>
#include <cstring>
#include <cuda_subset.h>
#include <cstdio>
#include "cuda_hook.h"
#include <string>
#include <unordered_map>
#include <elf.h>
#include <iostream>
#include "macro_common.h"

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


HOOK_C_API HOOK_DECL_EXPORT  CUresult cuInit_v2000(unsigned int Flags) {
    
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
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuModuleGetLoadingMode_v11070(CUmoduleLoadingMode * mode) {
    CuDriverCallStructure request{
        .op=CuDriverCall::CuModuleGetLoadingMode,
    };
    CuDriverCallReplyStructure reply;
    
    communicate_with_server(NULL, &request, &reply);
    *mode=reply.returnParams.mode;
    return reply.result;
}

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGetCount_v2000(int * count) {
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
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGetName_v2000(char * name, int len, CUdevice dev) {
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
HOOK_C_API HOOK_DECL_EXPORT CUresult cuDeviceGetUuid__v11040 (CUuuid * uuid,CUdevice dev){
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

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDriverGetVersion_v2020(int * driverVersion) {
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

HOOK_C_API HOOK_DECL_EXPORT CUresult cuMemAlloc_v3020(CUdeviceptr * dptr, size_t bytesize) {
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
HOOK_C_API HOOK_DECL_EXPORT CUresult cuMemFree_v3020(CUdeviceptr dptr) {
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

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGet_v2000(CUdevice * device, int ordinal) {
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
HOOK_C_API HOOK_DECL_EXPORT CUresult cuDeviceTotalMem_v3020(size_t * bytes,CUdevice dev){
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


HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDeviceGetAttribute_v2000(int * pi, CUdevice_attribute attrib, CUdevice dev) {
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
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuCtxSetCurrent_v4000(CUcontext ctx) {
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

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuCtxGetCurrent_v4000(CUcontext * pctx) {
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
CUresult cuCtxPushCurrent_v4000 (CUcontext,ctx){
	HOOK_TRACE_PROFILE("cuCtxPushCurrent");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuCtxPushCurrent,
		.params={.cuCtxPushCurrent={.ctx=ctx}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	printf("[cuCtxPushCurrent] push current context:%p\n",ctx);
	return reply.result;
}
CUresult cuCtxPopCurrent_v4000 (CUcontext * pctx){
	HOOK_TRACE_PROFILE("cuCtxPopCurrent");
	CuDriverCallStructure request{
		.op=CuDriverCall::CuCtxPopCurrent,
		.params={.empty{}},
	};
	CuDriverCallReplyStructure reply;
	communicate_with_server(nullptr, &request, &reply);
	*pctx=reply.returnParams.ctx;
	printf("[cuCtxPopCurrent] pop current context:%p\n",*pctx);
	return reply.result;
}


HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDevicePrimaryCtxRetain_v7000(CUcontext * pctx, CUdevice dev) {
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
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuDevicePrimaryCtxRelease_v11000(CUdevice dev) {
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


HOOK_C_API HOOK_DECL_EXPORT CUresult cuMemcpyHtoD_v3020( CUdeviceptr dstDevice,const void * srcHost,size_t ByteCount){
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

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuLibraryGetModule_v12000(CUmodule * pMod, CUlibrary library) {
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
HOOK_C_API HOOK_DECL_EXPORT  CUresult cuModuleGetFunction_v2000(CUfunction * hfunc, CUmodule hmod, const char * name) {
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

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuLaunchKernel_v4000(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void * * kernelParams, void * * extra) {

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

HOOK_C_API HOOK_DECL_EXPORT  CUresult cuLibraryLoadData_v12000(CUlibrary * library, const void * code, CUjit_option * jitOptions, void * * jitOptionsValues, unsigned int numJitOptions, CUlibraryOption * libraryOptions, void * * libraryOptionValues, unsigned int numLibraryOptions) {
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

DEF_FN(CUresult,cuGetErrorString_v6000,cuGetErrorString,6000,0,CUresult,error, const char**,pStr);
DEF_FN(CUresult,cuGetErrorName_v6000,cuGetErrorName,6000,0,CUresult,error, const char**,pStr);
// DEF_FN(CUresult,cuInit_v2000,cuInit,2000,0,unsigned int,Flags);
// DEF_FN(CUresult,cuDriverGetVersion_v2020,cuDriverGetVersion,2020,0,int*,driverVersion);
// DEF_FN(CUresult,cuDeviceGet_v2000,cuDeviceGet,2000,0,CUdevice_v1*,device, int,ordinal);
// DEF_FN(CUresult,cuDeviceGetCount_v2000,cuDeviceGetCount,2000,0,int*,count);
// DEF_FN(CUresult,cuDeviceGetName_v2000,cuDeviceGetName,2000,0,char*,name, int,len, CUdevice_v1,dev);
// DEF_FN(CUresult,cuDeviceGetUuid_v9020,cuDeviceGetUuid,9020,0,CUuuid*,uuid, CUdevice_v1,dev);
// DEF_FN(CUresult,cuDeviceGetUuid_v11040,cuDeviceGetUuid,11040,0,CUuuid*,uuid, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetLuid_v10000,cuDeviceGetLuid,10000,0,char*,luid, unsigned int*,deviceNodeMask, CUdevice_v1,dev);
// DEF_FN(CUresult,cuDeviceTotalMem_v3020,cuDeviceTotalMem,3020,0,size_t*,bytes, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetTexture1DLinearMaxWidth_v11010,cuDeviceGetTexture1DLinearMaxWidth,11010,0,size_t*,maxWidthInElements, CUarray_format,format, unsigned,numChannels, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetAttribute_v2000,cuDeviceGetAttribute,2000,0,int*,pi, CUdevice_attribute,attrib, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetNvSciSyncAttributes_v10020,cuDeviceGetNvSciSyncAttributes,10020,0,void*,nvSciSyncAttrList, CUdevice_v1,dev, int,flags);
DEF_FN(CUresult,cuDeviceSetMemPool_v11020,cuDeviceSetMemPool,11020,0,CUdevice_v1,dev, CUmemoryPool,pool);
DEF_FN(CUresult,cuDeviceGetMemPool_v11020,cuDeviceGetMemPool,11020,0,CUmemoryPool*,pool, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetDefaultMemPool_v11020,cuDeviceGetDefaultMemPool,11020,0,CUmemoryPool*,pool_out, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetProperties_v2000,cuDeviceGetProperties,2000,0,CUdevprop_v1*,prop, CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceComputeCapability_v2000,cuDeviceComputeCapability,2000,0,int*,major, int*,minor, CUdevice_v1,dev);
// DEF_FN(CUresult,cuDevicePrimaryCtxRetain_v7000,cuDevicePrimaryCtxRetain,7000,0,CUcontext*,pctx, CUdevice_v1,dev);
// DEF_FN(CUresult,cuDevicePrimaryCtxRelease_v11000,cuDevicePrimaryCtxRelease,11000,0,CUdevice_v1,dev);
DEF_FN(CUresult,cuDevicePrimaryCtxSetFlags_v11000,cuDevicePrimaryCtxSetFlags,11000,0,CUdevice_v1,dev, unsigned int,flags);
DEF_FN(CUresult,cuDevicePrimaryCtxGetState_v7000,cuDevicePrimaryCtxGetState,7000,0,CUdevice_v1,dev, unsigned int*,flags, int*,active);
DEF_FN(CUresult,cuDevicePrimaryCtxReset_v11000,cuDevicePrimaryCtxReset,11000,0,CUdevice_v1,dev);
DEF_FN(CUresult,cuDeviceGetExecAffinitySupport_v11040,cuDeviceGetExecAffinitySupport,11040,0,int*,pi, CUexecAffinityType,type, CUdevice,dev);
DEF_FN(CUresult,cuCtxCreate_v3020,cuCtxCreate,3020,0,CUcontext*,pctx, unsigned int,flags, CUdevice_v1,dev);
DEF_FN(CUresult,cuCtxCreate_v11040,cuCtxCreate,11040,0,CUcontext*,pctx, CUexecAffinityParam*,paramsArray, int,numParams, unsigned int,flags, CUdevice_v1,dev);
DEF_FN(CUresult,cuCtxGetId_v12000,cuCtxGetId,12000,0,CUcontext,ctx, unsigned long long*,ctxId);
DEF_FN(CUresult,cuCtxDestroy_v4000,cuCtxDestroy,4000,0,CUcontext,ctx);
// DEF_FN(CUresult,cuCtxPushCurrent_v4000,cuCtxPushCurrent,4000,0,CUcontext,ctx);
// DEF_FN(CUresult,cuCtxPopCurrent_v4000,cuCtxPopCurrent,4000,0,CUcontext*,pctx);
// DEF_FN(CUresult,cuCtxSetCurrent_v4000,cuCtxSetCurrent,4000,0,CUcontext,ctx);
// DEF_FN(CUresult,cuCtxGetCurrent_v4000,cuCtxGetCurrent,4000,0,CUcontext*,pctx);
DEF_FN(CUresult,cuCtxGetDevice_v2000,cuCtxGetDevice,2000,0,CUdevice_v1*,device);
DEF_FN(CUresult,cuCtxGetFlags_v7000,cuCtxGetFlags,7000,0,unsigned int*,flags);
DEF_FN(CUresult,cuCtxSetFlags_v12010,cuCtxSetFlags,12010,0,unsigned int,flags);
DEF_FN(CUresult,cuCtxSynchronize_v2000,cuCtxSynchronize,2000,0,void,);
DEF_FN(CUresult,cuCtxSetLimit_v3010,cuCtxSetLimit,3010,0,CUlimit,limit, size_t,value);
DEF_FN(CUresult,cuCtxGetLimit_v3010,cuCtxGetLimit,3010,0,size_t*,pvalue, CUlimit,limit);
DEF_FN(CUresult,cuCtxGetCacheConfig_v3020,cuCtxGetCacheConfig,3020,0,CUfunc_cache*,pconfig);
DEF_FN(CUresult,cuCtxSetCacheConfig_v3020,cuCtxSetCacheConfig,3020,0,CUfunc_cache,config);
DEF_FN(CUresult,cuCtxGetSharedMemConfig_v4020,cuCtxGetSharedMemConfig,4020,0,CUsharedconfig*,pConfig);
DEF_FN(CUresult,cuCtxSetSharedMemConfig_v4020,cuCtxSetSharedMemConfig,4020,0,CUsharedconfig,config);
DEF_FN(CUresult,cuCtxGetApiVersion_v3020,cuCtxGetApiVersion,3020,0,CUcontext,ctx, unsigned int*,version);
DEF_FN(CUresult,cuCtxGetStreamPriorityRange_v5050,cuCtxGetStreamPriorityRange,5050,0,int*,leastPriority, int*,greatestPriority);
DEF_FN(CUresult,cuCtxResetPersistingL2Cache_v11000,cuCtxResetPersistingL2Cache,11000,0,void,);
DEF_FN(CUresult,cuCtxAttach_v2000,cuCtxAttach,2000,0,CUcontext*,pctx, unsigned int,flags);
DEF_FN(CUresult,cuCtxDetach_v2000,cuCtxDetach,2000,0,CUcontext,ctx);
DEF_FN(CUresult,cuCtxGetExecAffinity_v11040,cuCtxGetExecAffinity,11040,0,CUexecAffinityParam*,pExecAffinity, CUexecAffinityType,type);
DEF_FN(CUresult,cuModuleLoad_v2000,cuModuleLoad,2000,0,CUmodule*,module, const char*,fname);
DEF_FN(CUresult,cuModuleLoadData_v2000,cuModuleLoadData,2000,0,CUmodule*,module, const void*,image);
DEF_FN(CUresult,cuModuleLoadDataEx_v2010,cuModuleLoadDataEx,2010,0,CUmodule*,module, const void*,image, unsigned int,numOptions, CUjit_option*,options, void**,optionValues);
DEF_FN(CUresult,cuModuleLoadFatBinary_v2000,cuModuleLoadFatBinary,2000,0,CUmodule*,module, const void*,fatCubin);
DEF_FN(CUresult,cuModuleUnload_v2000,cuModuleUnload,2000,0,CUmodule,hmod);
// DEF_FN(CUresult,cuModuleGetFunction_v2000,cuModuleGetFunction,2000,0,CUfunction*,hfunc, CUmodule,hmod, const char*,name);
DEF_FN(CUresult,cuModuleGetGlobal_v3020,cuModuleGetGlobal,3020,0,CUdeviceptr_v2*,dptr, size_t*,bytes, CUmodule,hmod, const char*,name);
DEF_FN(CUresult,cuModuleGetTexRef_v2000,cuModuleGetTexRef,2000,0,CUtexref*,pTexRef, CUmodule,hmod, const char*,name);
DEF_FN(CUresult,cuModuleGetSurfRef_v3000,cuModuleGetSurfRef,3000,0,CUsurfref*,pSurfRef, CUmodule,hmod, const char*,name);
DEF_FN(CUresult,cuModuleGetFunctionCount,cuModuleGetFunctionCount,0,0,unsigned int*,count, CUmodule,hmod);
DEF_FN(CUresult,cuModuleEnumerateFunctions,cuModuleEnumerateFunctions,0,0,CUfunction*,functions, unsigned int,numFunctions, CUmodule,mod);
DEF_FN(CUresult,cuLinkCreate_v6050,cuLinkCreate,6050,0,unsigned int,numOptions, CUjit_option*,options, void**,optionValues, CUlinkState*,stateOut);
DEF_FN(CUresult,cuLinkAddData_v6050,cuLinkAddData,6050,0,CUlinkState,state, CUjitInputType,type, void*,data, size_t,size, const char*,name, unsigned int,numOptions, CUjit_option*,options, void**,optionValues);
DEF_FN(CUresult,cuLinkAddFile_v6050,cuLinkAddFile,6050,0,CUlinkState,state, CUjitInputType,type, const char*,path, unsigned int,numOptions, CUjit_option*,options, void**,optionValues);
DEF_FN(CUresult,cuLinkComplete_v5050,cuLinkComplete,5050,0,CUlinkState,state, void**,cubinOut, size_t*,sizeOut);
DEF_FN(CUresult,cuLinkDestroy_v5050,cuLinkDestroy,5050,0,CUlinkState,state);
DEF_FN(CUresult,cuMemGetInfo_v3020,cuMemGetInfo,3020,0,size_t*,free, size_t*,total);
DEF_FN(CUresult,cuMemAlloc_v3020,cuMemAlloc,3020,0,CUdeviceptr_v2*,dptr, size_t,bytesize);
DEF_FN(CUresult,cuMemAllocPitch_v3020,cuMemAllocPitch,3020,0,CUdeviceptr_v2*,dptr, size_t*,pPitch, size_t,WidthInBytes, size_t,Height, unsigned int,ElementSizeBytes);
DEF_FN(CUresult,cuMemFree_v3020,cuMemFree,3020,0,CUdeviceptr_v2,dptr);
DEF_FN(CUresult,cuMemGetAddressRange_v3020,cuMemGetAddressRange,3020,0,CUdeviceptr_v2*,pbase, size_t*,psize, CUdeviceptr_v2,dptr);
DEF_FN(CUresult,cuMemAllocHost_v3020,cuMemAllocHost,3020,0,void**,pp, size_t,bytesize);
DEF_FN(CUresult,cuMemFreeHost_v2000,cuMemFreeHost,2000,0,void*,p);
DEF_FN(CUresult,cuMemHostAlloc_v2020,cuMemHostAlloc,2020,0,void**,pp, size_t,bytesize, unsigned int,Flags);
DEF_FN(CUresult,cuMemHostGetDevicePointer_v3020,cuMemHostGetDevicePointer,3020,0,CUdeviceptr_v2*,pdptr, void*,p, unsigned int,Flags);
DEF_FN(CUresult,cuMemHostGetFlags_v2030,cuMemHostGetFlags,2030,0,unsigned int*,pFlags, void*,p);
DEF_FN(CUresult,cuMemAllocManaged_v6000,cuMemAllocManaged,6000,0,CUdeviceptr_v2*,dptr, size_t,bytesize, unsigned int,flags);
DEF_FN(CUresult,cuDeviceGetByPCIBusId_v4010,cuDeviceGetByPCIBusId,4010,0,CUdevice_v1*,dev, const char*,pciBusId);
DEF_FN(CUresult,cuDeviceGetPCIBusId_v4010,cuDeviceGetPCIBusId,4010,0,char*,pciBusId, int,len, CUdevice_v1,dev);
DEF_FN(CUresult,cuIpcGetEventHandle_v4010,cuIpcGetEventHandle,4010,0,CUipcEventHandle_v1*,pHandle, CUevent,event);
DEF_FN(CUresult,cuIpcOpenEventHandle_v4010,cuIpcOpenEventHandle,4010,0,CUevent*,phEvent, CUipcEventHandle_v1,handle);
DEF_FN(CUresult,cuIpcGetMemHandle_v4010,cuIpcGetMemHandle,4010,0,CUipcMemHandle_v1*,pHandle, CUdeviceptr_v2,dptr);
DEF_FN(CUresult,cuIpcOpenMemHandle_v11000,cuIpcOpenMemHandle,11000,0,CUdeviceptr_v2*,pdptr, CUipcMemHandle_v1,handle, unsigned int,Flags);
DEF_FN(CUresult,cuIpcCloseMemHandle_v4010,cuIpcCloseMemHandle,4010,0,CUdeviceptr_v2,dptr);
DEF_FN(CUresult,cuMemHostRegister_v6050,cuMemHostRegister,6050,0,void*,p, size_t,bytesize, unsigned int,Flags);
DEF_FN(CUresult,cuMemHostUnregister_v4000,cuMemHostUnregister,4000,0,void*,p);
DEF_FN(CUresult,cuMemcpy_v7000_ptds,cuMemcpy,7000,1,CUdeviceptr_v2,dst, CUdeviceptr_v2,src, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyPeer_v7000_ptds,cuMemcpyPeer,7000,1,CUdeviceptr_v2,dstDevice, CUcontext,dstContext, CUdeviceptr_v2,srcDevice, CUcontext,srcContext, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyHtoD_v7000_ptds,cuMemcpyHtoD,7000,1,CUdeviceptr_v2,dstDevice, const void*,srcHost, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoH_v7000_ptds,cuMemcpyDtoH,7000,1,void*,dstHost, CUdeviceptr_v2,srcDevice, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoD_v7000_ptds,cuMemcpyDtoD,7000,1,CUdeviceptr_v2,dstDevice, CUdeviceptr_v2,srcDevice, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoA_v7000_ptds,cuMemcpyDtoA,7000,1,CUarray,dstArray, size_t,dstOffset, CUdeviceptr_v2,srcDevice, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoD_v7000_ptds,cuMemcpyAtoD,7000,1,CUdeviceptr_v2,dstDevice, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyHtoA_v7000_ptds,cuMemcpyHtoA,7000,1,CUarray,dstArray, size_t,dstOffset, const void*,srcHost, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoH_v7000_ptds,cuMemcpyAtoH,7000,1,void*,dstHost, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoA_v7000_ptds,cuMemcpyAtoA,7000,1,CUarray,dstArray, size_t,dstOffset, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpy2D_v7000_ptds,cuMemcpy2D,7000,1,const CUDA_MEMCPY2D_v2*,pCopy);
DEF_FN(CUresult,cuMemcpy2DUnaligned_v7000_ptds,cuMemcpy2DUnaligned,7000,1,const CUDA_MEMCPY2D_v2*,pCopy);
DEF_FN(CUresult,cuMemcpy3D_v7000_ptds,cuMemcpy3D,7000,1,const CUDA_MEMCPY3D_v2*,pCopy);
DEF_FN(CUresult,cuMemcpy3DPeer_v7000_ptds,cuMemcpy3DPeer,7000,1,const CUDA_MEMCPY3D_PEER_v1*,pCopy);
DEF_FN(CUresult,cuMemcpyAsync_v7000_ptsz,cuMemcpyAsync,7000,2,CUdeviceptr_v2,dst, CUdeviceptr_v2,src, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyPeerAsync_v7000_ptsz,cuMemcpyPeerAsync,7000,2,CUdeviceptr_v2,dstDevice, CUcontext,dstContext, CUdeviceptr_v2,srcDevice, CUcontext,srcContext, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyHtoDAsync_v7000_ptsz,cuMemcpyHtoDAsync,7000,2,CUdeviceptr_v2,dstDevice, const void*,srcHost, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyDtoHAsync_v7000_ptsz,cuMemcpyDtoHAsync,7000,2,void*,dstHost, CUdeviceptr_v2,srcDevice, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyDtoDAsync_v7000_ptsz,cuMemcpyDtoDAsync,7000,2,CUdeviceptr_v2,dstDevice, CUdeviceptr_v2,srcDevice, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyHtoAAsync_v7000_ptsz,cuMemcpyHtoAAsync,7000,2,CUarray,dstArray, size_t,dstOffset, const void*,srcHost, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyAtoHAsync_v7000_ptsz,cuMemcpyAtoHAsync,7000,2,void*,dstHost, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy2DAsync_v7000_ptsz,cuMemcpy2DAsync,7000,2,const CUDA_MEMCPY2D_v2*,pCopy, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy3DAsync_v7000_ptsz,cuMemcpy3DAsync,7000,2,const CUDA_MEMCPY3D_v2*,pCopy, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy3DPeerAsync_v7000_ptsz,cuMemcpy3DPeerAsync,7000,2,const CUDA_MEMCPY3D_PEER_v1*,pCopy, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD8_v7000_ptds,cuMemsetD8,7000,1,CUdeviceptr_v2,dstDevice, unsigned char,uc, size_t,N);
DEF_FN(CUresult,cuMemsetD16_v7000_ptds,cuMemsetD16,7000,1,CUdeviceptr_v2,dstDevice, unsigned short,us, size_t,N);
DEF_FN(CUresult,cuMemsetD32_v7000_ptds,cuMemsetD32,7000,1,CUdeviceptr_v2,dstDevice, unsigned int,ui, size_t,N);
DEF_FN(CUresult,cuMemsetD2D8_v7000_ptds,cuMemsetD2D8,7000,1,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned char,uc, size_t,Width, size_t,Height);
DEF_FN(CUresult,cuMemsetD2D16_v7000_ptds,cuMemsetD2D16,7000,1,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned short,us, size_t,Width, size_t,Height);
DEF_FN(CUresult,cuMemsetD2D32_v7000_ptds,cuMemsetD2D32,7000,1,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned int,ui, size_t,Width, size_t,Height);
DEF_FN(CUresult,cuMemsetD8Async_v7000_ptsz,cuMemsetD8Async,7000,2,CUdeviceptr_v2,dstDevice, unsigned char,uc, size_t,N, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD16Async_v7000_ptsz,cuMemsetD16Async,7000,2,CUdeviceptr_v2,dstDevice, unsigned short,us, size_t,N, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD32Async_v7000_ptsz,cuMemsetD32Async,7000,2,CUdeviceptr_v2,dstDevice, unsigned int,ui, size_t,N, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D8Async_v7000_ptsz,cuMemsetD2D8Async,7000,2,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned char,uc, size_t,Width, size_t,Height, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D16Async_v7000_ptsz,cuMemsetD2D16Async,7000,2,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned short,us, size_t,Width, size_t,Height, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D32Async_v7000_ptsz,cuMemsetD2D32Async,7000,2,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned int,ui, size_t,Width, size_t,Height, CUstream,hStream);
DEF_FN(CUresult,cuArrayCreate_v3020,cuArrayCreate,3020,0,CUarray*,pHandle, const CUDA_ARRAY_DESCRIPTOR_v2*,pAllocateArray);
DEF_FN(CUresult,cuArrayGetDescriptor_v3020,cuArrayGetDescriptor,3020,0,CUDA_ARRAY_DESCRIPTOR_v2*,pArrayDescriptor, CUarray,hArray);
DEF_FN(CUresult,cuArrayGetSparseProperties_v11010,cuArrayGetSparseProperties,11010,0,CUDA_ARRAY_SPARSE_PROPERTIES_v1*,sparseProperties, CUarray,array);
DEF_FN(CUresult,cuMipmappedArrayGetSparseProperties_v11010,cuMipmappedArrayGetSparseProperties,11010,0,CUDA_ARRAY_SPARSE_PROPERTIES_v1*,sparseProperties, CUmipmappedArray,mipmap);
DEF_FN(CUresult,cuArrayGetMemoryRequirements_v11060,cuArrayGetMemoryRequirements,11060,0,CUDA_ARRAY_MEMORY_REQUIREMENTS_v1*,memoryRequirements, CUarray,array, CUdevice,device);
DEF_FN(CUresult,cuMipmappedArrayGetMemoryRequirements_v11060,cuMipmappedArrayGetMemoryRequirements,11060,0,CUDA_ARRAY_MEMORY_REQUIREMENTS_v1*,memoryRequirements, CUmipmappedArray,mipmap, CUdevice,device);
DEF_FN(CUresult,cuArrayGetPlane_v11020,cuArrayGetPlane,11020,0,CUarray*,pPlaneArray, CUarray,hArray, unsigned int,planeIdx);
DEF_FN(CUresult,cuArrayDestroy_v2000,cuArrayDestroy,2000,0,CUarray,hArray);
DEF_FN(CUresult,cuArray3DCreate_v3020,cuArray3DCreate,3020,0,CUarray*,pHandle, const CUDA_ARRAY3D_DESCRIPTOR_v2*,pAllocateArray);
DEF_FN(CUresult,cuArray3DGetDescriptor_v3020,cuArray3DGetDescriptor,3020,0,CUDA_ARRAY3D_DESCRIPTOR_v2*,pArrayDescriptor, CUarray,hArray);
DEF_FN(CUresult,cuMipmappedArrayCreate_v5000,cuMipmappedArrayCreate,5000,0,CUmipmappedArray*,pHandle, const CUDA_ARRAY3D_DESCRIPTOR_v2*,pMipmappedArrayDesc, unsigned int,numMipmapLevels);
DEF_FN(CUresult,cuMipmappedArrayGetLevel_v5000,cuMipmappedArrayGetLevel,5000,0,CUarray*,pLevelArray, CUmipmappedArray,hMipmappedArray, unsigned int,level);
DEF_FN(CUresult,cuMipmappedArrayDestroy_v5000,cuMipmappedArrayDestroy,5000,0,CUmipmappedArray,hMipmappedArray);
DEF_FN(CUresult,cuMemAddressReserve_v10020,cuMemAddressReserve,10020,0,CUdeviceptr_v2*,ptr, size_t,size, size_t,alignment, CUdeviceptr_v2,addr, unsigned long long,flags);
DEF_FN(CUresult,cuMemAddressFree_v10020,cuMemAddressFree,10020,0,CUdeviceptr_v2,ptr, size_t,size);
DEF_FN(CUresult,cuMemCreate_v10020,cuMemCreate,10020,0,CUmemGenericAllocationHandle_v1*,handle, size_t,size, const CUmemAllocationProp_v1*,prop, unsigned long long,flags);
DEF_FN(CUresult,cuMemRelease_v10020,cuMemRelease,10020,0,CUmemGenericAllocationHandle_v1,handle);
DEF_FN(CUresult,cuMemMap_v10020,cuMemMap,10020,0,CUdeviceptr_v2,ptr, size_t,size, size_t,offset, CUmemGenericAllocationHandle_v1,handle, unsigned long long,flags);
DEF_FN(CUresult,cuMemMapArrayAsync_v11010_ptsz,cuMemMapArrayAsync,11010,2,CUarrayMapInfo_v1*,mapInfoList, unsigned int,count, CUstream,hStream);
DEF_FN(CUresult,cuMemUnmap_v10020,cuMemUnmap,10020,0,CUdeviceptr_v2,ptr, size_t,size);
DEF_FN(CUresult,cuMemSetAccess_v10020,cuMemSetAccess,10020,0,CUdeviceptr_v2,ptr, size_t,size, const CUmemAccessDesc_v1*,desc, size_t,count);
DEF_FN(CUresult,cuMemGetAccess_v10020,cuMemGetAccess,10020,0,unsigned long long*,flags, const CUmemLocation_v1*,location, CUdeviceptr_v2,ptr);
DEF_FN(CUresult,cuMemExportToShareableHandle_v10020,cuMemExportToShareableHandle,10020,0,void*,shareableHandle, CUmemGenericAllocationHandle_v1,handle, CUmemAllocationHandleType,handleType, unsigned long long,flags);
DEF_FN(CUresult,cuMemImportFromShareableHandle_v10020,cuMemImportFromShareableHandle,10020,0,CUmemGenericAllocationHandle_v1*,handle, void*,osHandle, CUmemAllocationHandleType,shHandleType);
DEF_FN(CUresult,cuMemGetAllocationGranularity_v10020,cuMemGetAllocationGranularity,10020,0,size_t*,granularity, const CUmemAllocationProp_v1*,prop, CUmemAllocationGranularity_flags,option);
DEF_FN(CUresult,cuMemGetAllocationPropertiesFromHandle_v10020,cuMemGetAllocationPropertiesFromHandle,10020,0,CUmemAllocationProp_v1*,prop, CUmemGenericAllocationHandle_v1,handle);
DEF_FN(CUresult,cuMemRetainAllocationHandle_v11000,cuMemRetainAllocationHandle,11000,0,CUmemGenericAllocationHandle_v1*,handle, void*,addr);
DEF_FN(CUresult,cuMemFreeAsync_v11020_ptsz,cuMemFreeAsync,11020,2,CUdeviceptr_v2,dptr, CUstream,hStream);
DEF_FN(CUresult,cuMemAllocAsync_v11020_ptsz,cuMemAllocAsync,11020,2,CUdeviceptr_v2*,dptr, size_t,bytesize, CUstream,hStream);
DEF_FN(CUresult,cuMemPoolTrimTo_v11020,cuMemPoolTrimTo,11020,0,CUmemoryPool,pool, size_t,minBytesToKeep);
DEF_FN(CUresult,cuMemPoolSetAttribute_v11020,cuMemPoolSetAttribute,11020,0,CUmemoryPool,pool, CUmemPool_attribute,attr, void*,value);
DEF_FN(CUresult,cuMemPoolGetAttribute_v11020,cuMemPoolGetAttribute,11020,0,CUmemoryPool,pool, CUmemPool_attribute,attr, void*,value);
DEF_FN(CUresult,cuMemPoolSetAccess_v11020,cuMemPoolSetAccess,11020,0,CUmemoryPool,pool, const CUmemAccessDesc_v1*,map, size_t,count);
DEF_FN(CUresult,cuMemPoolGetAccess_v11020,cuMemPoolGetAccess,11020,0,CUmemAccess_flags*,flags, CUmemoryPool,memPool, CUmemLocation_v1*,location);
DEF_FN(CUresult,cuMemPoolCreate_v11020,cuMemPoolCreate,11020,0,CUmemoryPool*,pool, const CUmemPoolProps_v1*,poolProps);
DEF_FN(CUresult,cuMemPoolDestroy_v11020,cuMemPoolDestroy,11020,0,CUmemoryPool,pool);
DEF_FN(CUresult,cuMemAllocFromPoolAsync_v11020_ptsz,cuMemAllocFromPoolAsync,11020,2,CUdeviceptr_v2*,dptr, size_t,bytesize, CUmemoryPool,pool, CUstream,hStream);
DEF_FN(CUresult,cuMemPoolExportToShareableHandle_v11020,cuMemPoolExportToShareableHandle,11020,0,void*,handle_out, CUmemoryPool,pool, CUmemAllocationHandleType,handleType, unsigned long long,flags);
DEF_FN(CUresult,cuMemPoolImportFromShareableHandle_v11020,cuMemPoolImportFromShareableHandle,11020,0,CUmemoryPool*,pool_out, void*,handle, CUmemAllocationHandleType,handleType, unsigned long long,flags);
DEF_FN(CUresult,cuMemPoolExportPointer_v11020,cuMemPoolExportPointer,11020,0,CUmemPoolPtrExportData_v1*,shareData_out, CUdeviceptr_v2,ptr);
DEF_FN(CUresult,cuMemPoolImportPointer_v11020,cuMemPoolImportPointer,11020,0,CUdeviceptr_v2*,ptr_out, CUmemoryPool,pool, CUmemPoolPtrExportData_v1*,shareData);
DEF_FN(CUresult,cuPointerGetAttribute_v4000,cuPointerGetAttribute,4000,0,void*,data, CUpointer_attribute,attribute, CUdeviceptr_v2,ptr);
DEF_FN(CUresult,cuMemPrefetchAsync_v8000_ptsz,cuMemPrefetchAsync,8000,2,CUdeviceptr_v2,devPtr, size_t,count, CUdevice_v1,dstDevice, CUstream,hStream);
DEF_FN(CUresult,cuMemAdvise_v8000,cuMemAdvise,8000,0,CUdeviceptr_v2,devPtr, size_t,count, CUmem_advise,advice, CUdevice_v1,device);
DEF_FN(CUresult,cuMemAdvise_v12020,cuMemAdvise,12020,0,CUdeviceptr_v2,devPtr, size_t,count, CUmem_advise,advice, CUmemLocation_v1,location);
DEF_FN(CUresult,cuMemPrefetchAsync_v12020_ptsz,cuMemPrefetchAsync,12020,2,CUdeviceptr_v2,devPtr, size_t,count, CUmemLocation_v1,location, unsigned int,flags, CUstream,hStream);
DEF_FN(CUresult,cuMemRangeGetAttribute_v8000,cuMemRangeGetAttribute,8000,0,void*,data, size_t,dataSize, CUmem_range_attribute,attribute, CUdeviceptr_v2,devPtr, size_t,count);
DEF_FN(CUresult,cuMemRangeGetAttributes_v8000,cuMemRangeGetAttributes,8000,0,void**,data, size_t*,dataSizes, CUmem_range_attribute*,attributes, size_t,numAttributes, CUdeviceptr_v2,devPtr, size_t,count);
DEF_FN(CUresult,cuMulticastCreate_v12010,cuMulticastCreate,12010,0,CUmemGenericAllocationHandle*,mcHandle, const CUmulticastObjectProp*,prop);
DEF_FN(CUresult,cuMulticastAddDevice_v12010,cuMulticastAddDevice,12010,0,CUmemGenericAllocationHandle,mcHandle, CUdevice,dev);
DEF_FN(CUresult,cuMulticastBindMem_v12010,cuMulticastBindMem,12010,0,CUmemGenericAllocationHandle,mcHandle, size_t,mcOffset, CUmemGenericAllocationHandle,memHandle, size_t,memOffset, size_t,size, unsigned long long,flags);
DEF_FN(CUresult,cuMulticastBindAddr_v12010,cuMulticastBindAddr,12010,0,CUmemGenericAllocationHandle,mcHandle, size_t,mcOffset, CUdeviceptr,memptr, size_t,size, unsigned long long,flags);
DEF_FN(CUresult,cuMulticastUnbind_v12010,cuMulticastUnbind,12010,0,CUmemGenericAllocationHandle,mcHandle, CUdevice,dev, size_t,mcOffset, size_t,size);
DEF_FN(CUresult,cuMulticastGetGranularity_v12010,cuMulticastGetGranularity,12010,0,size_t*,granularity, const CUmulticastObjectProp*,prop, CUmulticastGranularity_flags,option);
DEF_FN(CUresult,cuPointerSetAttribute_v6000,cuPointerSetAttribute,6000,0,const void*,value, CUpointer_attribute,attribute, CUdeviceptr_v2,ptr);
DEF_FN(CUresult,cuPointerGetAttributes_v7000,cuPointerGetAttributes,7000,0,unsigned int,numAttributes, CUpointer_attribute*,attributes, void**,data, CUdeviceptr_v2,ptr);
DEF_FN(CUresult,cuStreamCreate_v2000,cuStreamCreate,2000,0,CUstream*,phStream, unsigned int,Flags);
DEF_FN(CUresult,cuStreamCreateWithPriority_v5050,cuStreamCreateWithPriority,5050,0,CUstream*,phStream, unsigned int,flags, int,priority);
DEF_FN(CUresult,cuStreamGetId_v12000,cuStreamGetId,12000,0,CUstream,hStream, unsigned long long*,streamId);
DEF_FN(CUresult,cuStreamGetId_v12000_ptsz,cuStreamGetId,12000,2,CUstream,hStream, unsigned long long*,streamId);
DEF_FN(CUresult,cuStreamGetPriority_v7000_ptsz,cuStreamGetPriority,7000,2,CUstream,hStream, int*,priority);
DEF_FN(CUresult,cuStreamGetFlags_v7000_ptsz,cuStreamGetFlags,7000,2,CUstream,hStream, unsigned int*,flags);
DEF_FN(CUresult,cuStreamGetCtx_v9020_ptsz,cuStreamGetCtx,9020,2,CUstream,hStream, CUcontext*,pctx);
DEF_FN(CUresult,cuStreamWaitEvent_v7000_ptsz,cuStreamWaitEvent,7000,2,CUstream,hStream, CUevent,hEvent, unsigned int,Flags);
DEF_FN(CUresult,cuStreamAddCallback_v7000_ptsz,cuStreamAddCallback,7000,2,CUstream,hStream, CUstreamCallback,callback, void*,userData, unsigned int,flags);
DEF_FN(CUresult,cuStreamBeginCapture_v10010_ptsz,cuStreamBeginCapture,10010,2,CUstream,hStream, CUstreamCaptureMode,mode);
DEF_FN(CUresult,cuStreamBeginCaptureToGraph_v12030_ptsz,cuStreamBeginCaptureToGraph,12030,2,CUstream,hStream, CUgraph,hGraph, const CUgraphNode*,dependencies, const CUgraphEdgeData*,dependencyData, size_t,numDependencies, CUstreamCaptureMode,mode);
DEF_FN(CUresult,cuThreadExchangeStreamCaptureMode_v10010,cuThreadExchangeStreamCaptureMode,10010,0,CUstreamCaptureMode*,mode);
DEF_FN(CUresult,cuStreamEndCapture_v10000_ptsz,cuStreamEndCapture,10000,2,CUstream,hStream, CUgraph*,phGraph);
DEF_FN(CUresult,cuStreamIsCapturing_v10000_ptsz,cuStreamIsCapturing,10000,2,CUstream,hStream, CUstreamCaptureStatus*,captureStatus);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v10010_ptsz,cuStreamGetCaptureInfo,10010,2,CUstream,hStream, CUstreamCaptureStatus*,captureStatus_out, cuuint64_t*,id_out);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v11030_ptsz,cuStreamGetCaptureInfo,11030,2,CUstream,hStream, CUstreamCaptureStatus*,captureStatus_out, cuuint64_t*,id_out, CUgraph*,graph_out, const CUgraphNode**,dependencies_out, size_t*,numDependencies_out);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v12030_ptsz,cuStreamGetCaptureInfo,12030,2,CUstream,hStream, CUstreamCaptureStatus*,captureStatus_out, cuuint64_t*,id_out, CUgraph*,graph_out, const CUgraphNode**,dependencies_out, const CUgraphEdgeData**,edgeData_out, size_t*,numDependencies_out);
DEF_FN(CUresult,cuStreamUpdateCaptureDependencies_v11030_ptsz,cuStreamUpdateCaptureDependencies,11030,2,CUstream,hStream, CUgraphNode*,dependencies, size_t,numDependencies, unsigned int,flags);
DEF_FN(CUresult,cuStreamUpdateCaptureDependencies_v12030_ptsz,cuStreamUpdateCaptureDependencies,12030,2,CUstream,hStream, CUgraphNode*,dependencies, const CUgraphEdgeData*,dependencyData, size_t,numDependencies, unsigned int,flags);
DEF_FN(CUresult,cuStreamAttachMemAsync_v7000_ptsz,cuStreamAttachMemAsync,7000,2,CUstream,hStream, CUdeviceptr_v2,dptr, size_t,length, unsigned int,flags);
DEF_FN(CUresult,cuStreamQuery_v7000_ptsz,cuStreamQuery,7000,2,CUstream,hStream);
DEF_FN(CUresult,cuStreamSynchronize_v7000_ptsz,cuStreamSynchronize,7000,2,CUstream,hStream);
DEF_FN(CUresult,cuStreamDestroy_v4000,cuStreamDestroy,4000,0,CUstream,hStream);
DEF_FN(CUresult,cuStreamCopyAttributes_v11000_ptsz,cuStreamCopyAttributes,11000,2,CUstream,dst, CUstream,src);
DEF_FN(CUresult,cuStreamGetAttribute_v11000_ptsz,cuStreamGetAttribute,11000,2,CUstream,hStream, CUstreamAttrID,attr, CUstreamAttrValue_v1*,value_out);
DEF_FN(CUresult,cuStreamSetAttribute_v11000_ptsz,cuStreamSetAttribute,11000,2,CUstream,hStream, CUstreamAttrID,attr, const CUstreamAttrValue_v1*,value);
DEF_FN(CUresult,cuEventCreate_v2000,cuEventCreate,2000,0,CUevent*,phEvent, unsigned int,Flags);
DEF_FN(CUresult,cuEventRecord_v7000_ptsz,cuEventRecord,7000,2,CUevent,hEvent, CUstream,hStream);
DEF_FN(CUresult,cuEventRecordWithFlags_v11010_ptsz,cuEventRecordWithFlags,11010,2,CUevent,hEvent, CUstream,hStream, unsigned int,flags);
DEF_FN(CUresult,cuEventQuery_v2000,cuEventQuery,2000,0,CUevent,hEvent);
DEF_FN(CUresult,cuEventSynchronize_v2000,cuEventSynchronize,2000,0,CUevent,hEvent);
DEF_FN(CUresult,cuEventDestroy_v4000,cuEventDestroy,4000,0,CUevent,hEvent);
DEF_FN(CUresult,cuEventElapsedTime_v2000,cuEventElapsedTime,2000,0,float*,pMilliseconds, CUevent,hStart, CUevent,hEnd);
DEF_FN(CUresult,cuImportExternalMemory_v10000,cuImportExternalMemory,10000,0,CUexternalMemory*,extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC_v1*,memHandleDesc);
DEF_FN(CUresult,cuExternalMemoryGetMappedBuffer_v10000,cuExternalMemoryGetMappedBuffer,10000,0,CUdeviceptr_v2*,devPtr, CUexternalMemory,extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC_v1*,bufferDesc);
DEF_FN(CUresult,cuExternalMemoryGetMappedMipmappedArray_v10000,cuExternalMemoryGetMappedMipmappedArray,10000,0,CUmipmappedArray*,mipmap, CUexternalMemory,extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC_v1*,mipmapDesc);
DEF_FN(CUresult,cuDestroyExternalMemory_v10000,cuDestroyExternalMemory,10000,0,CUexternalMemory,extMem);
DEF_FN(CUresult,cuImportExternalSemaphore_v10000,cuImportExternalSemaphore,10000,0,CUexternalSemaphore*,extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC_v1*,semHandleDesc);
DEF_FN(CUresult,cuSignalExternalSemaphoresAsync_v10000_ptsz,cuSignalExternalSemaphoresAsync,10000,2,const CUexternalSemaphore*,extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_v1*,paramsArray, unsigned int,numExtSems, CUstream,stream);
DEF_FN(CUresult,cuWaitExternalSemaphoresAsync_v10000_ptsz,cuWaitExternalSemaphoresAsync,10000,2,const CUexternalSemaphore*,extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_v1*,paramsArray, unsigned int,numExtSems, CUstream,stream);
DEF_FN(CUresult,cuDestroyExternalSemaphore_v10000,cuDestroyExternalSemaphore,10000,0,CUexternalSemaphore,extSem);
DEF_FN(CUresult,cuStreamWaitValue32_v8000_ptsz,cuStreamWaitValue32,8000,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue64_v9000_ptsz,cuStreamWaitValue64,9000,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue32_v8000_ptsz,cuStreamWriteValue32,8000,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue64_v9000_ptsz,cuStreamWriteValue64,9000,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamBatchMemOp_v8000_ptsz,cuStreamBatchMemOp,8000,2,CUstream,stream, unsigned int,count, CUstreamBatchMemOpParams_v1*,paramArray, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue32_v11070_ptsz,cuStreamWaitValue32,11070,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue64_v11070_ptsz,cuStreamWaitValue64,11070,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue32_v11070_ptsz,cuStreamWriteValue32,11070,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue64_v11070_ptsz,cuStreamWriteValue64,11070,2,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamBatchMemOp_v11070_ptsz,cuStreamBatchMemOp,11070,2,CUstream,stream, unsigned int,count, CUstreamBatchMemOpParams*,paramArray, unsigned int,flags);
DEF_FN(CUresult,cuFuncGetAttribute_v2020,cuFuncGetAttribute,2020,0,int*,pi, CUfunction_attribute,attrib, CUfunction,hfunc);
DEF_FN(CUresult,cuFuncSetAttribute_v9000,cuFuncSetAttribute,9000,0,CUfunction,hfunc, CUfunction_attribute,attrib, int,value);
DEF_FN(CUresult,cuFuncSetCacheConfig_v3000,cuFuncSetCacheConfig,3000,0,CUfunction,hfunc, CUfunc_cache,config);
DEF_FN(CUresult,cuFuncSetSharedMemConfig_v4020,cuFuncSetSharedMemConfig,4020,0,CUfunction,hfunc, CUsharedconfig,config);
DEF_FN(CUresult,cuFuncGetName_v12030,cuFuncGetName,12030,0,const char**,name, CUfunction,hfunc);
DEF_FN(CUresult,cuFuncGetParamInfo_v12040,cuFuncGetParamInfo,12040,0,CUfunction,func, size_t,paramIndex, size_t*,paramOffset, size_t*,paramSize);
DEF_FN(CUresult,cuFuncIsLoaded_v12040,cuFuncIsLoaded,12040,0,CUfunctionLoadingState*,state, CUfunction,hfunc);
DEF_FN(CUresult,cuFuncLoad_v12040,cuFuncLoad,12040,0,CUfunction,hfunc);
DEF_FN(CUresult,cuLaunchKernel_v7000_ptsz,cuLaunchKernel,7000,2,CUfunction,f, unsigned int,gridDimX, unsigned int,gridDimY, unsigned int,gridDimZ, unsigned int,blockDimX, unsigned int,blockDimY, unsigned int,blockDimZ, unsigned int,sharedMemBytes, CUstream,hStream, void**,kernelParams, void**,extra);
DEF_FN(CUresult,cuLaunchKernelEx_v11060_ptsz,cuLaunchKernelEx,11060,2,const CUlaunchConfig*,config, CUfunction,f, void**,kernelParams, void**,extra);
DEF_FN(CUresult,cuLaunchCooperativeKernel_v9000_ptsz,cuLaunchCooperativeKernel,9000,2,CUfunction,f, unsigned int,gridDimX, unsigned int,gridDimY, unsigned int,gridDimZ, unsigned int,blockDimX, unsigned int,blockDimY, unsigned int,blockDimZ, unsigned int,sharedMemBytes, CUstream,hStream, void**,kernelParams);
DEF_FN(CUresult,cuLaunchCooperativeKernelMultiDevice_v9000,cuLaunchCooperativeKernelMultiDevice,9000,0,CUDA_LAUNCH_PARAMS_v1*,launchParamsList, unsigned int,numDevices, unsigned int,flags);
DEF_FN(CUresult,cuLaunchHostFunc_v10000_ptsz,cuLaunchHostFunc,10000,2,CUstream,hStream, CUhostFn,fn, void*,userData);
DEF_FN(CUresult,cuFuncSetBlockShape_v2000,cuFuncSetBlockShape,2000,0,CUfunction,hfunc, int,x, int,y, int,z);
DEF_FN(CUresult,cuFuncSetSharedSize_v2000,cuFuncSetSharedSize,2000,0,CUfunction,hfunc, unsigned int,bytes);
DEF_FN(CUresult,cuParamSetSize_v2000,cuParamSetSize,2000,0,CUfunction,hfunc, unsigned int,numbytes);
DEF_FN(CUresult,cuParamSeti_v2000,cuParamSeti,2000,0,CUfunction,hfunc, int,offset, unsigned int,value);
DEF_FN(CUresult,cuParamSetf_v2000,cuParamSetf,2000,0,CUfunction,hfunc, int,offset, float,value);
DEF_FN(CUresult,cuParamSetv_v2000,cuParamSetv,2000,0,CUfunction,hfunc, int,offset, void*,ptr, unsigned int,numbytes);
DEF_FN(CUresult,cuLaunch_v2000,cuLaunch,2000,0,CUfunction,f);
DEF_FN(CUresult,cuLaunchGrid_v2000,cuLaunchGrid,2000,0,CUfunction,f, int,grid_width, int,grid_height);
DEF_FN(CUresult,cuLaunchGridAsync_v2000,cuLaunchGridAsync,2000,0,CUfunction,f, int,grid_width, int,grid_height, CUstream,hStream);
DEF_FN(CUresult,cuParamSetTexRef_v2000,cuParamSetTexRef,2000,0,CUfunction,hfunc, int,texunit, CUtexref,hTexRef);
DEF_FN(CUresult,cuGraphCreate_v10000,cuGraphCreate,10000,0,CUgraph*,phGraph, unsigned int,flags);
DEF_FN(CUresult,cuGraphAddKernelNode_v10000,cuGraphAddKernelNode,10000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_KERNEL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphKernelNodeGetParams_v10000,cuGraphKernelNodeGetParams,10000,0,CUgraphNode,hNode, CUDA_KERNEL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphKernelNodeSetParams_v10000,cuGraphKernelNodeSetParams,10000,0,CUgraphNode,hNode, const CUDA_KERNEL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphAddKernelNode_v12000,cuGraphAddKernelNode,12000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_KERNEL_NODE_PARAMS_v2*,nodeParams);
DEF_FN(CUresult,cuGraphKernelNodeGetParams_v12000,cuGraphKernelNodeGetParams,12000,0,CUgraphNode,hNode, CUDA_KERNEL_NODE_PARAMS_v2*,nodeParams);
DEF_FN(CUresult,cuGraphKernelNodeSetParams_v12000,cuGraphKernelNodeSetParams,12000,0,CUgraphNode,hNode, const CUDA_KERNEL_NODE_PARAMS_v2*,nodeParams);
DEF_FN(CUresult,cuGraphAddMemcpyNode_v10000,cuGraphAddMemcpyNode,10000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_MEMCPY3D_v2*,copyParams, CUcontext,ctx);
DEF_FN(CUresult,cuGraphMemcpyNodeGetParams_v10000,cuGraphMemcpyNodeGetParams,10000,0,CUgraphNode,hNode, CUDA_MEMCPY3D_v2*,nodeParams);
DEF_FN(CUresult,cuGraphMemcpyNodeSetParams_v10000,cuGraphMemcpyNodeSetParams,10000,0,CUgraphNode,hNode, const CUDA_MEMCPY3D_v2*,nodeParams);
DEF_FN(CUresult,cuGraphAddMemsetNode_v10000,cuGraphAddMemsetNode,10000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_MEMSET_NODE_PARAMS_v1*,memsetParams, CUcontext,ctx);
DEF_FN(CUresult,cuGraphMemsetNodeGetParams_v10000,cuGraphMemsetNodeGetParams,10000,0,CUgraphNode,hNode, CUDA_MEMSET_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphMemsetNodeSetParams_v10000,cuGraphMemsetNodeSetParams,10000,0,CUgraphNode,hNode, const CUDA_MEMSET_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphAddHostNode_v10000,cuGraphAddHostNode,10000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_HOST_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphHostNodeGetParams_v10000,cuGraphHostNodeGetParams,10000,0,CUgraphNode,hNode, CUDA_HOST_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphHostNodeSetParams_v10000,cuGraphHostNodeSetParams,10000,0,CUgraphNode,hNode, const CUDA_HOST_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphAddChildGraphNode_v10000,cuGraphAddChildGraphNode,10000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, CUgraph,childGraph);
DEF_FN(CUresult,cuGraphChildGraphNodeGetGraph_v10000,cuGraphChildGraphNodeGetGraph,10000,0,CUgraphNode,hNode, CUgraph*,phGraph);
DEF_FN(CUresult,cuGraphAddEmptyNode_v10000,cuGraphAddEmptyNode,10000,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies);
DEF_FN(CUresult,cuGraphAddEventRecordNode_v11010,cuGraphAddEventRecordNode,11010,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, CUevent,event);
DEF_FN(CUresult,cuGraphEventRecordNodeGetEvent_v11010,cuGraphEventRecordNodeGetEvent,11010,0,CUgraphNode,hNode, CUevent*,event_out);
DEF_FN(CUresult,cuGraphEventRecordNodeSetEvent_v11010,cuGraphEventRecordNodeSetEvent,11010,0,CUgraphNode,hNode, CUevent,event);
DEF_FN(CUresult,cuGraphAddEventWaitNode_v11010,cuGraphAddEventWaitNode,11010,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, CUevent,event);
DEF_FN(CUresult,cuGraphEventWaitNodeGetEvent_v11010,cuGraphEventWaitNodeGetEvent,11010,0,CUgraphNode,hNode, CUevent*,event_out);
DEF_FN(CUresult,cuGraphEventWaitNodeSetEvent_v11010,cuGraphEventWaitNodeSetEvent,11010,0,CUgraphNode,hNode, CUevent,event);
DEF_FN(CUresult,cuGraphAddExternalSemaphoresSignalNode_v11020,cuGraphAddExternalSemaphoresSignalNode,11020,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphExternalSemaphoresSignalNodeGetParams_v11020,cuGraphExternalSemaphoresSignalNodeGetParams,11020,0,CUgraphNode,hNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_v1*,params_out);
DEF_FN(CUresult,cuGraphExternalSemaphoresSignalNodeSetParams_v11020,cuGraphExternalSemaphoresSignalNodeSetParams,11020,0,CUgraphNode,hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphAddExternalSemaphoresWaitNode_v11020,cuGraphAddExternalSemaphoresWaitNode,11020,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_EXT_SEM_WAIT_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphExternalSemaphoresWaitNodeGetParams_v11020,cuGraphExternalSemaphoresWaitNodeGetParams,11020,0,CUgraphNode,hNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS_v1*,params_out);
DEF_FN(CUresult,cuGraphExternalSemaphoresWaitNodeSetParams_v11020,cuGraphExternalSemaphoresWaitNodeSetParams,11020,0,CUgraphNode,hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphAddBatchMemOpNode_v11070,cuGraphAddBatchMemOpNode,11070,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, const CUDA_BATCH_MEM_OP_NODE_PARAMS*,nodeParams);
DEF_FN(CUresult,cuGraphBatchMemOpNodeGetParams_v11070,cuGraphBatchMemOpNodeGetParams,11070,0,CUgraphNode,hNode, CUDA_BATCH_MEM_OP_NODE_PARAMS*,nodeParams_out);
DEF_FN(CUresult,cuGraphBatchMemOpNodeSetParams_v11070,cuGraphBatchMemOpNodeSetParams,11070,0,CUgraphNode,hNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS*,nodeParams);
DEF_FN(CUresult,cuGraphExecBatchMemOpNodeSetParams_v11070,cuGraphExecBatchMemOpNodeSetParams,11070,0,CUgraphExec,graphExec, CUgraphNode,node, const CUDA_BATCH_MEM_OP_NODE_PARAMS*,nodeParams);
DEF_FN(CUresult,cuGraphClone_v10000,cuGraphClone,10000,0,CUgraph*,phGraphClone, CUgraph,originalGraph);
DEF_FN(CUresult,cuGraphNodeFindInClone_v10000,cuGraphNodeFindInClone,10000,0,CUgraphNode*,phNode, CUgraphNode,hOriginalNode, CUgraph,hClonedGraph);
DEF_FN(CUresult,cuGraphNodeGetType_v10000,cuGraphNodeGetType,10000,0,CUgraphNode,hNode, CUgraphNodeType*,type);
DEF_FN(CUresult,cuGraphGetNodes_v10000,cuGraphGetNodes,10000,0,CUgraph,hGraph, CUgraphNode*,nodes, size_t*,numNodes);
DEF_FN(CUresult,cuGraphGetRootNodes_v10000,cuGraphGetRootNodes,10000,0,CUgraph,hGraph, CUgraphNode*,rootNodes, size_t*,numRootNodes);
DEF_FN(CUresult,cuGraphGetEdges_v10000,cuGraphGetEdges,10000,0,CUgraph,hGraph, CUgraphNode*,from, CUgraphNode*,to, size_t*,numEdges);
DEF_FN(CUresult,cuGraphGetEdges_v12030,cuGraphGetEdges,12030,0,CUgraph,hGraph, CUgraphNode*,from, CUgraphNode*,to, CUgraphEdgeData*,edgeData, size_t*,numEdges);
DEF_FN(CUresult,cuGraphNodeGetDependencies_v10000,cuGraphNodeGetDependencies,10000,0,CUgraphNode,hNode, CUgraphNode*,dependencies, size_t*,numDependencies);
DEF_FN(CUresult,cuGraphNodeGetDependencies_v12030,cuGraphNodeGetDependencies,12030,0,CUgraphNode,hNode, CUgraphNode*,dependencies, CUgraphEdgeData*,edgeData, size_t*,numDependencies);
DEF_FN(CUresult,cuGraphNodeGetDependentNodes_v10000,cuGraphNodeGetDependentNodes,10000,0,CUgraphNode,hNode, CUgraphNode*,dependentNodes, size_t*,numDependentNodes);
DEF_FN(CUresult,cuGraphNodeGetDependentNodes_v12030,cuGraphNodeGetDependentNodes,12030,0,CUgraphNode,hNode, CUgraphNode*,dependentNodes, CUgraphEdgeData*,edgeData, size_t*,numDependentNodes);
DEF_FN(CUresult,cuGraphAddDependencies_v10000,cuGraphAddDependencies,10000,0,CUgraph,hGraph, const CUgraphNode*,from, const CUgraphNode*,to, size_t,numDependencies);
DEF_FN(CUresult,cuGraphAddDependencies_v12030,cuGraphAddDependencies,12030,0,CUgraph,hGraph, const CUgraphNode*,from, const CUgraphNode*,to, const CUgraphEdgeData*,edgeData, size_t,numDependencies);
DEF_FN(CUresult,cuGraphRemoveDependencies_v10000,cuGraphRemoveDependencies,10000,0,CUgraph,hGraph, const CUgraphNode*,from, const CUgraphNode*,to, size_t,numDependencies);
DEF_FN(CUresult,cuGraphRemoveDependencies_v12030,cuGraphRemoveDependencies,12030,0,CUgraph,hGraph, const CUgraphNode*,from, const CUgraphNode*,to, const CUgraphEdgeData*,edgeData, size_t,numDependencies);
DEF_FN(CUresult,cuGraphDestroyNode_v10000,cuGraphDestroyNode,10000,0,CUgraphNode,hNode);
DEF_FN(CUresult,cuGraphInstantiateWithFlags_v11040,cuGraphInstantiateWithFlags,11040,0,CUgraphExec*,phGraphExec, CUgraph,hGraph, unsigned long long,flags);
DEF_FN(CUresult,cuGraphInstantiateWithParams_v12000_ptsz,cuGraphInstantiateWithParams,12000,2,CUgraphExec*,phGraphExec, CUgraph,hGraph, CUDA_GRAPH_INSTANTIATE_PARAMS*,instantiateParams);
DEF_FN(CUresult,cuGraphExecGetFlags_v12000,cuGraphExecGetFlags,12000,0,CUgraphExec,hGraphExec, cuuint64_t*,flags);
DEF_FN(CUresult,cuGraphExecKernelNodeSetParams_v10010,cuGraphExecKernelNodeSetParams,10010,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_KERNEL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphExecKernelNodeSetParams_v12000,cuGraphExecKernelNodeSetParams,12000,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_KERNEL_NODE_PARAMS_v2*,nodeParams);
DEF_FN(CUresult,cuGraphExecMemcpyNodeSetParams_v10020,cuGraphExecMemcpyNodeSetParams,10020,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_MEMCPY3D_v2*,copyParams, CUcontext,ctx);
DEF_FN(CUresult,cuGraphExecMemsetNodeSetParams_v10020,cuGraphExecMemsetNodeSetParams,10020,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_MEMSET_NODE_PARAMS_v1*,memsetParams, CUcontext,ctx);
DEF_FN(CUresult,cuGraphExecHostNodeSetParams_v10020,cuGraphExecHostNodeSetParams,10020,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_HOST_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphExecChildGraphNodeSetParams_v11010,cuGraphExecChildGraphNodeSetParams,11010,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, CUgraph,childGraph);
DEF_FN(CUresult,cuGraphExecEventRecordNodeSetEvent_v11010,cuGraphExecEventRecordNodeSetEvent,11010,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, CUevent,event);
DEF_FN(CUresult,cuGraphExecEventWaitNodeSetEvent_v11010,cuGraphExecEventWaitNodeSetEvent,11010,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, CUevent,event);
DEF_FN(CUresult,cuGraphExecExternalSemaphoresSignalNodeSetParams_v11020,cuGraphExecExternalSemaphoresSignalNodeSetParams,11020,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphExecExternalSemaphoresWaitNodeSetParams_v11020,cuGraphExecExternalSemaphoresWaitNodeSetParams,11020,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS_v1*,nodeParams);
DEF_FN(CUresult,cuGraphUpload_v11010_ptsz,cuGraphUpload,11010,2,CUgraphExec,hGraphExec, CUstream,hStream);
DEF_FN(CUresult,cuGraphLaunch_v10000_ptsz,cuGraphLaunch,10000,2,CUgraphExec,hGraphExec, CUstream,hStream);
DEF_FN(CUresult,cuGraphExecDestroy_v10000,cuGraphExecDestroy,10000,0,CUgraphExec,hGraphExec);
DEF_FN(CUresult,cuGraphDestroy_v10000,cuGraphDestroy,10000,0,CUgraph,hGraph);
DEF_FN(CUresult,cuGraphExecUpdate_v10020,cuGraphExecUpdate,10020,0,CUgraphExec,hGraphExec, CUgraph,hGraph, CUgraphNode*,hErrorNode_out, CUgraphExecUpdateResult*,updateResult_out);
DEF_FN(CUresult,cuGraphExecUpdate_v12000,cuGraphExecUpdate,12000,0,CUgraphExec,hGraphExec, CUgraph,hGraph, CUgraphExecUpdateResultInfo*,resultInfo);
DEF_FN(CUresult,cuGraphKernelNodeCopyAttributes_v11000,cuGraphKernelNodeCopyAttributes,11000,0,CUgraphNode,dst, CUgraphNode,src);
DEF_FN(CUresult,cuGraphKernelNodeGetAttribute_v11000,cuGraphKernelNodeGetAttribute,11000,0,CUgraphNode,hNode, CUkernelNodeAttrID,attr, CUkernelNodeAttrValue_v1*,value_out);
DEF_FN(CUresult,cuGraphKernelNodeSetAttribute_v11000,cuGraphKernelNodeSetAttribute,11000,0,CUgraphNode,hNode, CUkernelNodeAttrID,attr, const CUkernelNodeAttrValue_v1*,value);
DEF_FN(CUresult,cuGraphDebugDotPrint_v11030,cuGraphDebugDotPrint,11030,0,CUgraph,hGraph, const char*,path, unsigned int,flags);
DEF_FN(CUresult,cuGraphAddMemAllocNode_v11040,cuGraphAddMemAllocNode,11040,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, CUDA_MEM_ALLOC_NODE_PARAMS*,nodeParams);
DEF_FN(CUresult,cuGraphMemAllocNodeGetParams_v11040,cuGraphMemAllocNodeGetParams,11040,0,CUgraphNode,hNode, CUDA_MEM_ALLOC_NODE_PARAMS*,params_out);
DEF_FN(CUresult,cuGraphAddMemFreeNode_v11040,cuGraphAddMemFreeNode,11040,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, CUdeviceptr,dptr);
DEF_FN(CUresult,cuGraphMemFreeNodeGetParams_v11040,cuGraphMemFreeNodeGetParams,11040,0,CUgraphNode,hNode, CUdeviceptr*,dptr_out);
DEF_FN(CUresult,cuGraphNodeSetEnabled_v11060,cuGraphNodeSetEnabled,11060,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, unsigned int,isEnabled);
DEF_FN(CUresult,cuGraphNodeGetEnabled_v11060,cuGraphNodeGetEnabled,11060,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, unsigned int*,isEnabled);
DEF_FN(CUresult,cuGraphAddNode_v12020,cuGraphAddNode,12020,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, size_t,numDependencies, CUgraphNodeParams*,nodeParams);
DEF_FN(CUresult,cuGraphAddNode_v12030,cuGraphAddNode,12030,0,CUgraphNode*,phGraphNode, CUgraph,hGraph, const CUgraphNode*,dependencies, const CUgraphEdgeData*,dependencyData, size_t,numDependencies, CUgraphNodeParams*,nodeParams);
DEF_FN(CUresult,cuGraphNodeSetParams_v12020,cuGraphNodeSetParams,12020,0,CUgraphNode,hNode, CUgraphNodeParams*,nodeParams);
DEF_FN(CUresult,cuGraphExecNodeSetParams_v12020,cuGraphExecNodeSetParams,12020,0,CUgraphExec,hGraphExec, CUgraphNode,hNode, CUgraphNodeParams*,nodeParams);
DEF_FN(CUresult,cuGraphConditionalHandleCreate_v12030,cuGraphConditionalHandleCreate,12030,0,CUgraphConditionalHandle*,pHandle_out, CUgraph,hGraph, CUcontext,ctx, unsigned int,defaultLaunchValue, unsigned int,flags);
DEF_FN(CUresult,cuDeviceGraphMemTrim_v11040,cuDeviceGraphMemTrim,11040,0,CUdevice,device);
DEF_FN(CUresult,cuDeviceGetGraphMemAttribute_v11040,cuDeviceGetGraphMemAttribute,11040,0,CUdevice,device, CUgraphMem_attribute,attr, void*,value);
DEF_FN(CUresult,cuDeviceSetGraphMemAttribute_v11040,cuDeviceSetGraphMemAttribute,11040,0,CUdevice,device, CUgraphMem_attribute,attr, void*,value);
DEF_FN(CUresult,cuOccupancyMaxActiveBlocksPerMultiprocessor_v6050,cuOccupancyMaxActiveBlocksPerMultiprocessor,6050,0,int*,numBlocks, CUfunction,func, int,blockSize, size_t,dynamicSMemSize);
DEF_FN(CUresult,cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags_v7000,cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags,7000,0,int*,numBlocks, CUfunction,func, int,blockSize, size_t,dynamicSMemSize, unsigned int,flags);
DEF_FN(CUresult,cuOccupancyMaxPotentialBlockSize_v6050,cuOccupancyMaxPotentialBlockSize,6050,0,int*,minGridSize, int*,blockSize, CUfunction,func, CUoccupancyB2DSize,blockSizeToDynamicSMemSize, size_t,dynamicSMemSize, int,blockSizeLimit);
DEF_FN(CUresult,cuOccupancyMaxPotentialBlockSizeWithFlags_v7000,cuOccupancyMaxPotentialBlockSizeWithFlags,7000,0,int*,minGridSize, int*,blockSize, CUfunction,func, CUoccupancyB2DSize,blockSizeToDynamicSMemSize, size_t,dynamicSMemSize, int,blockSizeLimit, unsigned int,flags);
DEF_FN(CUresult,cuOccupancyAvailableDynamicSMemPerBlock_v10020,cuOccupancyAvailableDynamicSMemPerBlock,10020,0,size_t*,dynamicSmemSize, CUfunction,func, int,numBlocks, int,blockSize);
DEF_FN(CUresult,cuOccupancyMaxPotentialClusterSize_v11070,cuOccupancyMaxPotentialClusterSize,11070,0,int*,clusterSize, CUfunction,func, const CUlaunchConfig*,config);
DEF_FN(CUresult,cuOccupancyMaxActiveClusters_v11070,cuOccupancyMaxActiveClusters,11070,0,int*,numClusters, CUfunction,func, const CUlaunchConfig*,config);
DEF_FN(CUresult,cuTexRefSetArray_v2000,cuTexRefSetArray,2000,0,CUtexref,hTexRef, CUarray,hArray, unsigned int,Flags);
DEF_FN(CUresult,cuTexRefSetMipmappedArray_v5000,cuTexRefSetMipmappedArray,5000,0,CUtexref,hTexRef, CUmipmappedArray,hMipmappedArray, unsigned int,Flags);
DEF_FN(CUresult,cuTexRefSetAddress_v3020,cuTexRefSetAddress,3020,0,size_t*,ByteOffset, CUtexref,hTexRef, CUdeviceptr_v2,dptr, size_t,bytes);
DEF_FN(CUresult,cuTexRefSetAddress2D_v4010,cuTexRefSetAddress2D,4010,0,CUtexref,hTexRef, const CUDA_ARRAY_DESCRIPTOR_v2*,desc, CUdeviceptr_v2,dptr, size_t,Pitch);
DEF_FN(CUresult,cuTexRefSetFormat_v2000,cuTexRefSetFormat,2000,0,CUtexref,hTexRef, CUarray_format,fmt, int,NumPackedComponents);
DEF_FN(CUresult,cuTexRefSetAddressMode_v2000,cuTexRefSetAddressMode,2000,0,CUtexref,hTexRef, int,dim, CUaddress_mode,am);
DEF_FN(CUresult,cuTexRefSetFilterMode_v2000,cuTexRefSetFilterMode,2000,0,CUtexref,hTexRef, CUfilter_mode,fm);
DEF_FN(CUresult,cuTexRefSetMipmapFilterMode_v5000,cuTexRefSetMipmapFilterMode,5000,0,CUtexref,hTexRef, CUfilter_mode,fm);
DEF_FN(CUresult,cuTexRefSetMipmapLevelBias_v5000,cuTexRefSetMipmapLevelBias,5000,0,CUtexref,hTexRef, float,bias);
DEF_FN(CUresult,cuTexRefSetMipmapLevelClamp_v5000,cuTexRefSetMipmapLevelClamp,5000,0,CUtexref,hTexRef, float,minMipmapLevelClamp, float,maxMipmapLevelClamp);
DEF_FN(CUresult,cuTexRefSetMaxAnisotropy_v5000,cuTexRefSetMaxAnisotropy,5000,0,CUtexref,hTexRef, unsigned int,maxAniso);
DEF_FN(CUresult,cuTexRefSetBorderColor_v8000,cuTexRefSetBorderColor,8000,0,CUtexref,hTexRef, float*,pBorderColor);
DEF_FN(CUresult,cuTexRefSetFlags_v2000,cuTexRefSetFlags,2000,0,CUtexref,hTexRef, unsigned int,Flags);
DEF_FN(CUresult,cuTexRefGetAddress_v3020,cuTexRefGetAddress,3020,0,CUdeviceptr_v2*,pdptr, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetArray_v2000,cuTexRefGetArray,2000,0,CUarray*,phArray, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmappedArray_v5000,cuTexRefGetMipmappedArray,5000,0,CUmipmappedArray*,phMipmappedArray, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetAddressMode_v2000,cuTexRefGetAddressMode,2000,0,CUaddress_mode*,pam, CUtexref,hTexRef, int,dim);
DEF_FN(CUresult,cuTexRefGetFilterMode_v2000,cuTexRefGetFilterMode,2000,0,CUfilter_mode*,pfm, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetFormat_v2000,cuTexRefGetFormat,2000,0,CUarray_format*,pFormat, int*,pNumChannels, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmapFilterMode_v5000,cuTexRefGetMipmapFilterMode,5000,0,CUfilter_mode*,pfm, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmapLevelBias_v5000,cuTexRefGetMipmapLevelBias,5000,0,float*,pbias, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMipmapLevelClamp_v5000,cuTexRefGetMipmapLevelClamp,5000,0,float*,pminMipmapLevelClamp, float*,pmaxMipmapLevelClamp, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetMaxAnisotropy_v5000,cuTexRefGetMaxAnisotropy,5000,0,int*,pmaxAniso, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetBorderColor_v8000,cuTexRefGetBorderColor,8000,0,float*,pBorderColor, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefGetFlags_v2000,cuTexRefGetFlags,2000,0,unsigned int*,pFlags, CUtexref,hTexRef);
DEF_FN(CUresult,cuTexRefCreate_v2000,cuTexRefCreate,2000,0,CUtexref*,pTexRef);
DEF_FN(CUresult,cuTexRefDestroy_v2000,cuTexRefDestroy,2000,0,CUtexref,hTexRef);
DEF_FN(CUresult,cuSurfRefSetArray_v3000,cuSurfRefSetArray,3000,0,CUsurfref,hSurfRef, CUarray,hArray, unsigned int,Flags);
DEF_FN(CUresult,cuSurfRefGetArray_v3000,cuSurfRefGetArray,3000,0,CUarray*,phArray, CUsurfref,hSurfRef);
DEF_FN(CUresult,cuTexObjectCreate_v5000,cuTexObjectCreate,5000,0,CUtexObject_v1*,pTexObject, const CUDA_RESOURCE_DESC_v1*,pResDesc, const CUDA_TEXTURE_DESC_v1*,pTexDesc, const CUDA_RESOURCE_VIEW_DESC_v1*,pResViewDesc);
DEF_FN(CUresult,cuTexObjectDestroy_v5000,cuTexObjectDestroy,5000,0,CUtexObject_v1,texObject);
DEF_FN(CUresult,cuTexObjectGetResourceDesc_v5000,cuTexObjectGetResourceDesc,5000,0,CUDA_RESOURCE_DESC_v1*,pResDesc, CUtexObject_v1,texObject);
DEF_FN(CUresult,cuTexObjectGetTextureDesc_v5000,cuTexObjectGetTextureDesc,5000,0,CUDA_TEXTURE_DESC_v1*,pTexDesc, CUtexObject_v1,texObject);
DEF_FN(CUresult,cuTexObjectGetResourceViewDesc_v5000,cuTexObjectGetResourceViewDesc,5000,0,CUDA_RESOURCE_VIEW_DESC_v1*,pResViewDesc, CUtexObject_v1,texObject);
DEF_FN(CUresult,cuSurfObjectCreate_v5000,cuSurfObjectCreate,5000,0,CUsurfObject_v1*,pSurfObject, const CUDA_RESOURCE_DESC_v1*,pResDesc);
DEF_FN(CUresult,cuSurfObjectDestroy_v5000,cuSurfObjectDestroy,5000,0,CUsurfObject_v1,surfObject);
DEF_FN(CUresult,cuSurfObjectGetResourceDesc_v5000,cuSurfObjectGetResourceDesc,5000,0,CUDA_RESOURCE_DESC_v1*,pResDesc, CUsurfObject_v1,surfObject);
DEF_FN(CUresult,cuTensorMapEncodeTiled_v12000,cuTensorMapEncodeTiled,12000,0,CUtensorMap*,tensorMap, CUtensorMapDataType,tensorDataType, cuuint32_t,tensorRank, void*,globalAddress, const cuuint64_t*,globalDim, const cuuint64_t*,globalStrides, const cuuint32_t*,boxDim, const cuuint32_t*,elementStrides, CUtensorMapInterleave,interleave, CUtensorMapSwizzle,swizzle, CUtensorMapL2promotion,l2Promotion, CUtensorMapFloatOOBfill,oobFill);
DEF_FN(CUresult,cuTensorMapEncodeIm2col_v12000,cuTensorMapEncodeIm2col,12000,0,CUtensorMap*,tensorMap, CUtensorMapDataType,tensorDataType, cuuint32_t,tensorRank, void*,globalAddress, const cuuint64_t*,globalDim, const cuuint64_t*,globalStrides, const int*,pixelBoxLowerCorner, const int*,pixelBoxUpperCorner, cuuint32_t,channelsPerPixel, cuuint32_t,pixelsPerColumn, const cuuint32_t*,elementStrides, CUtensorMapInterleave,interleave, CUtensorMapSwizzle,swizzle, CUtensorMapL2promotion,l2Promotion, CUtensorMapFloatOOBfill,oobFill);
DEF_FN(CUresult,cuTensorMapReplaceAddress_v12000,cuTensorMapReplaceAddress,12000,0,CUtensorMap*,tensorMap, void*,globalAddress);
DEF_FN(CUresult,cuDeviceCanAccessPeer_v4000,cuDeviceCanAccessPeer,4000,0,int*,canAccessPeer, CUdevice_v1,dev, CUdevice_v1,peerDev);
DEF_FN(CUresult,cuCtxEnablePeerAccess_v4000,cuCtxEnablePeerAccess,4000,0,CUcontext,peerContext, unsigned int,Flags);
DEF_FN(CUresult,cuCtxDisablePeerAccess_v4000,cuCtxDisablePeerAccess,4000,0,CUcontext,peerContext);
DEF_FN(CUresult,cuDeviceGetP2PAttribute_v8000,cuDeviceGetP2PAttribute,8000,0,int*,value, CUdevice_P2PAttribute,attrib, CUdevice_v1,srcDevice, CUdevice_v1,dstDevice);
DEF_FN(CUresult,cuGraphicsUnregisterResource_v3000,cuGraphicsUnregisterResource,3000,0,CUgraphicsResource,resource);
DEF_FN(CUresult,cuGraphicsSubResourceGetMappedArray_v3000,cuGraphicsSubResourceGetMappedArray,3000,0,CUarray*,pArray, CUgraphicsResource,resource, unsigned int,arrayIndex, unsigned int,mipLevel);
DEF_FN(CUresult,cuGraphicsResourceGetMappedMipmappedArray_v5000,cuGraphicsResourceGetMappedMipmappedArray,5000,0,CUmipmappedArray*,pMipmappedArray, CUgraphicsResource,resource);
DEF_FN(CUresult,cuGraphicsResourceGetMappedPointer_v3020,cuGraphicsResourceGetMappedPointer,3020,0,CUdeviceptr_v2*,pDevPtr, size_t*,pSize, CUgraphicsResource,resource);
DEF_FN(CUresult,cuGraphicsResourceSetMapFlags_v6050,cuGraphicsResourceSetMapFlags,6050,0,CUgraphicsResource,resource, unsigned int,flags);
DEF_FN(CUresult,cuGraphicsMapResources_v7000_ptsz,cuGraphicsMapResources,7000,2,unsigned int,count, CUgraphicsResource*,resources, CUstream,hStream);
DEF_FN(CUresult,cuGraphicsUnmapResources_v7000_ptsz,cuGraphicsUnmapResources,7000,2,unsigned int,count, CUgraphicsResource*,resources, CUstream,hStream);
DEF_FN(CUresult,cuGetExportTable_v3000,cuGetExportTable,3000,0,const void**,ppExportTable, const CUuuid*,pExportTableId);
DEF_FN(CUresult,cuFuncGetModule_v11000,cuFuncGetModule,11000,0,CUmodule*,hmod, CUfunction,hfunc);
DEF_FN(CUresult,cuGetProcAddress_v11030,cuGetProcAddress,11030,0,const char*,symbol, void**,pfn, int,driverVersion, cuuint64_t,flags);
DEF_FN(CUresult,cuGetProcAddress_v12000,cuGetProcAddress,12000,0,const char*,symbol, void**,pfn, int,driverVersion, cuuint64_t,flags, CUdriverProcAddressQueryResult*,symbolFound);
// DEF_FN(CUresult,cuMemcpyHtoD_v3020,cuMemcpyHtoD,3020,0,CUdeviceptr_v2,dstDevice, const void*,srcHost, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoH_v3020,cuMemcpyDtoH,3020,0,void*,dstHost, CUdeviceptr_v2,srcDevice, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoD_v3020,cuMemcpyDtoD,3020,0,CUdeviceptr_v2,dstDevice, CUdeviceptr_v2,srcDevice, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyDtoA_v3020,cuMemcpyDtoA,3020,0,CUarray,dstArray, size_t,dstOffset, CUdeviceptr_v2,srcDevice, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoD_v3020,cuMemcpyAtoD,3020,0,CUdeviceptr_v2,dstDevice, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyHtoA_v3020,cuMemcpyHtoA,3020,0,CUarray,dstArray, size_t,dstOffset, const void*,srcHost, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoH_v3020,cuMemcpyAtoH,3020,0,void*,dstHost, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAtoA_v3020,cuMemcpyAtoA,3020,0,CUarray,dstArray, size_t,dstOffset, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyHtoAAsync_v3020,cuMemcpyHtoAAsync,3020,0,CUarray,dstArray, size_t,dstOffset, const void*,srcHost, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyAtoHAsync_v3020,cuMemcpyAtoHAsync,3020,0,void*,dstHost, CUarray,srcArray, size_t,srcOffset, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy2D_v3020,cuMemcpy2D,3020,0,const CUDA_MEMCPY2D_v2*,pCopy);
DEF_FN(CUresult,cuMemcpy2DUnaligned_v3020,cuMemcpy2DUnaligned,3020,0,const CUDA_MEMCPY2D_v2*,pCopy);
DEF_FN(CUresult,cuMemcpy3D_v3020,cuMemcpy3D,3020,0,const CUDA_MEMCPY3D_v2*,pCopy);
DEF_FN(CUresult,cuMemcpyHtoDAsync_v3020,cuMemcpyHtoDAsync,3020,0,CUdeviceptr_v2,dstDevice, const void*,srcHost, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyDtoHAsync_v3020,cuMemcpyDtoHAsync,3020,0,void*,dstHost, CUdeviceptr_v2,srcDevice, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyDtoDAsync_v3020,cuMemcpyDtoDAsync,3020,0,CUdeviceptr_v2,dstDevice, CUdeviceptr_v2,srcDevice, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy2DAsync_v3020,cuMemcpy2DAsync,3020,0,const CUDA_MEMCPY2D_v2*,pCopy, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy3DAsync_v3020,cuMemcpy3DAsync,3020,0,const CUDA_MEMCPY3D_v2*,pCopy, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD8_v3020,cuMemsetD8,3020,0,CUdeviceptr_v2,dstDevice, unsigned char,uc, size_t,N);
DEF_FN(CUresult,cuMemsetD16_v3020,cuMemsetD16,3020,0,CUdeviceptr_v2,dstDevice, unsigned short,us, size_t,N);
DEF_FN(CUresult,cuMemsetD32_v3020,cuMemsetD32,3020,0,CUdeviceptr_v2,dstDevice, unsigned int,ui, size_t,N);
DEF_FN(CUresult,cuMemsetD2D8_v3020,cuMemsetD2D8,3020,0,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned char,uc, size_t,Width, size_t,Height);
DEF_FN(CUresult,cuMemsetD2D16_v3020,cuMemsetD2D16,3020,0,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned short,us, size_t,Width, size_t,Height);
DEF_FN(CUresult,cuMemsetD2D32_v3020,cuMemsetD2D32,3020,0,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned int,ui, size_t,Width, size_t,Height);
DEF_FN(CUresult,cuMemcpy_v4000,cuMemcpy,4000,0,CUdeviceptr_v2,dst, CUdeviceptr_v2,src, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyAsync_v4000,cuMemcpyAsync,4000,0,CUdeviceptr_v2,dst, CUdeviceptr_v2,src, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpyPeer_v4000,cuMemcpyPeer,4000,0,CUdeviceptr_v2,dstDevice, CUcontext,dstContext, CUdeviceptr_v2,srcDevice, CUcontext,srcContext, size_t,ByteCount);
DEF_FN(CUresult,cuMemcpyPeerAsync_v4000,cuMemcpyPeerAsync,4000,0,CUdeviceptr_v2,dstDevice, CUcontext,dstContext, CUdeviceptr_v2,srcDevice, CUcontext,srcContext, size_t,ByteCount, CUstream,hStream);
DEF_FN(CUresult,cuMemcpy3DPeer_v4000,cuMemcpy3DPeer,4000,0,const CUDA_MEMCPY3D_PEER_v1*,pCopy);
DEF_FN(CUresult,cuMemcpy3DPeerAsync_v4000,cuMemcpy3DPeerAsync,4000,0,const CUDA_MEMCPY3D_PEER_v1*,pCopy, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD8Async_v3020,cuMemsetD8Async,3020,0,CUdeviceptr_v2,dstDevice, unsigned char,uc, size_t,N, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD16Async_v3020,cuMemsetD16Async,3020,0,CUdeviceptr_v2,dstDevice, unsigned short,us, size_t,N, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD32Async_v3020,cuMemsetD32Async,3020,0,CUdeviceptr_v2,dstDevice, unsigned int,ui, size_t,N, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D8Async_v3020,cuMemsetD2D8Async,3020,0,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned char,uc, size_t,Width, size_t,Height, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D16Async_v3020,cuMemsetD2D16Async,3020,0,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned short,us, size_t,Width, size_t,Height, CUstream,hStream);
DEF_FN(CUresult,cuMemsetD2D32Async_v3020,cuMemsetD2D32Async,3020,0,CUdeviceptr_v2,dstDevice, size_t,dstPitch, unsigned int,ui, size_t,Width, size_t,Height, CUstream,hStream);
DEF_FN(CUresult,cuStreamGetPriority_v5050,cuStreamGetPriority,5050,0,CUstream,hStream, int*,priority);
DEF_FN(CUresult,cuStreamGetFlags_v5050,cuStreamGetFlags,5050,0,CUstream,hStream, unsigned int*,flags);
DEF_FN(CUresult,cuStreamGetCtx_v9020,cuStreamGetCtx,9020,0,CUstream,hStream, CUcontext*,pctx);
DEF_FN(CUresult,cuStreamWaitEvent_v3020,cuStreamWaitEvent,3020,0,CUstream,hStream, CUevent,hEvent, unsigned int,Flags);
DEF_FN(CUresult,cuStreamAddCallback_v5000,cuStreamAddCallback,5000,0,CUstream,hStream, CUstreamCallback,callback, void*,userData, unsigned int,flags);
DEF_FN(CUresult,cuStreamAttachMemAsync_v6000,cuStreamAttachMemAsync,6000,0,CUstream,hStream, CUdeviceptr_v2,dptr, size_t,length, unsigned int,flags);
DEF_FN(CUresult,cuStreamQuery_v2000,cuStreamQuery,2000,0,CUstream,hStream);
DEF_FN(CUresult,cuStreamSynchronize_v2000,cuStreamSynchronize,2000,0,CUstream,hStream);
DEF_FN(CUresult,cuEventRecord_v2000,cuEventRecord,2000,0,CUevent,hEvent, CUstream,hStream);
DEF_FN(CUresult,cuEventRecordWithFlags_v11010,cuEventRecordWithFlags,11010,0,CUevent,hEvent, CUstream,hStream, unsigned int,flags);
// DEF_FN(CUresult,cuLaunchKernel_v4000,cuLaunchKernel,4000,0,CUfunction,f, unsigned int,gridDimX, unsigned int,gridDimY, unsigned int,gridDimZ, unsigned int,blockDimX, unsigned int,blockDimY, unsigned int,blockDimZ, unsigned int,sharedMemBytes, CUstream,hStream, void**,kernelParams, void**,extra);
DEF_FN(CUresult,cuLaunchKernelEx_v11060,cuLaunchKernelEx,11060,0,const CUlaunchConfig*,config, CUfunction,f, void**,kernelParams, void**,extra);
DEF_FN(CUresult,cuLaunchHostFunc_v10000,cuLaunchHostFunc,10000,0,CUstream,hStream, CUhostFn,fn, void*,userData);
DEF_FN(CUresult,cuGraphicsMapResources_v3000,cuGraphicsMapResources,3000,0,unsigned int,count, CUgraphicsResource*,resources, CUstream,hStream);
DEF_FN(CUresult,cuGraphicsUnmapResources_v3000,cuGraphicsUnmapResources,3000,0,unsigned int,count, CUgraphicsResource*,resources, CUstream,hStream);
DEF_FN(CUresult,cuStreamWriteValue32_v8000,cuStreamWriteValue32,8000,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue32_v8000,cuStreamWaitValue32,8000,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue64_v9000,cuStreamWriteValue64,9000,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue64_v9000,cuStreamWaitValue64,9000,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamBatchMemOp_v8000,cuStreamBatchMemOp,8000,0,CUstream,stream, unsigned int,count, CUstreamBatchMemOpParams*,paramArray, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue32_v11070,cuStreamWriteValue32,11070,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue32_v11070,cuStreamWaitValue32,11070,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint32_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWriteValue64_v11070,cuStreamWriteValue64,11070,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamWaitValue64_v11070,cuStreamWaitValue64,11070,0,CUstream,stream, CUdeviceptr_v2,addr, cuuint64_t,value, unsigned int,flags);
DEF_FN(CUresult,cuStreamBatchMemOp_v11070,cuStreamBatchMemOp,11070,0,CUstream,stream, unsigned int,count, CUstreamBatchMemOpParams*,paramArray, unsigned int,flags);
DEF_FN(CUresult,cuMemPrefetchAsync_v8000,cuMemPrefetchAsync,8000,0,CUdeviceptr_v2,devPtr, size_t,count, CUdevice_v1,dstDevice, CUstream,hStream);
DEF_FN(CUresult,cuMemPrefetchAsync_v12020,cuMemPrefetchAsync,12020,0,CUdeviceptr_v2,devPtr, size_t,count, CUmemLocation_v1,location, unsigned int,flags, CUstream,hStream);
DEF_FN(CUresult,cuLaunchCooperativeKernel_v9000,cuLaunchCooperativeKernel,9000,0,CUfunction,f, unsigned int,gridDimX, unsigned int,gridDimY, unsigned int,gridDimZ, unsigned int,blockDimX, unsigned int,blockDimY, unsigned int,blockDimZ, unsigned int,sharedMemBytes, CUstream,hStream, void**,kernelParams);
DEF_FN(CUresult,cuSignalExternalSemaphoresAsync_v10000,cuSignalExternalSemaphoresAsync,10000,0,const CUexternalSemaphore*,extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_v1*,paramsArray, unsigned int,numExtSems, CUstream,stream);
DEF_FN(CUresult,cuWaitExternalSemaphoresAsync_v10000,cuWaitExternalSemaphoresAsync,10000,0,const CUexternalSemaphore*,extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_v1*,paramsArray, unsigned int,numExtSems, CUstream,stream);
DEF_FN(CUresult,cuStreamBeginCapture_v10010,cuStreamBeginCapture,10010,0,CUstream,hStream, CUstreamCaptureMode,mode);
DEF_FN(CUresult,cuStreamBeginCaptureToGraph_v12030,cuStreamBeginCaptureToGraph,12030,0,CUstream,hStream, CUgraph,hGraph, const CUgraphNode*,dependencies, const CUgraphEdgeData*,dependencyData, size_t,numDependencies, CUstreamCaptureMode,mode);
DEF_FN(CUresult,cuStreamEndCapture_v10000,cuStreamEndCapture,10000,0,CUstream,hStream, CUgraph*,phGraph);
DEF_FN(CUresult,cuStreamIsCapturing_v10000,cuStreamIsCapturing,10000,0,CUstream,hStream, CUstreamCaptureStatus*,captureStatus);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v10010,cuStreamGetCaptureInfo,10010,0,CUstream,hStream, CUstreamCaptureStatus*,captureStatus_out, cuuint64_t*,id_out);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v11030,cuStreamGetCaptureInfo,11030,0,CUstream,hStream, CUstreamCaptureStatus*,captureStatus_out, cuuint64_t*,id_out, CUgraph*,graph_out, const CUgraphNode**,dependencies_out, size_t*,numDependencies_out);
DEF_FN(CUresult,cuStreamGetCaptureInfo_v12030,cuStreamGetCaptureInfo,12030,0,CUstream,hStream, CUstreamCaptureStatus*,captureStatus_out, cuuint64_t*,id_out, CUgraph*,graph_out, const CUgraphNode**,dependencies_out, const CUgraphEdgeData**,edgeData_out, size_t*,numDependencies_out);
DEF_FN(CUresult,cuStreamUpdateCaptureDependencies_v11030,cuStreamUpdateCaptureDependencies,11030,0,CUstream,hStream, CUgraphNode*,dependencies, size_t,numDependencies, unsigned int,flags);
DEF_FN(CUresult,cuStreamUpdateCaptureDependencies_v12030,cuStreamUpdateCaptureDependencies,12030,0,CUstream,hStream, CUgraphNode*,dependencies, const CUgraphEdgeData*,dependencyData, size_t,numDependencies, unsigned int,flags);
DEF_FN(CUresult,cuGraphInstantiateWithParams_v12000,cuGraphInstantiateWithParams,12000,0,CUgraphExec*,phGraphExec, CUgraph,hGraph, CUDA_GRAPH_INSTANTIATE_PARAMS*,instantiateParams);
DEF_FN(CUresult,cuGraphUpload_v11010,cuGraphUpload,11010,0,CUgraphExec,hGraph, CUstream,hStream);
DEF_FN(CUresult,cuGraphLaunch_v10000,cuGraphLaunch,10000,0,CUgraphExec,hGraph, CUstream,hStream);
DEF_FN(CUresult,cuStreamCopyAttributes_v11000,cuStreamCopyAttributes,11000,0,CUstream,dstStream, CUstream,srcStream);
DEF_FN(CUresult,cuStreamGetAttribute_v11000,cuStreamGetAttribute,11000,0,CUstream,hStream, CUstreamAttrID,attr, CUstreamAttrValue_v1*,value);
DEF_FN(CUresult,cuStreamSetAttribute_v11000,cuStreamSetAttribute,11000,0,CUstream,hStream, CUstreamAttrID,attr, const CUstreamAttrValue_v1*,param);
DEF_FN(CUresult,cuMemMapArrayAsync_v11010,cuMemMapArrayAsync,11010,0,CUarrayMapInfo_v1*,mapInfoList, unsigned int,count, CUstream,hStream);
DEF_FN(CUresult,cuMemFreeAsync_v11020,cuMemFreeAsync,11020,0,CUdeviceptr_v2,dptr, CUstream,hStream);
DEF_FN(CUresult,cuMemAllocAsync_v11020,cuMemAllocAsync,11020,0,CUdeviceptr_v2*,dptr, size_t,bytesize, CUstream,hStream);
DEF_FN(CUresult,cuMemAllocFromPoolAsync_v11020,cuMemAllocFromPoolAsync,11020,0,CUdeviceptr_v2*,dptr, size_t,bytesize, CUmemoryPool,pool, CUstream,hStream);
DEF_FN(CUresult,cuFlushGPUDirectRDMAWrites_v11030,cuFlushGPUDirectRDMAWrites,11030,0,CUflushGPUDirectRDMAWritesTarget,target, CUflushGPUDirectRDMAWritesScope,scope);
DEF_FN(CUresult,cuUserObjectCreate_v11030,cuUserObjectCreate,11030,0,CUuserObject*,object_out, void*,ptr, CUhostFn,destroy, unsigned int,initialRefcount, unsigned int,flags);
DEF_FN(CUresult,cuUserObjectRetain_v11030,cuUserObjectRetain,11030,0,CUuserObject,object, unsigned int,count);
DEF_FN(CUresult,cuUserObjectRelease_v11030,cuUserObjectRelease,11030,0,CUuserObject,object, unsigned int,count);
DEF_FN(CUresult,cuGraphRetainUserObject_v11030,cuGraphRetainUserObject,11030,0,CUgraph,graph, CUuserObject,object, unsigned int,count, unsigned int,flags);
DEF_FN(CUresult,cuGraphReleaseUserObject_v11030,cuGraphReleaseUserObject,11030,0,CUgraph,graph, CUuserObject,object, unsigned int,count);
// DEF_FN(CUresult,cuModuleGetLoadingMode_v11070,cuModuleGetLoadingMode,11070,0,CUmoduleLoadingMode*,mode);
DEF_FN(CUresult,cuMemGetHandleForAddressRange_v11070,cuMemGetHandleForAddressRange,11070,0,void*,handle, CUdeviceptr,dptr, size_t,size, CUmemRangeHandleType,handleType, unsigned long long,flags);
// DEF_FN(CUresult,cuLibraryLoadData_v12000,cuLibraryLoadData,12000,0,CUlibrary*,library, const void*,code, CUjit_option*,jitOptions, void**,jitOptionsValues, unsigned int,numJitOptions, CUlibraryOption*,libraryOptions, void**,libraryOptionValues, unsigned int,numLibraryOptions);
DEF_FN(CUresult,cuLibraryLoadFromFile_v12000,cuLibraryLoadFromFile,12000,0,CUlibrary*,library, const char*,fileName, CUjit_option*,jitOptions, void**,jitOptionsValues, unsigned int,numJitOptions, CUlibraryOption*,libraryOptions, void**,libraryOptionValues, unsigned int,numLibraryOptions);
DEF_FN(CUresult,cuLibraryUnload_v12000,cuLibraryUnload,12000,0,CUlibrary,library);
DEF_FN(CUresult,cuLibraryGetKernel_v12000,cuLibraryGetKernel,12000,0,CUkernel*,pKernel, CUlibrary,library, const char*,name);
// DEF_FN(CUresult,cuLibraryGetModule_v12000,cuLibraryGetModule,12000,0,CUmodule*,pMod, CUlibrary,library);
DEF_FN(CUresult,cuLibraryGetKernelCount,cuLibraryGetKernelCount,0,0,unsigned int*,count, CUlibrary,lib);
DEF_FN(CUresult,cuLibraryEnumerateKernels,cuLibraryEnumerateKernels,0,0,CUkernel*,kernels, unsigned int,numKernels, CUlibrary,lib);
DEF_FN(CUresult,cuKernelGetFunction_v12000,cuKernelGetFunction,12000,0,CUfunction*,pFunc, CUkernel,kernel);
DEF_FN(CUresult,cuLibraryGetGlobal_v12000,cuLibraryGetGlobal,12000,0,CUdeviceptr*,dptr, size_t*,bytes, CUlibrary,library, const char*,name);
DEF_FN(CUresult,cuLibraryGetManaged_v12000,cuLibraryGetManaged,12000,0,CUdeviceptr*,dptr, size_t*,bytes, CUlibrary,library, const char*,name);
DEF_FN(CUresult,cuKernelGetAttribute_v12000,cuKernelGetAttribute,12000,0,int*,pi, CUfunction_attribute,attrib, CUkernel,kernel, CUdevice,dev);
DEF_FN(CUresult,cuKernelSetAttribute_v12000,cuKernelSetAttribute,12000,0,CUfunction_attribute,attrib, int,val, CUkernel,kernel, CUdevice,dev);
DEF_FN(CUresult,cuKernelSetCacheConfig_v12000,cuKernelSetCacheConfig,12000,0,CUkernel,kernel, CUfunc_cache,config, CUdevice,dev);
DEF_FN(CUresult,cuKernelGetName_v12030,cuKernelGetName,12030,0,const char**,name, CUkernel,hfunc);
DEF_FN(CUresult,cuKernelGetParamInfo_v12040,cuKernelGetParamInfo,12040,0,CUkernel,kernel, size_t,paramIndex, size_t*,paramOffset, size_t*,paramSize);
DEF_FN(CUresult,cuLibraryGetUnifiedFunction_v12000,cuLibraryGetUnifiedFunction,12000,0,void**,fptr, CUlibrary,library, const char*,symbol);
DEF_FN(CUresult,cuCoredumpGetAttribute_v12010,cuCoredumpGetAttribute,12010,0,CUcoredumpSettings,get, void*,value, size_t*,size);
DEF_FN(CUresult,cuCoredumpGetAttributeGlobal_v12010,cuCoredumpGetAttributeGlobal,12010,0,CUcoredumpSettings,get, void*,value, size_t*,size);
DEF_FN(CUresult,cuCoredumpSetAttribute_v12010,cuCoredumpSetAttribute,12010,0,CUcoredumpSettings,set, void*,value, size_t*,size);
DEF_FN(CUresult,cuCoredumpSetAttributeGlobal_v12010,cuCoredumpSetAttributeGlobal,12010,0,CUcoredumpSettings,set, void*,value, size_t*,size);
DEF_FN(CUresult,cuDeviceRegisterAsyncNotification_v12040,cuDeviceRegisterAsyncNotification,12040,0,CUdevice,device, CUasyncCallback,callbackFunc, void*,userData, CUasyncCallbackHandle*,callback);
DEF_FN(CUresult,cuDeviceUnregisterAsyncNotification_v12040,cuDeviceUnregisterAsyncNotification,12040,0,CUdevice,device, CUasyncCallbackHandle,callback);
DEF_FN(CUresult,cuGreenCtxCreate_v12040,cuGreenCtxCreate,12040,0,CUgreenCtx*,phCtx, CUdevResourceDesc,desc, CUdevice,dev, unsigned int,flags);
DEF_FN(CUresult,cuGreenCtxDestroy_v12040,cuGreenCtxDestroy,12040,0,CUgreenCtx,hCtx);
DEF_FN(CUresult,cuDeviceGetDevResource_v12040,cuDeviceGetDevResource,12040,0,CUdevice,dev, CUdevResource*,result, CUdevResourceType,type);
DEF_FN(CUresult,cuCtxGetDevResource_v12040,cuCtxGetDevResource,12040,0,CUcontext,hCtx, CUdevResource*,result, CUdevResourceType,type);
DEF_FN(CUresult,cuGreenCtxGetDevResource_v12040,cuGreenCtxGetDevResource,12040,0,CUgreenCtx,hCtx, CUdevResource*,result, CUdevResourceType,type);
DEF_FN(CUresult,cuGreenCtxRecordEvent_v12040,cuGreenCtxRecordEvent,12040,0,CUgreenCtx,hCtx, CUevent,hEvent);
DEF_FN(CUresult,cuGreenCtxWaitEvent_v12040,cuGreenCtxWaitEvent,12040,0,CUgreenCtx,hCtx, CUevent,hEvent);
DEF_FN(CUresult,cuDevResourceGenerateDesc_v12040,cuDevResourceGenerateDesc,12040,0,CUdevResourceDesc*,phDesc, CUdevResource*,resources, unsigned int,nbResources);
DEF_FN(CUresult,cuDevSmResourceSplitByCount_v12040,cuDevSmResourceSplitByCount,12040,0,CUdevResource*,result, unsigned int*,nbGroups, const CUdevResource*,input, CUdevResource*,remaining, unsigned int,useFlags, unsigned int,minCount);
DEF_FN(CUresult,cuStreamGetGreenCtx_v12040,cuStreamGetGreenCtx,12040,0,CUstream,hStream, CUgreenCtx*,phCtx);
DEF_FN(CUresult,cuCtxFromGreenCtx_v12040,cuCtxFromGreenCtx,12040,0,CUcontext*,pContext, CUgreenCtx,hCtx);
// #if defined(__CUDA_API_VERSION_INTERNAL)
	DEF_FN(CUresult,cuMemHostRegister_v4000,cuMemHostRegister,4000,0,void*,p, size_t,bytesize, unsigned int,Flags);
	DEF_FN(CUresult,cuGraphicsResourceSetMapFlags_v3000,cuGraphicsResourceSetMapFlags,3000,0,CUgraphicsResource,resource, unsigned int,flags);
	DEF_FN(CUresult,cuLinkCreate_v5050,cuLinkCreate,5050,0,unsigned int,numOptions, CUjit_option*,options, void**,optionValues, CUlinkState*,stateOut);
	DEF_FN(CUresult,cuLinkAddData_v5050,cuLinkAddData,5050,0,CUlinkState,state, CUjitInputType,type, void*,data, size_t,size, const char*,name, unsigned int,numOptions, CUjit_option*,options, void**,optionValues);
	DEF_FN(CUresult,cuLinkAddFile_v5050,cuLinkAddFile,5050,0,CUlinkState,state, CUjitInputType,type, const char*,path, unsigned int,numOptions, CUjit_option*,options, void**,optionValues);
	DEF_FN(CUresult,cuTexRefSetAddress2D_v3020,cuTexRefSetAddress2D,3020,0,CUtexref,hTexRef, const CUDA_ARRAY_DESCRIPTOR_v2*,desc, CUdeviceptr_v2,dptr, size_t,Pitch);
	DEF_FN(CUresult,cuDeviceTotalMem_v2000,cuDeviceTotalMem,2000,0,unsigned int*,bytes, CUdevice_v1,dev);
	DEF_FN(CUresult,cuCtxCreate_v2000,cuCtxCreate,2000,0,CUcontext*,pctx, unsigned int,flags, CUdevice_v1,dev);
	DEF_FN(CUresult,cuModuleGetGlobal_v2000,cuModuleGetGlobal,2000,0,CUdeviceptr_v1*,dptr, unsigned int*,bytes, CUmodule,hmod, const char*,name);
	DEF_FN(CUresult,cuMemGetInfo_v2000,cuMemGetInfo,2000,0,unsigned int*,free, unsigned int*,total);
	DEF_FN(CUresult,cuMemAlloc_v2000,cuMemAlloc,2000,0,CUdeviceptr_v1*,dptr, unsigned int,bytesize);
	DEF_FN(CUresult,cuMemAllocPitch_v2000,cuMemAllocPitch,2000,0,CUdeviceptr_v1*,dptr, unsigned int*,pPitch, unsigned int,WidthInBytes, unsigned int,Height, unsigned int,ElementSizeBytes);
	DEF_FN(CUresult,cuMemFree_v2000,cuMemFree,2000,0,CUdeviceptr_v1,dptr);
	DEF_FN(CUresult,cuMemGetAddressRange_v2000,cuMemGetAddressRange,2000,0,CUdeviceptr_v1*,pbase, unsigned int*,psize, CUdeviceptr_v1,dptr);
	DEF_FN(CUresult,cuMemAllocHost_v2000,cuMemAllocHost,2000,0,void**,pp, unsigned int,bytesize);
	DEF_FN(CUresult,cuMemHostGetDevicePointer_v2020,cuMemHostGetDevicePointer,2020,0,CUdeviceptr_v1*,pdptr, void*,p, unsigned int,Flags);
	DEF_FN(CUresult,cuMemcpyHtoD_v2000,cuMemcpyHtoD,2000,0,CUdeviceptr_v1,dstDevice, const void*,srcHost, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyDtoH_v2000,cuMemcpyDtoH,2000,0,void*,dstHost, CUdeviceptr_v1,srcDevice, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyDtoD_v2000,cuMemcpyDtoD,2000,0,CUdeviceptr_v1,dstDevice, CUdeviceptr_v1,srcDevice, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyDtoA_v2000,cuMemcpyDtoA,2000,0,CUarray,dstArray, unsigned int,dstOffset, CUdeviceptr_v1,srcDevice, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyAtoD_v2000,cuMemcpyAtoD,2000,0,CUdeviceptr_v1,dstDevice, CUarray,srcArray, unsigned int,srcOffset, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyHtoA_v2000,cuMemcpyHtoA,2000,0,CUarray,dstArray, unsigned int,dstOffset, const void*,srcHost, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyAtoH_v2000,cuMemcpyAtoH,2000,0,void*,dstHost, CUarray,srcArray, unsigned int,srcOffset, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyAtoA_v2000,cuMemcpyAtoA,2000,0,CUarray,dstArray, unsigned int,dstOffset, CUarray,srcArray, unsigned int,srcOffset, unsigned int,ByteCount);
	DEF_FN(CUresult,cuMemcpyHtoAAsync_v2000,cuMemcpyHtoAAsync,2000,0,CUarray,dstArray, unsigned int,dstOffset, const void*,srcHost, unsigned int,ByteCount, CUstream,hStream);
	DEF_FN(CUresult,cuMemcpyAtoHAsync_v2000,cuMemcpyAtoHAsync,2000,0,void*,dstHost, CUarray,srcArray, unsigned int,srcOffset, unsigned int,ByteCount, CUstream,hStream);
	DEF_FN(CUresult,cuMemcpy2D_v2000,cuMemcpy2D,2000,0,const CUDA_MEMCPY2D_v1*,pCopy);
	DEF_FN(CUresult,cuMemcpy2DUnaligned_v2000,cuMemcpy2DUnaligned,2000,0,const CUDA_MEMCPY2D_v1*,pCopy);
	DEF_FN(CUresult,cuMemcpy3D_v2000,cuMemcpy3D,2000,0,const CUDA_MEMCPY3D_v1*,pCopy);
	DEF_FN(CUresult,cuMemcpyHtoDAsync_v2000,cuMemcpyHtoDAsync,2000,0,CUdeviceptr_v1,dstDevice, const void*,srcHost, unsigned int,ByteCount, CUstream,hStream);
	DEF_FN(CUresult,cuMemcpyDtoHAsync_v2000,cuMemcpyDtoHAsync,2000,0,void*,dstHost, CUdeviceptr_v1,srcDevice, unsigned int,ByteCount, CUstream,hStream);
	DEF_FN(CUresult,cuMemcpyDtoDAsync_v3000,cuMemcpyDtoDAsync,3000,0,CUdeviceptr_v1,dstDevice, CUdeviceptr_v1,srcDevice, unsigned int,ByteCount, CUstream,hStream);
	DEF_FN(CUresult,cuMemcpy2DAsync_v2000,cuMemcpy2DAsync,2000,0,const CUDA_MEMCPY2D_v1*,pCopy, CUstream,hStream);
	DEF_FN(CUresult,cuMemcpy3DAsync_v2000,cuMemcpy3DAsync,2000,0,const CUDA_MEMCPY3D_v1*,pCopy, CUstream,hStream);
	DEF_FN(CUresult,cuMemsetD8_v2000,cuMemsetD8,2000,0,CUdeviceptr_v1,dstDevice, unsigned char,uc, unsigned int,N);
	DEF_FN(CUresult,cuMemsetD16_v2000,cuMemsetD16,2000,0,CUdeviceptr_v1,dstDevice, unsigned short,us, unsigned int,N);
	DEF_FN(CUresult,cuMemsetD32_v2000,cuMemsetD32,2000,0,CUdeviceptr_v1,dstDevice, unsigned int,ui, unsigned int,N);
	DEF_FN(CUresult,cuMemsetD2D8_v2000,cuMemsetD2D8,2000,0,CUdeviceptr_v1,dstDevice, unsigned int,dstPitch, unsigned char,uc, unsigned int,Width, unsigned int,Height);
	DEF_FN(CUresult,cuMemsetD2D16_v2000,cuMemsetD2D16,2000,0,CUdeviceptr_v1,dstDevice, unsigned int,dstPitch, unsigned short,us, unsigned int,Width, unsigned int,Height);
	DEF_FN(CUresult,cuMemsetD2D32_v2000,cuMemsetD2D32,2000,0,CUdeviceptr_v1,dstDevice, unsigned int,dstPitch, unsigned int,ui, unsigned int,Width, unsigned int,Height);
	DEF_FN(CUresult,cuArrayCreate_v2000,cuArrayCreate,2000,0,CUarray*,pHandle, const CUDA_ARRAY_DESCRIPTOR_v1*,pAllocateArray);
	DEF_FN(CUresult,cuArrayGetDescriptor_v2000,cuArrayGetDescriptor,2000,0,CUDA_ARRAY_DESCRIPTOR_v1*,pArrayDescriptor, CUarray,hArray);
	DEF_FN(CUresult,cuArray3DCreate_v2000,cuArray3DCreate,2000,0,CUarray*,pHandle, const CUDA_ARRAY3D_DESCRIPTOR_v1*,pAllocateArray);
	DEF_FN(CUresult,cuArray3DGetDescriptor_v2000,cuArray3DGetDescriptor,2000,0,CUDA_ARRAY3D_DESCRIPTOR_v1*,pArrayDescriptor, CUarray,hArray);
	DEF_FN(CUresult,cuTexRefSetAddress_v2000,cuTexRefSetAddress,2000,0,unsigned int*,ByteOffset, CUtexref,hTexRef, CUdeviceptr_v1,dptr, unsigned int,bytes);
	DEF_FN(CUresult,cuTexRefSetAddress2D_v2020,cuTexRefSetAddress2D,2020,0,CUtexref,hTexRef, const CUDA_ARRAY_DESCRIPTOR_v1*,desc, CUdeviceptr_v1,dptr, unsigned int,Pitch);
	DEF_FN(CUresult,cuTexRefGetAddress_v2000,cuTexRefGetAddress,2000,0,CUdeviceptr_v1*,pdptr, CUtexref,hTexRef);
	DEF_FN(CUresult,cuGraphicsResourceGetMappedPointer_v3000,cuGraphicsResourceGetMappedPointer,3000,0,CUdeviceptr_v1*,pDevPtr, unsigned int*,pSize, CUgraphicsResource,resource);
	DEF_FN(CUresult,cuCtxDestroy_v2000,cuCtxDestroy,2000,0,CUcontext,ctx);
	DEF_FN(CUresult,cuCtxPopCurrent_v2000,cuCtxPopCurrent,2000,0,CUcontext*,pctx);
	DEF_FN(CUresult,cuCtxPushCurrent_v2000,cuCtxPushCurrent,2000,0,CUcontext,ctx);
	DEF_FN(CUresult,cuStreamDestroy_v2000,cuStreamDestroy,2000,0,CUstream,hStream);
	DEF_FN(CUresult,cuEventDestroy_v2000,cuEventDestroy,2000,0,CUevent,hEvent);
	DEF_FN(CUresult,cuDevicePrimaryCtxRelease_v7000,cuDevicePrimaryCtxRelease,7000,0,CUdevice_v1,dev);
	DEF_FN(CUresult,cuDevicePrimaryCtxReset_v7000,cuDevicePrimaryCtxReset,7000,0,CUdevice_v1,dev);
	DEF_FN(CUresult,cuDevicePrimaryCtxSetFlags_v7000,cuDevicePrimaryCtxSetFlags,7000,0,CUdevice_v1,dev, unsigned int,flags);
	DEF_FN(CUresult,cuStreamBeginCapture_v10000,cuStreamBeginCapture,10000,0,CUstream,hStream);
	DEF_FN(CUresult,cuStreamBeginCapture_v10000_ptsz,cuStreamBeginCapture,10000,2,CUstream,hStream);
	DEF_FN(CUresult,cuIpcOpenMemHandle_v4010,cuIpcOpenMemHandle,4010,0,CUdeviceptr_v2*,pdptr, CUipcMemHandle_v1,handle, unsigned int,Flags);
	DEF_FN(CUresult,cuGraphInstantiate_v10000,cuGraphInstantiate,10000,0,CUgraphExec*,phGraphExec, CUgraph,hGraph, CUgraphNode*,phErrorNode, char*,logBuffer, size_t,bufferSize);
	DEF_FN(CUresult,cuGraphInstantiate_v11000,cuGraphInstantiate,11000,0,CUgraphExec*,phGraphExec, CUgraph,hGraph, CUgraphNode*,phErrorNode, char*,logBuffer, size_t,bufferSize);
// #endif
std::unordered_map<std::string,CuDriverFunction> cuDriverFunctionTable {
	{"cuGetErrorString_v6000",CuDriverFunction("cuGetErrorString",6000,0,reinterpret_cast<void*>(&cuGetErrorString_v6000)) },
	{"cuGetErrorName_v6000",CuDriverFunction("cuGetErrorName",6000,0,reinterpret_cast<void*>(&cuGetErrorName_v6000)) },
	{"cuInit_v2000",CuDriverFunction("cuInit",2000,0,reinterpret_cast<void*>(&cuInit_v2000)) },
	{"cuDriverGetVersion_v2020",CuDriverFunction("cuDriverGetVersion",2020,0,reinterpret_cast<void*>(&cuDriverGetVersion_v2020)) },
	{"cuDeviceGet_v2000",CuDriverFunction("cuDeviceGet",2000,0,reinterpret_cast<void*>(&cuDeviceGet_v2000)) },
	{"cuDeviceGetCount_v2000",CuDriverFunction("cuDeviceGetCount",2000,0,reinterpret_cast<void*>(&cuDeviceGetCount_v2000)) },
	{"cuDeviceGetName_v2000",CuDriverFunction("cuDeviceGetName",2000,0,reinterpret_cast<void*>(&cuDeviceGetName_v2000)) },
	{"cuDeviceGetUuid_v9020",CuDriverFunction("cuDeviceGetUuid",9020,0,reinterpret_cast<void*>(&cuDeviceGetUuid_v9020)) },
	{"cuDeviceGetUuid_v11040",CuDriverFunction("cuDeviceGetUuid",11040,0,reinterpret_cast<void*>(&cuDeviceGetUuid_v11040)) },
	{"cuDeviceGetLuid_v10000",CuDriverFunction("cuDeviceGetLuid",10000,0,reinterpret_cast<void*>(&cuDeviceGetLuid_v10000)) },
	{"cuDeviceTotalMem_v3020",CuDriverFunction("cuDeviceTotalMem",3020,0,reinterpret_cast<void*>(&cuDeviceTotalMem_v3020)) },
	{"cuDeviceGetTexture1DLinearMaxWidth_v11010",CuDriverFunction("cuDeviceGetTexture1DLinearMaxWidth",11010,0,reinterpret_cast<void*>(&cuDeviceGetTexture1DLinearMaxWidth_v11010)) },
	{"cuDeviceGetAttribute_v2000",CuDriverFunction("cuDeviceGetAttribute",2000,0,reinterpret_cast<void*>(&cuDeviceGetAttribute_v2000)) },
	{"cuDeviceGetNvSciSyncAttributes_v10020",CuDriverFunction("cuDeviceGetNvSciSyncAttributes",10020,0,reinterpret_cast<void*>(&cuDeviceGetNvSciSyncAttributes_v10020)) },
	{"cuDeviceSetMemPool_v11020",CuDriverFunction("cuDeviceSetMemPool",11020,0,reinterpret_cast<void*>(&cuDeviceSetMemPool_v11020)) },
	{"cuDeviceGetMemPool_v11020",CuDriverFunction("cuDeviceGetMemPool",11020,0,reinterpret_cast<void*>(&cuDeviceGetMemPool_v11020)) },
	{"cuDeviceGetDefaultMemPool_v11020",CuDriverFunction("cuDeviceGetDefaultMemPool",11020,0,reinterpret_cast<void*>(&cuDeviceGetDefaultMemPool_v11020)) },
	{"cuDeviceGetProperties_v2000",CuDriverFunction("cuDeviceGetProperties",2000,0,reinterpret_cast<void*>(&cuDeviceGetProperties_v2000)) },
	{"cuDeviceComputeCapability_v2000",CuDriverFunction("cuDeviceComputeCapability",2000,0,reinterpret_cast<void*>(&cuDeviceComputeCapability_v2000)) },
	{"cuDevicePrimaryCtxRetain_v7000",CuDriverFunction("cuDevicePrimaryCtxRetain",7000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxRetain_v7000)) },
	{"cuDevicePrimaryCtxRelease_v11000",CuDriverFunction("cuDevicePrimaryCtxRelease",11000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxRelease_v11000)) },
	{"cuDevicePrimaryCtxSetFlags_v11000",CuDriverFunction("cuDevicePrimaryCtxSetFlags",11000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxSetFlags_v11000)) },
	{"cuDevicePrimaryCtxGetState_v7000",CuDriverFunction("cuDevicePrimaryCtxGetState",7000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxGetState_v7000)) },
	{"cuDevicePrimaryCtxReset_v11000",CuDriverFunction("cuDevicePrimaryCtxReset",11000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxReset_v11000)) },
	{"cuDeviceGetExecAffinitySupport_v11040",CuDriverFunction("cuDeviceGetExecAffinitySupport",11040,0,reinterpret_cast<void*>(&cuDeviceGetExecAffinitySupport_v11040)) },
	{"cuCtxCreate_v3020",CuDriverFunction("cuCtxCreate",3020,0,reinterpret_cast<void*>(&cuCtxCreate_v3020)) },
	{"cuCtxCreate_v11040",CuDriverFunction("cuCtxCreate",11040,0,reinterpret_cast<void*>(&cuCtxCreate_v11040)) },
	{"cuCtxGetId_v12000",CuDriverFunction("cuCtxGetId",12000,0,reinterpret_cast<void*>(&cuCtxGetId_v12000)) },
	{"cuCtxDestroy_v4000",CuDriverFunction("cuCtxDestroy",4000,0,reinterpret_cast<void*>(&cuCtxDestroy_v4000)) },
	{"cuCtxPushCurrent_v4000",CuDriverFunction("cuCtxPushCurrent",4000,0,reinterpret_cast<void*>(&cuCtxPushCurrent_v4000)) },
	{"cuCtxPopCurrent_v4000",CuDriverFunction("cuCtxPopCurrent",4000,0,reinterpret_cast<void*>(&cuCtxPopCurrent_v4000)) },
	{"cuCtxSetCurrent_v4000",CuDriverFunction("cuCtxSetCurrent",4000,0,reinterpret_cast<void*>(&cuCtxSetCurrent_v4000)) },
	{"cuCtxGetCurrent_v4000",CuDriverFunction("cuCtxGetCurrent",4000,0,reinterpret_cast<void*>(&cuCtxGetCurrent_v4000)) },
	{"cuCtxGetDevice_v2000",CuDriverFunction("cuCtxGetDevice",2000,0,reinterpret_cast<void*>(&cuCtxGetDevice_v2000)) },
	{"cuCtxGetFlags_v7000",CuDriverFunction("cuCtxGetFlags",7000,0,reinterpret_cast<void*>(&cuCtxGetFlags_v7000)) },
	{"cuCtxSetFlags_v12010",CuDriverFunction("cuCtxSetFlags",12010,0,reinterpret_cast<void*>(&cuCtxSetFlags_v12010)) },
	{"cuCtxSynchronize_v2000",CuDriverFunction("cuCtxSynchronize",2000,0,reinterpret_cast<void*>(&cuCtxSynchronize_v2000)) },
	{"cuCtxSetLimit_v3010",CuDriverFunction("cuCtxSetLimit",3010,0,reinterpret_cast<void*>(&cuCtxSetLimit_v3010)) },
	{"cuCtxGetLimit_v3010",CuDriverFunction("cuCtxGetLimit",3010,0,reinterpret_cast<void*>(&cuCtxGetLimit_v3010)) },
	{"cuCtxGetCacheConfig_v3020",CuDriverFunction("cuCtxGetCacheConfig",3020,0,reinterpret_cast<void*>(&cuCtxGetCacheConfig_v3020)) },
	{"cuCtxSetCacheConfig_v3020",CuDriverFunction("cuCtxSetCacheConfig",3020,0,reinterpret_cast<void*>(&cuCtxSetCacheConfig_v3020)) },
	{"cuCtxGetSharedMemConfig_v4020",CuDriverFunction("cuCtxGetSharedMemConfig",4020,0,reinterpret_cast<void*>(&cuCtxGetSharedMemConfig_v4020)) },
	{"cuCtxSetSharedMemConfig_v4020",CuDriverFunction("cuCtxSetSharedMemConfig",4020,0,reinterpret_cast<void*>(&cuCtxSetSharedMemConfig_v4020)) },
	{"cuCtxGetApiVersion_v3020",CuDriverFunction("cuCtxGetApiVersion",3020,0,reinterpret_cast<void*>(&cuCtxGetApiVersion_v3020)) },
	{"cuCtxGetStreamPriorityRange_v5050",CuDriverFunction("cuCtxGetStreamPriorityRange",5050,0,reinterpret_cast<void*>(&cuCtxGetStreamPriorityRange_v5050)) },
	{"cuCtxResetPersistingL2Cache_v11000",CuDriverFunction("cuCtxResetPersistingL2Cache",11000,0,reinterpret_cast<void*>(&cuCtxResetPersistingL2Cache_v11000)) },
	{"cuCtxAttach_v2000",CuDriverFunction("cuCtxAttach",2000,0,reinterpret_cast<void*>(&cuCtxAttach_v2000)) },
	{"cuCtxDetach_v2000",CuDriverFunction("cuCtxDetach",2000,0,reinterpret_cast<void*>(&cuCtxDetach_v2000)) },
	{"cuCtxGetExecAffinity_v11040",CuDriverFunction("cuCtxGetExecAffinity",11040,0,reinterpret_cast<void*>(&cuCtxGetExecAffinity_v11040)) },
	{"cuModuleLoad_v2000",CuDriverFunction("cuModuleLoad",2000,0,reinterpret_cast<void*>(&cuModuleLoad_v2000)) },
	{"cuModuleLoadData_v2000",CuDriverFunction("cuModuleLoadData",2000,0,reinterpret_cast<void*>(&cuModuleLoadData_v2000)) },
	{"cuModuleLoadDataEx_v2010",CuDriverFunction("cuModuleLoadDataEx",2010,0,reinterpret_cast<void*>(&cuModuleLoadDataEx_v2010)) },
	{"cuModuleLoadFatBinary_v2000",CuDriverFunction("cuModuleLoadFatBinary",2000,0,reinterpret_cast<void*>(&cuModuleLoadFatBinary_v2000)) },
	{"cuModuleUnload_v2000",CuDriverFunction("cuModuleUnload",2000,0,reinterpret_cast<void*>(&cuModuleUnload_v2000)) },
	{"cuModuleGetFunction_v2000",CuDriverFunction("cuModuleGetFunction",2000,0,reinterpret_cast<void*>(&cuModuleGetFunction_v2000)) },
	{"cuModuleGetGlobal_v3020",CuDriverFunction("cuModuleGetGlobal",3020,0,reinterpret_cast<void*>(&cuModuleGetGlobal_v3020)) },
	{"cuModuleGetTexRef_v2000",CuDriverFunction("cuModuleGetTexRef",2000,0,reinterpret_cast<void*>(&cuModuleGetTexRef_v2000)) },
	{"cuModuleGetSurfRef_v3000",CuDriverFunction("cuModuleGetSurfRef",3000,0,reinterpret_cast<void*>(&cuModuleGetSurfRef_v3000)) },
	{"cuModuleGetFunctionCount",CuDriverFunction("cuModuleGetFunctionCount",0,0,reinterpret_cast<void*>(&cuModuleGetFunctionCount)) },
	{"cuModuleEnumerateFunctions",CuDriverFunction("cuModuleEnumerateFunctions",0,0,reinterpret_cast<void*>(&cuModuleEnumerateFunctions)) },
	{"cuLinkCreate_v6050",CuDriverFunction("cuLinkCreate",6050,0,reinterpret_cast<void*>(&cuLinkCreate_v6050)) },
	{"cuLinkAddData_v6050",CuDriverFunction("cuLinkAddData",6050,0,reinterpret_cast<void*>(&cuLinkAddData_v6050)) },
	{"cuLinkAddFile_v6050",CuDriverFunction("cuLinkAddFile",6050,0,reinterpret_cast<void*>(&cuLinkAddFile_v6050)) },
	{"cuLinkComplete_v5050",CuDriverFunction("cuLinkComplete",5050,0,reinterpret_cast<void*>(&cuLinkComplete_v5050)) },
	{"cuLinkDestroy_v5050",CuDriverFunction("cuLinkDestroy",5050,0,reinterpret_cast<void*>(&cuLinkDestroy_v5050)) },
	{"cuMemGetInfo_v3020",CuDriverFunction("cuMemGetInfo",3020,0,reinterpret_cast<void*>(&cuMemGetInfo_v3020)) },
	{"cuMemAlloc_v3020",CuDriverFunction("cuMemAlloc",3020,0,reinterpret_cast<void*>(&cuMemAlloc_v3020)) },
	{"cuMemAllocPitch_v3020",CuDriverFunction("cuMemAllocPitch",3020,0,reinterpret_cast<void*>(&cuMemAllocPitch_v3020)) },
	{"cuMemFree_v3020",CuDriverFunction("cuMemFree",3020,0,reinterpret_cast<void*>(&cuMemFree_v3020)) },
	{"cuMemGetAddressRange_v3020",CuDriverFunction("cuMemGetAddressRange",3020,0,reinterpret_cast<void*>(&cuMemGetAddressRange_v3020)) },
	{"cuMemAllocHost_v3020",CuDriverFunction("cuMemAllocHost",3020,0,reinterpret_cast<void*>(&cuMemAllocHost_v3020)) },
	{"cuMemFreeHost_v2000",CuDriverFunction("cuMemFreeHost",2000,0,reinterpret_cast<void*>(&cuMemFreeHost_v2000)) },
	{"cuMemHostAlloc_v2020",CuDriverFunction("cuMemHostAlloc",2020,0,reinterpret_cast<void*>(&cuMemHostAlloc_v2020)) },
	{"cuMemHostGetDevicePointer_v3020",CuDriverFunction("cuMemHostGetDevicePointer",3020,0,reinterpret_cast<void*>(&cuMemHostGetDevicePointer_v3020)) },
	{"cuMemHostGetFlags_v2030",CuDriverFunction("cuMemHostGetFlags",2030,0,reinterpret_cast<void*>(&cuMemHostGetFlags_v2030)) },
	{"cuMemAllocManaged_v6000",CuDriverFunction("cuMemAllocManaged",6000,0,reinterpret_cast<void*>(&cuMemAllocManaged_v6000)) },
	{"cuDeviceGetByPCIBusId_v4010",CuDriverFunction("cuDeviceGetByPCIBusId",4010,0,reinterpret_cast<void*>(&cuDeviceGetByPCIBusId_v4010)) },
	{"cuDeviceGetPCIBusId_v4010",CuDriverFunction("cuDeviceGetPCIBusId",4010,0,reinterpret_cast<void*>(&cuDeviceGetPCIBusId_v4010)) },
	{"cuIpcGetEventHandle_v4010",CuDriverFunction("cuIpcGetEventHandle",4010,0,reinterpret_cast<void*>(&cuIpcGetEventHandle_v4010)) },
	{"cuIpcOpenEventHandle_v4010",CuDriverFunction("cuIpcOpenEventHandle",4010,0,reinterpret_cast<void*>(&cuIpcOpenEventHandle_v4010)) },
	{"cuIpcGetMemHandle_v4010",CuDriverFunction("cuIpcGetMemHandle",4010,0,reinterpret_cast<void*>(&cuIpcGetMemHandle_v4010)) },
	{"cuIpcOpenMemHandle_v11000",CuDriverFunction("cuIpcOpenMemHandle",11000,0,reinterpret_cast<void*>(&cuIpcOpenMemHandle_v11000)) },
	{"cuIpcCloseMemHandle_v4010",CuDriverFunction("cuIpcCloseMemHandle",4010,0,reinterpret_cast<void*>(&cuIpcCloseMemHandle_v4010)) },
	{"cuMemHostRegister_v6050",CuDriverFunction("cuMemHostRegister",6050,0,reinterpret_cast<void*>(&cuMemHostRegister_v6050)) },
	{"cuMemHostUnregister_v4000",CuDriverFunction("cuMemHostUnregister",4000,0,reinterpret_cast<void*>(&cuMemHostUnregister_v4000)) },
	{"cuMemcpy_v7000_ptds",CuDriverFunction("cuMemcpy",7000,1,reinterpret_cast<void*>(&cuMemcpy_v7000_ptds)) },
	{"cuMemcpyPeer_v7000_ptds",CuDriverFunction("cuMemcpyPeer",7000,1,reinterpret_cast<void*>(&cuMemcpyPeer_v7000_ptds)) },
	{"cuMemcpyHtoD_v7000_ptds",CuDriverFunction("cuMemcpyHtoD",7000,1,reinterpret_cast<void*>(&cuMemcpyHtoD_v7000_ptds)) },
	{"cuMemcpyDtoH_v7000_ptds",CuDriverFunction("cuMemcpyDtoH",7000,1,reinterpret_cast<void*>(&cuMemcpyDtoH_v7000_ptds)) },
	{"cuMemcpyDtoD_v7000_ptds",CuDriverFunction("cuMemcpyDtoD",7000,1,reinterpret_cast<void*>(&cuMemcpyDtoD_v7000_ptds)) },
	{"cuMemcpyDtoA_v7000_ptds",CuDriverFunction("cuMemcpyDtoA",7000,1,reinterpret_cast<void*>(&cuMemcpyDtoA_v7000_ptds)) },
	{"cuMemcpyAtoD_v7000_ptds",CuDriverFunction("cuMemcpyAtoD",7000,1,reinterpret_cast<void*>(&cuMemcpyAtoD_v7000_ptds)) },
	{"cuMemcpyHtoA_v7000_ptds",CuDriverFunction("cuMemcpyHtoA",7000,1,reinterpret_cast<void*>(&cuMemcpyHtoA_v7000_ptds)) },
	{"cuMemcpyAtoH_v7000_ptds",CuDriverFunction("cuMemcpyAtoH",7000,1,reinterpret_cast<void*>(&cuMemcpyAtoH_v7000_ptds)) },
	{"cuMemcpyAtoA_v7000_ptds",CuDriverFunction("cuMemcpyAtoA",7000,1,reinterpret_cast<void*>(&cuMemcpyAtoA_v7000_ptds)) },
	{"cuMemcpy2D_v7000_ptds",CuDriverFunction("cuMemcpy2D",7000,1,reinterpret_cast<void*>(&cuMemcpy2D_v7000_ptds)) },
	{"cuMemcpy2DUnaligned_v7000_ptds",CuDriverFunction("cuMemcpy2DUnaligned",7000,1,reinterpret_cast<void*>(&cuMemcpy2DUnaligned_v7000_ptds)) },
	{"cuMemcpy3D_v7000_ptds",CuDriverFunction("cuMemcpy3D",7000,1,reinterpret_cast<void*>(&cuMemcpy3D_v7000_ptds)) },
	{"cuMemcpy3DPeer_v7000_ptds",CuDriverFunction("cuMemcpy3DPeer",7000,1,reinterpret_cast<void*>(&cuMemcpy3DPeer_v7000_ptds)) },
	{"cuMemcpyAsync_v7000_ptsz",CuDriverFunction("cuMemcpyAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyAsync_v7000_ptsz)) },
	{"cuMemcpyPeerAsync_v7000_ptsz",CuDriverFunction("cuMemcpyPeerAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyPeerAsync_v7000_ptsz)) },
	{"cuMemcpyHtoDAsync_v7000_ptsz",CuDriverFunction("cuMemcpyHtoDAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyHtoDAsync_v7000_ptsz)) },
	{"cuMemcpyDtoHAsync_v7000_ptsz",CuDriverFunction("cuMemcpyDtoHAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyDtoHAsync_v7000_ptsz)) },
	{"cuMemcpyDtoDAsync_v7000_ptsz",CuDriverFunction("cuMemcpyDtoDAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyDtoDAsync_v7000_ptsz)) },
	{"cuMemcpyHtoAAsync_v7000_ptsz",CuDriverFunction("cuMemcpyHtoAAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyHtoAAsync_v7000_ptsz)) },
	{"cuMemcpyAtoHAsync_v7000_ptsz",CuDriverFunction("cuMemcpyAtoHAsync",7000,2,reinterpret_cast<void*>(&cuMemcpyAtoHAsync_v7000_ptsz)) },
	{"cuMemcpy2DAsync_v7000_ptsz",CuDriverFunction("cuMemcpy2DAsync",7000,2,reinterpret_cast<void*>(&cuMemcpy2DAsync_v7000_ptsz)) },
	{"cuMemcpy3DAsync_v7000_ptsz",CuDriverFunction("cuMemcpy3DAsync",7000,2,reinterpret_cast<void*>(&cuMemcpy3DAsync_v7000_ptsz)) },
	{"cuMemcpy3DPeerAsync_v7000_ptsz",CuDriverFunction("cuMemcpy3DPeerAsync",7000,2,reinterpret_cast<void*>(&cuMemcpy3DPeerAsync_v7000_ptsz)) },
	{"cuMemsetD8_v7000_ptds",CuDriverFunction("cuMemsetD8",7000,1,reinterpret_cast<void*>(&cuMemsetD8_v7000_ptds)) },
	{"cuMemsetD16_v7000_ptds",CuDriverFunction("cuMemsetD16",7000,1,reinterpret_cast<void*>(&cuMemsetD16_v7000_ptds)) },
	{"cuMemsetD32_v7000_ptds",CuDriverFunction("cuMemsetD32",7000,1,reinterpret_cast<void*>(&cuMemsetD32_v7000_ptds)) },
	{"cuMemsetD2D8_v7000_ptds",CuDriverFunction("cuMemsetD2D8",7000,1,reinterpret_cast<void*>(&cuMemsetD2D8_v7000_ptds)) },
	{"cuMemsetD2D16_v7000_ptds",CuDriverFunction("cuMemsetD2D16",7000,1,reinterpret_cast<void*>(&cuMemsetD2D16_v7000_ptds)) },
	{"cuMemsetD2D32_v7000_ptds",CuDriverFunction("cuMemsetD2D32",7000,1,reinterpret_cast<void*>(&cuMemsetD2D32_v7000_ptds)) },
	{"cuMemsetD8Async_v7000_ptsz",CuDriverFunction("cuMemsetD8Async",7000,2,reinterpret_cast<void*>(&cuMemsetD8Async_v7000_ptsz)) },
	{"cuMemsetD16Async_v7000_ptsz",CuDriverFunction("cuMemsetD16Async",7000,2,reinterpret_cast<void*>(&cuMemsetD16Async_v7000_ptsz)) },
	{"cuMemsetD32Async_v7000_ptsz",CuDriverFunction("cuMemsetD32Async",7000,2,reinterpret_cast<void*>(&cuMemsetD32Async_v7000_ptsz)) },
	{"cuMemsetD2D8Async_v7000_ptsz",CuDriverFunction("cuMemsetD2D8Async",7000,2,reinterpret_cast<void*>(&cuMemsetD2D8Async_v7000_ptsz)) },
	{"cuMemsetD2D16Async_v7000_ptsz",CuDriverFunction("cuMemsetD2D16Async",7000,2,reinterpret_cast<void*>(&cuMemsetD2D16Async_v7000_ptsz)) },
	{"cuMemsetD2D32Async_v7000_ptsz",CuDriverFunction("cuMemsetD2D32Async",7000,2,reinterpret_cast<void*>(&cuMemsetD2D32Async_v7000_ptsz)) },
	{"cuArrayCreate_v3020",CuDriverFunction("cuArrayCreate",3020,0,reinterpret_cast<void*>(&cuArrayCreate_v3020)) },
	{"cuArrayGetDescriptor_v3020",CuDriverFunction("cuArrayGetDescriptor",3020,0,reinterpret_cast<void*>(&cuArrayGetDescriptor_v3020)) },
	{"cuArrayGetSparseProperties_v11010",CuDriverFunction("cuArrayGetSparseProperties",11010,0,reinterpret_cast<void*>(&cuArrayGetSparseProperties_v11010)) },
	{"cuMipmappedArrayGetSparseProperties_v11010",CuDriverFunction("cuMipmappedArrayGetSparseProperties",11010,0,reinterpret_cast<void*>(&cuMipmappedArrayGetSparseProperties_v11010)) },
	{"cuArrayGetMemoryRequirements_v11060",CuDriverFunction("cuArrayGetMemoryRequirements",11060,0,reinterpret_cast<void*>(&cuArrayGetMemoryRequirements_v11060)) },
	{"cuMipmappedArrayGetMemoryRequirements_v11060",CuDriverFunction("cuMipmappedArrayGetMemoryRequirements",11060,0,reinterpret_cast<void*>(&cuMipmappedArrayGetMemoryRequirements_v11060)) },
	{"cuArrayGetPlane_v11020",CuDriverFunction("cuArrayGetPlane",11020,0,reinterpret_cast<void*>(&cuArrayGetPlane_v11020)) },
	{"cuArrayDestroy_v2000",CuDriverFunction("cuArrayDestroy",2000,0,reinterpret_cast<void*>(&cuArrayDestroy_v2000)) },
	{"cuArray3DCreate_v3020",CuDriverFunction("cuArray3DCreate",3020,0,reinterpret_cast<void*>(&cuArray3DCreate_v3020)) },
	{"cuArray3DGetDescriptor_v3020",CuDriverFunction("cuArray3DGetDescriptor",3020,0,reinterpret_cast<void*>(&cuArray3DGetDescriptor_v3020)) },
	{"cuMipmappedArrayCreate_v5000",CuDriverFunction("cuMipmappedArrayCreate",5000,0,reinterpret_cast<void*>(&cuMipmappedArrayCreate_v5000)) },
	{"cuMipmappedArrayGetLevel_v5000",CuDriverFunction("cuMipmappedArrayGetLevel",5000,0,reinterpret_cast<void*>(&cuMipmappedArrayGetLevel_v5000)) },
	{"cuMipmappedArrayDestroy_v5000",CuDriverFunction("cuMipmappedArrayDestroy",5000,0,reinterpret_cast<void*>(&cuMipmappedArrayDestroy_v5000)) },
	{"cuMemAddressReserve_v10020",CuDriverFunction("cuMemAddressReserve",10020,0,reinterpret_cast<void*>(&cuMemAddressReserve_v10020)) },
	{"cuMemAddressFree_v10020",CuDriverFunction("cuMemAddressFree",10020,0,reinterpret_cast<void*>(&cuMemAddressFree_v10020)) },
	{"cuMemCreate_v10020",CuDriverFunction("cuMemCreate",10020,0,reinterpret_cast<void*>(&cuMemCreate_v10020)) },
	{"cuMemRelease_v10020",CuDriverFunction("cuMemRelease",10020,0,reinterpret_cast<void*>(&cuMemRelease_v10020)) },
	{"cuMemMap_v10020",CuDriverFunction("cuMemMap",10020,0,reinterpret_cast<void*>(&cuMemMap_v10020)) },
	{"cuMemMapArrayAsync_v11010_ptsz",CuDriverFunction("cuMemMapArrayAsync",11010,2,reinterpret_cast<void*>(&cuMemMapArrayAsync_v11010_ptsz)) },
	{"cuMemUnmap_v10020",CuDriverFunction("cuMemUnmap",10020,0,reinterpret_cast<void*>(&cuMemUnmap_v10020)) },
	{"cuMemSetAccess_v10020",CuDriverFunction("cuMemSetAccess",10020,0,reinterpret_cast<void*>(&cuMemSetAccess_v10020)) },
	{"cuMemGetAccess_v10020",CuDriverFunction("cuMemGetAccess",10020,0,reinterpret_cast<void*>(&cuMemGetAccess_v10020)) },
	{"cuMemExportToShareableHandle_v10020",CuDriverFunction("cuMemExportToShareableHandle",10020,0,reinterpret_cast<void*>(&cuMemExportToShareableHandle_v10020)) },
	{"cuMemImportFromShareableHandle_v10020",CuDriverFunction("cuMemImportFromShareableHandle",10020,0,reinterpret_cast<void*>(&cuMemImportFromShareableHandle_v10020)) },
	{"cuMemGetAllocationGranularity_v10020",CuDriverFunction("cuMemGetAllocationGranularity",10020,0,reinterpret_cast<void*>(&cuMemGetAllocationGranularity_v10020)) },
	{"cuMemGetAllocationPropertiesFromHandle_v10020",CuDriverFunction("cuMemGetAllocationPropertiesFromHandle",10020,0,reinterpret_cast<void*>(&cuMemGetAllocationPropertiesFromHandle_v10020)) },
	{"cuMemRetainAllocationHandle_v11000",CuDriverFunction("cuMemRetainAllocationHandle",11000,0,reinterpret_cast<void*>(&cuMemRetainAllocationHandle_v11000)) },
	{"cuMemFreeAsync_v11020_ptsz",CuDriverFunction("cuMemFreeAsync",11020,2,reinterpret_cast<void*>(&cuMemFreeAsync_v11020_ptsz)) },
	{"cuMemAllocAsync_v11020_ptsz",CuDriverFunction("cuMemAllocAsync",11020,2,reinterpret_cast<void*>(&cuMemAllocAsync_v11020_ptsz)) },
	{"cuMemPoolTrimTo_v11020",CuDriverFunction("cuMemPoolTrimTo",11020,0,reinterpret_cast<void*>(&cuMemPoolTrimTo_v11020)) },
	{"cuMemPoolSetAttribute_v11020",CuDriverFunction("cuMemPoolSetAttribute",11020,0,reinterpret_cast<void*>(&cuMemPoolSetAttribute_v11020)) },
	{"cuMemPoolGetAttribute_v11020",CuDriverFunction("cuMemPoolGetAttribute",11020,0,reinterpret_cast<void*>(&cuMemPoolGetAttribute_v11020)) },
	{"cuMemPoolSetAccess_v11020",CuDriverFunction("cuMemPoolSetAccess",11020,0,reinterpret_cast<void*>(&cuMemPoolSetAccess_v11020)) },
	{"cuMemPoolGetAccess_v11020",CuDriverFunction("cuMemPoolGetAccess",11020,0,reinterpret_cast<void*>(&cuMemPoolGetAccess_v11020)) },
	{"cuMemPoolCreate_v11020",CuDriverFunction("cuMemPoolCreate",11020,0,reinterpret_cast<void*>(&cuMemPoolCreate_v11020)) },
	{"cuMemPoolDestroy_v11020",CuDriverFunction("cuMemPoolDestroy",11020,0,reinterpret_cast<void*>(&cuMemPoolDestroy_v11020)) },
	{"cuMemAllocFromPoolAsync_v11020_ptsz",CuDriverFunction("cuMemAllocFromPoolAsync",11020,2,reinterpret_cast<void*>(&cuMemAllocFromPoolAsync_v11020_ptsz)) },
	{"cuMemPoolExportToShareableHandle_v11020",CuDriverFunction("cuMemPoolExportToShareableHandle",11020,0,reinterpret_cast<void*>(&cuMemPoolExportToShareableHandle_v11020)) },
	{"cuMemPoolImportFromShareableHandle_v11020",CuDriverFunction("cuMemPoolImportFromShareableHandle",11020,0,reinterpret_cast<void*>(&cuMemPoolImportFromShareableHandle_v11020)) },
	{"cuMemPoolExportPointer_v11020",CuDriverFunction("cuMemPoolExportPointer",11020,0,reinterpret_cast<void*>(&cuMemPoolExportPointer_v11020)) },
	{"cuMemPoolImportPointer_v11020",CuDriverFunction("cuMemPoolImportPointer",11020,0,reinterpret_cast<void*>(&cuMemPoolImportPointer_v11020)) },
	{"cuPointerGetAttribute_v4000",CuDriverFunction("cuPointerGetAttribute",4000,0,reinterpret_cast<void*>(&cuPointerGetAttribute_v4000)) },
	{"cuMemPrefetchAsync_v8000_ptsz",CuDriverFunction("cuMemPrefetchAsync",8000,2,reinterpret_cast<void*>(&cuMemPrefetchAsync_v8000_ptsz)) },
	{"cuMemAdvise_v8000",CuDriverFunction("cuMemAdvise",8000,0,reinterpret_cast<void*>(&cuMemAdvise_v8000)) },
	{"cuMemAdvise_v12020",CuDriverFunction("cuMemAdvise",12020,0,reinterpret_cast<void*>(&cuMemAdvise_v12020)) },
	{"cuMemPrefetchAsync_v12020_ptsz",CuDriverFunction("cuMemPrefetchAsync",12020,2,reinterpret_cast<void*>(&cuMemPrefetchAsync_v12020_ptsz)) },
	{"cuMemRangeGetAttribute_v8000",CuDriverFunction("cuMemRangeGetAttribute",8000,0,reinterpret_cast<void*>(&cuMemRangeGetAttribute_v8000)) },
	{"cuMemRangeGetAttributes_v8000",CuDriverFunction("cuMemRangeGetAttributes",8000,0,reinterpret_cast<void*>(&cuMemRangeGetAttributes_v8000)) },
	{"cuMulticastCreate_v12010",CuDriverFunction("cuMulticastCreate",12010,0,reinterpret_cast<void*>(&cuMulticastCreate_v12010)) },
	{"cuMulticastAddDevice_v12010",CuDriverFunction("cuMulticastAddDevice",12010,0,reinterpret_cast<void*>(&cuMulticastAddDevice_v12010)) },
	{"cuMulticastBindMem_v12010",CuDriverFunction("cuMulticastBindMem",12010,0,reinterpret_cast<void*>(&cuMulticastBindMem_v12010)) },
	{"cuMulticastBindAddr_v12010",CuDriverFunction("cuMulticastBindAddr",12010,0,reinterpret_cast<void*>(&cuMulticastBindAddr_v12010)) },
	{"cuMulticastUnbind_v12010",CuDriverFunction("cuMulticastUnbind",12010,0,reinterpret_cast<void*>(&cuMulticastUnbind_v12010)) },
	{"cuMulticastGetGranularity_v12010",CuDriverFunction("cuMulticastGetGranularity",12010,0,reinterpret_cast<void*>(&cuMulticastGetGranularity_v12010)) },
	{"cuPointerSetAttribute_v6000",CuDriverFunction("cuPointerSetAttribute",6000,0,reinterpret_cast<void*>(&cuPointerSetAttribute_v6000)) },
	{"cuPointerGetAttributes_v7000",CuDriverFunction("cuPointerGetAttributes",7000,0,reinterpret_cast<void*>(&cuPointerGetAttributes_v7000)) },
	{"cuStreamCreate_v2000",CuDriverFunction("cuStreamCreate",2000,0,reinterpret_cast<void*>(&cuStreamCreate_v2000)) },
	{"cuStreamCreateWithPriority_v5050",CuDriverFunction("cuStreamCreateWithPriority",5050,0,reinterpret_cast<void*>(&cuStreamCreateWithPriority_v5050)) },
	{"cuStreamGetId_v12000",CuDriverFunction("cuStreamGetId",12000,0,reinterpret_cast<void*>(&cuStreamGetId_v12000)) },
	{"cuStreamGetId_v12000_ptsz",CuDriverFunction("cuStreamGetId",12000,2,reinterpret_cast<void*>(&cuStreamGetId_v12000_ptsz)) },
	{"cuStreamGetPriority_v7000_ptsz",CuDriverFunction("cuStreamGetPriority",7000,2,reinterpret_cast<void*>(&cuStreamGetPriority_v7000_ptsz)) },
	{"cuStreamGetFlags_v7000_ptsz",CuDriverFunction("cuStreamGetFlags",7000,2,reinterpret_cast<void*>(&cuStreamGetFlags_v7000_ptsz)) },
	{"cuStreamGetCtx_v9020_ptsz",CuDriverFunction("cuStreamGetCtx",9020,2,reinterpret_cast<void*>(&cuStreamGetCtx_v9020_ptsz)) },
	{"cuStreamWaitEvent_v7000_ptsz",CuDriverFunction("cuStreamWaitEvent",7000,2,reinterpret_cast<void*>(&cuStreamWaitEvent_v7000_ptsz)) },
	{"cuStreamAddCallback_v7000_ptsz",CuDriverFunction("cuStreamAddCallback",7000,2,reinterpret_cast<void*>(&cuStreamAddCallback_v7000_ptsz)) },
	{"cuStreamBeginCapture_v10010_ptsz",CuDriverFunction("cuStreamBeginCapture",10010,2,reinterpret_cast<void*>(&cuStreamBeginCapture_v10010_ptsz)) },
	{"cuStreamBeginCaptureToGraph_v12030_ptsz",CuDriverFunction("cuStreamBeginCaptureToGraph",12030,2,reinterpret_cast<void*>(&cuStreamBeginCaptureToGraph_v12030_ptsz)) },
	{"cuThreadExchangeStreamCaptureMode_v10010",CuDriverFunction("cuThreadExchangeStreamCaptureMode",10010,0,reinterpret_cast<void*>(&cuThreadExchangeStreamCaptureMode_v10010)) },
	{"cuStreamEndCapture_v10000_ptsz",CuDriverFunction("cuStreamEndCapture",10000,2,reinterpret_cast<void*>(&cuStreamEndCapture_v10000_ptsz)) },
	{"cuStreamIsCapturing_v10000_ptsz",CuDriverFunction("cuStreamIsCapturing",10000,2,reinterpret_cast<void*>(&cuStreamIsCapturing_v10000_ptsz)) },
	{"cuStreamGetCaptureInfo_v10010_ptsz",CuDriverFunction("cuStreamGetCaptureInfo",10010,2,reinterpret_cast<void*>(&cuStreamGetCaptureInfo_v10010_ptsz)) },
	{"cuStreamGetCaptureInfo_v11030_ptsz",CuDriverFunction("cuStreamGetCaptureInfo",11030,2,reinterpret_cast<void*>(&cuStreamGetCaptureInfo_v11030_ptsz)) },
	{"cuStreamGetCaptureInfo_v12030_ptsz",CuDriverFunction("cuStreamGetCaptureInfo",12030,2,reinterpret_cast<void*>(&cuStreamGetCaptureInfo_v12030_ptsz)) },
	{"cuStreamUpdateCaptureDependencies_v11030_ptsz",CuDriverFunction("cuStreamUpdateCaptureDependencies",11030,2,reinterpret_cast<void*>(&cuStreamUpdateCaptureDependencies_v11030_ptsz)) },
	{"cuStreamUpdateCaptureDependencies_v12030_ptsz",CuDriverFunction("cuStreamUpdateCaptureDependencies",12030,2,reinterpret_cast<void*>(&cuStreamUpdateCaptureDependencies_v12030_ptsz)) },
	{"cuStreamAttachMemAsync_v7000_ptsz",CuDriverFunction("cuStreamAttachMemAsync",7000,2,reinterpret_cast<void*>(&cuStreamAttachMemAsync_v7000_ptsz)) },
	{"cuStreamQuery_v7000_ptsz",CuDriverFunction("cuStreamQuery",7000,2,reinterpret_cast<void*>(&cuStreamQuery_v7000_ptsz)) },
	{"cuStreamSynchronize_v7000_ptsz",CuDriverFunction("cuStreamSynchronize",7000,2,reinterpret_cast<void*>(&cuStreamSynchronize_v7000_ptsz)) },
	{"cuStreamDestroy_v4000",CuDriverFunction("cuStreamDestroy",4000,0,reinterpret_cast<void*>(&cuStreamDestroy_v4000)) },
	{"cuStreamCopyAttributes_v11000_ptsz",CuDriverFunction("cuStreamCopyAttributes",11000,2,reinterpret_cast<void*>(&cuStreamCopyAttributes_v11000_ptsz)) },
	{"cuStreamGetAttribute_v11000_ptsz",CuDriverFunction("cuStreamGetAttribute",11000,2,reinterpret_cast<void*>(&cuStreamGetAttribute_v11000_ptsz)) },
	{"cuStreamSetAttribute_v11000_ptsz",CuDriverFunction("cuStreamSetAttribute",11000,2,reinterpret_cast<void*>(&cuStreamSetAttribute_v11000_ptsz)) },
	{"cuEventCreate_v2000",CuDriverFunction("cuEventCreate",2000,0,reinterpret_cast<void*>(&cuEventCreate_v2000)) },
	{"cuEventRecord_v7000_ptsz",CuDriverFunction("cuEventRecord",7000,2,reinterpret_cast<void*>(&cuEventRecord_v7000_ptsz)) },
	{"cuEventRecordWithFlags_v11010_ptsz",CuDriverFunction("cuEventRecordWithFlags",11010,2,reinterpret_cast<void*>(&cuEventRecordWithFlags_v11010_ptsz)) },
	{"cuEventQuery_v2000",CuDriverFunction("cuEventQuery",2000,0,reinterpret_cast<void*>(&cuEventQuery_v2000)) },
	{"cuEventSynchronize_v2000",CuDriverFunction("cuEventSynchronize",2000,0,reinterpret_cast<void*>(&cuEventSynchronize_v2000)) },
	{"cuEventDestroy_v4000",CuDriverFunction("cuEventDestroy",4000,0,reinterpret_cast<void*>(&cuEventDestroy_v4000)) },
	{"cuEventElapsedTime_v2000",CuDriverFunction("cuEventElapsedTime",2000,0,reinterpret_cast<void*>(&cuEventElapsedTime_v2000)) },
	{"cuImportExternalMemory_v10000",CuDriverFunction("cuImportExternalMemory",10000,0,reinterpret_cast<void*>(&cuImportExternalMemory_v10000)) },
	{"cuExternalMemoryGetMappedBuffer_v10000",CuDriverFunction("cuExternalMemoryGetMappedBuffer",10000,0,reinterpret_cast<void*>(&cuExternalMemoryGetMappedBuffer_v10000)) },
	{"cuExternalMemoryGetMappedMipmappedArray_v10000",CuDriverFunction("cuExternalMemoryGetMappedMipmappedArray",10000,0,reinterpret_cast<void*>(&cuExternalMemoryGetMappedMipmappedArray_v10000)) },
	{"cuDestroyExternalMemory_v10000",CuDriverFunction("cuDestroyExternalMemory",10000,0,reinterpret_cast<void*>(&cuDestroyExternalMemory_v10000)) },
	{"cuImportExternalSemaphore_v10000",CuDriverFunction("cuImportExternalSemaphore",10000,0,reinterpret_cast<void*>(&cuImportExternalSemaphore_v10000)) },
	{"cuSignalExternalSemaphoresAsync_v10000_ptsz",CuDriverFunction("cuSignalExternalSemaphoresAsync",10000,2,reinterpret_cast<void*>(&cuSignalExternalSemaphoresAsync_v10000_ptsz)) },
	{"cuWaitExternalSemaphoresAsync_v10000_ptsz",CuDriverFunction("cuWaitExternalSemaphoresAsync",10000,2,reinterpret_cast<void*>(&cuWaitExternalSemaphoresAsync_v10000_ptsz)) },
	{"cuDestroyExternalSemaphore_v10000",CuDriverFunction("cuDestroyExternalSemaphore",10000,0,reinterpret_cast<void*>(&cuDestroyExternalSemaphore_v10000)) },
	{"cuStreamWaitValue32_v8000_ptsz",CuDriverFunction("cuStreamWaitValue32",8000,2,reinterpret_cast<void*>(&cuStreamWaitValue32_v8000_ptsz)) },
	{"cuStreamWaitValue64_v9000_ptsz",CuDriverFunction("cuStreamWaitValue64",9000,2,reinterpret_cast<void*>(&cuStreamWaitValue64_v9000_ptsz)) },
	{"cuStreamWriteValue32_v8000_ptsz",CuDriverFunction("cuStreamWriteValue32",8000,2,reinterpret_cast<void*>(&cuStreamWriteValue32_v8000_ptsz)) },
	{"cuStreamWriteValue64_v9000_ptsz",CuDriverFunction("cuStreamWriteValue64",9000,2,reinterpret_cast<void*>(&cuStreamWriteValue64_v9000_ptsz)) },
	{"cuStreamBatchMemOp_v8000_ptsz",CuDriverFunction("cuStreamBatchMemOp",8000,2,reinterpret_cast<void*>(&cuStreamBatchMemOp_v8000_ptsz)) },
	{"cuStreamWaitValue32_v11070_ptsz",CuDriverFunction("cuStreamWaitValue32",11070,2,reinterpret_cast<void*>(&cuStreamWaitValue32_v11070_ptsz)) },
	{"cuStreamWaitValue64_v11070_ptsz",CuDriverFunction("cuStreamWaitValue64",11070,2,reinterpret_cast<void*>(&cuStreamWaitValue64_v11070_ptsz)) },
	{"cuStreamWriteValue32_v11070_ptsz",CuDriverFunction("cuStreamWriteValue32",11070,2,reinterpret_cast<void*>(&cuStreamWriteValue32_v11070_ptsz)) },
	{"cuStreamWriteValue64_v11070_ptsz",CuDriverFunction("cuStreamWriteValue64",11070,2,reinterpret_cast<void*>(&cuStreamWriteValue64_v11070_ptsz)) },
	{"cuStreamBatchMemOp_v11070_ptsz",CuDriverFunction("cuStreamBatchMemOp",11070,2,reinterpret_cast<void*>(&cuStreamBatchMemOp_v11070_ptsz)) },
	{"cuFuncGetAttribute_v2020",CuDriverFunction("cuFuncGetAttribute",2020,0,reinterpret_cast<void*>(&cuFuncGetAttribute_v2020)) },
	{"cuFuncSetAttribute_v9000",CuDriverFunction("cuFuncSetAttribute",9000,0,reinterpret_cast<void*>(&cuFuncSetAttribute_v9000)) },
	{"cuFuncSetCacheConfig_v3000",CuDriverFunction("cuFuncSetCacheConfig",3000,0,reinterpret_cast<void*>(&cuFuncSetCacheConfig_v3000)) },
	{"cuFuncSetSharedMemConfig_v4020",CuDriverFunction("cuFuncSetSharedMemConfig",4020,0,reinterpret_cast<void*>(&cuFuncSetSharedMemConfig_v4020)) },
	{"cuFuncGetName_v12030",CuDriverFunction("cuFuncGetName",12030,0,reinterpret_cast<void*>(&cuFuncGetName_v12030)) },
	{"cuFuncGetParamInfo_v12040",CuDriverFunction("cuFuncGetParamInfo",12040,0,reinterpret_cast<void*>(&cuFuncGetParamInfo_v12040)) },
	{"cuFuncIsLoaded_v12040",CuDriverFunction("cuFuncIsLoaded",12040,0,reinterpret_cast<void*>(&cuFuncIsLoaded_v12040)) },
	{"cuFuncLoad_v12040",CuDriverFunction("cuFuncLoad",12040,0,reinterpret_cast<void*>(&cuFuncLoad_v12040)) },
	{"cuLaunchKernel_v7000_ptsz",CuDriverFunction("cuLaunchKernel",7000,2,reinterpret_cast<void*>(&cuLaunchKernel_v7000_ptsz)) },
	{"cuLaunchKernelEx_v11060_ptsz",CuDriverFunction("cuLaunchKernelEx",11060,2,reinterpret_cast<void*>(&cuLaunchKernelEx_v11060_ptsz)) },
	{"cuLaunchCooperativeKernel_v9000_ptsz",CuDriverFunction("cuLaunchCooperativeKernel",9000,2,reinterpret_cast<void*>(&cuLaunchCooperativeKernel_v9000_ptsz)) },
	{"cuLaunchCooperativeKernelMultiDevice_v9000",CuDriverFunction("cuLaunchCooperativeKernelMultiDevice",9000,0,reinterpret_cast<void*>(&cuLaunchCooperativeKernelMultiDevice_v9000)) },
	{"cuLaunchHostFunc_v10000_ptsz",CuDriverFunction("cuLaunchHostFunc",10000,2,reinterpret_cast<void*>(&cuLaunchHostFunc_v10000_ptsz)) },
	{"cuFuncSetBlockShape_v2000",CuDriverFunction("cuFuncSetBlockShape",2000,0,reinterpret_cast<void*>(&cuFuncSetBlockShape_v2000)) },
	{"cuFuncSetSharedSize_v2000",CuDriverFunction("cuFuncSetSharedSize",2000,0,reinterpret_cast<void*>(&cuFuncSetSharedSize_v2000)) },
	{"cuParamSetSize_v2000",CuDriverFunction("cuParamSetSize",2000,0,reinterpret_cast<void*>(&cuParamSetSize_v2000)) },
	{"cuParamSeti_v2000",CuDriverFunction("cuParamSeti",2000,0,reinterpret_cast<void*>(&cuParamSeti_v2000)) },
	{"cuParamSetf_v2000",CuDriverFunction("cuParamSetf",2000,0,reinterpret_cast<void*>(&cuParamSetf_v2000)) },
	{"cuParamSetv_v2000",CuDriverFunction("cuParamSetv",2000,0,reinterpret_cast<void*>(&cuParamSetv_v2000)) },
	{"cuLaunch_v2000",CuDriverFunction("cuLaunch",2000,0,reinterpret_cast<void*>(&cuLaunch_v2000)) },
	{"cuLaunchGrid_v2000",CuDriverFunction("cuLaunchGrid",2000,0,reinterpret_cast<void*>(&cuLaunchGrid_v2000)) },
	{"cuLaunchGridAsync_v2000",CuDriverFunction("cuLaunchGridAsync",2000,0,reinterpret_cast<void*>(&cuLaunchGridAsync_v2000)) },
	{"cuParamSetTexRef_v2000",CuDriverFunction("cuParamSetTexRef",2000,0,reinterpret_cast<void*>(&cuParamSetTexRef_v2000)) },
	{"cuGraphCreate_v10000",CuDriverFunction("cuGraphCreate",10000,0,reinterpret_cast<void*>(&cuGraphCreate_v10000)) },
	{"cuGraphAddKernelNode_v10000",CuDriverFunction("cuGraphAddKernelNode",10000,0,reinterpret_cast<void*>(&cuGraphAddKernelNode_v10000)) },
	{"cuGraphKernelNodeGetParams_v10000",CuDriverFunction("cuGraphKernelNodeGetParams",10000,0,reinterpret_cast<void*>(&cuGraphKernelNodeGetParams_v10000)) },
	{"cuGraphKernelNodeSetParams_v10000",CuDriverFunction("cuGraphKernelNodeSetParams",10000,0,reinterpret_cast<void*>(&cuGraphKernelNodeSetParams_v10000)) },
	{"cuGraphAddKernelNode_v12000",CuDriverFunction("cuGraphAddKernelNode",12000,0,reinterpret_cast<void*>(&cuGraphAddKernelNode_v12000)) },
	{"cuGraphKernelNodeGetParams_v12000",CuDriverFunction("cuGraphKernelNodeGetParams",12000,0,reinterpret_cast<void*>(&cuGraphKernelNodeGetParams_v12000)) },
	{"cuGraphKernelNodeSetParams_v12000",CuDriverFunction("cuGraphKernelNodeSetParams",12000,0,reinterpret_cast<void*>(&cuGraphKernelNodeSetParams_v12000)) },
	{"cuGraphAddMemcpyNode_v10000",CuDriverFunction("cuGraphAddMemcpyNode",10000,0,reinterpret_cast<void*>(&cuGraphAddMemcpyNode_v10000)) },
	{"cuGraphMemcpyNodeGetParams_v10000",CuDriverFunction("cuGraphMemcpyNodeGetParams",10000,0,reinterpret_cast<void*>(&cuGraphMemcpyNodeGetParams_v10000)) },
	{"cuGraphMemcpyNodeSetParams_v10000",CuDriverFunction("cuGraphMemcpyNodeSetParams",10000,0,reinterpret_cast<void*>(&cuGraphMemcpyNodeSetParams_v10000)) },
	{"cuGraphAddMemsetNode_v10000",CuDriverFunction("cuGraphAddMemsetNode",10000,0,reinterpret_cast<void*>(&cuGraphAddMemsetNode_v10000)) },
	{"cuGraphMemsetNodeGetParams_v10000",CuDriverFunction("cuGraphMemsetNodeGetParams",10000,0,reinterpret_cast<void*>(&cuGraphMemsetNodeGetParams_v10000)) },
	{"cuGraphMemsetNodeSetParams_v10000",CuDriverFunction("cuGraphMemsetNodeSetParams",10000,0,reinterpret_cast<void*>(&cuGraphMemsetNodeSetParams_v10000)) },
	{"cuGraphAddHostNode_v10000",CuDriverFunction("cuGraphAddHostNode",10000,0,reinterpret_cast<void*>(&cuGraphAddHostNode_v10000)) },
	{"cuGraphHostNodeGetParams_v10000",CuDriverFunction("cuGraphHostNodeGetParams",10000,0,reinterpret_cast<void*>(&cuGraphHostNodeGetParams_v10000)) },
	{"cuGraphHostNodeSetParams_v10000",CuDriverFunction("cuGraphHostNodeSetParams",10000,0,reinterpret_cast<void*>(&cuGraphHostNodeSetParams_v10000)) },
	{"cuGraphAddChildGraphNode_v10000",CuDriverFunction("cuGraphAddChildGraphNode",10000,0,reinterpret_cast<void*>(&cuGraphAddChildGraphNode_v10000)) },
	{"cuGraphChildGraphNodeGetGraph_v10000",CuDriverFunction("cuGraphChildGraphNodeGetGraph",10000,0,reinterpret_cast<void*>(&cuGraphChildGraphNodeGetGraph_v10000)) },
	{"cuGraphAddEmptyNode_v10000",CuDriverFunction("cuGraphAddEmptyNode",10000,0,reinterpret_cast<void*>(&cuGraphAddEmptyNode_v10000)) },
	{"cuGraphAddEventRecordNode_v11010",CuDriverFunction("cuGraphAddEventRecordNode",11010,0,reinterpret_cast<void*>(&cuGraphAddEventRecordNode_v11010)) },
	{"cuGraphEventRecordNodeGetEvent_v11010",CuDriverFunction("cuGraphEventRecordNodeGetEvent",11010,0,reinterpret_cast<void*>(&cuGraphEventRecordNodeGetEvent_v11010)) },
	{"cuGraphEventRecordNodeSetEvent_v11010",CuDriverFunction("cuGraphEventRecordNodeSetEvent",11010,0,reinterpret_cast<void*>(&cuGraphEventRecordNodeSetEvent_v11010)) },
	{"cuGraphAddEventWaitNode_v11010",CuDriverFunction("cuGraphAddEventWaitNode",11010,0,reinterpret_cast<void*>(&cuGraphAddEventWaitNode_v11010)) },
	{"cuGraphEventWaitNodeGetEvent_v11010",CuDriverFunction("cuGraphEventWaitNodeGetEvent",11010,0,reinterpret_cast<void*>(&cuGraphEventWaitNodeGetEvent_v11010)) },
	{"cuGraphEventWaitNodeSetEvent_v11010",CuDriverFunction("cuGraphEventWaitNodeSetEvent",11010,0,reinterpret_cast<void*>(&cuGraphEventWaitNodeSetEvent_v11010)) },
	{"cuGraphAddExternalSemaphoresSignalNode_v11020",CuDriverFunction("cuGraphAddExternalSemaphoresSignalNode",11020,0,reinterpret_cast<void*>(&cuGraphAddExternalSemaphoresSignalNode_v11020)) },
	{"cuGraphExternalSemaphoresSignalNodeGetParams_v11020",CuDriverFunction("cuGraphExternalSemaphoresSignalNodeGetParams",11020,0,reinterpret_cast<void*>(&cuGraphExternalSemaphoresSignalNodeGetParams_v11020)) },
	{"cuGraphExternalSemaphoresSignalNodeSetParams_v11020",CuDriverFunction("cuGraphExternalSemaphoresSignalNodeSetParams",11020,0,reinterpret_cast<void*>(&cuGraphExternalSemaphoresSignalNodeSetParams_v11020)) },
	{"cuGraphAddExternalSemaphoresWaitNode_v11020",CuDriverFunction("cuGraphAddExternalSemaphoresWaitNode",11020,0,reinterpret_cast<void*>(&cuGraphAddExternalSemaphoresWaitNode_v11020)) },
	{"cuGraphExternalSemaphoresWaitNodeGetParams_v11020",CuDriverFunction("cuGraphExternalSemaphoresWaitNodeGetParams",11020,0,reinterpret_cast<void*>(&cuGraphExternalSemaphoresWaitNodeGetParams_v11020)) },
	{"cuGraphExternalSemaphoresWaitNodeSetParams_v11020",CuDriverFunction("cuGraphExternalSemaphoresWaitNodeSetParams",11020,0,reinterpret_cast<void*>(&cuGraphExternalSemaphoresWaitNodeSetParams_v11020)) },
	{"cuGraphAddBatchMemOpNode_v11070",CuDriverFunction("cuGraphAddBatchMemOpNode",11070,0,reinterpret_cast<void*>(&cuGraphAddBatchMemOpNode_v11070)) },
	{"cuGraphBatchMemOpNodeGetParams_v11070",CuDriverFunction("cuGraphBatchMemOpNodeGetParams",11070,0,reinterpret_cast<void*>(&cuGraphBatchMemOpNodeGetParams_v11070)) },
	{"cuGraphBatchMemOpNodeSetParams_v11070",CuDriverFunction("cuGraphBatchMemOpNodeSetParams",11070,0,reinterpret_cast<void*>(&cuGraphBatchMemOpNodeSetParams_v11070)) },
	{"cuGraphExecBatchMemOpNodeSetParams_v11070",CuDriverFunction("cuGraphExecBatchMemOpNodeSetParams",11070,0,reinterpret_cast<void*>(&cuGraphExecBatchMemOpNodeSetParams_v11070)) },
	{"cuGraphClone_v10000",CuDriverFunction("cuGraphClone",10000,0,reinterpret_cast<void*>(&cuGraphClone_v10000)) },
	{"cuGraphNodeFindInClone_v10000",CuDriverFunction("cuGraphNodeFindInClone",10000,0,reinterpret_cast<void*>(&cuGraphNodeFindInClone_v10000)) },
	{"cuGraphNodeGetType_v10000",CuDriverFunction("cuGraphNodeGetType",10000,0,reinterpret_cast<void*>(&cuGraphNodeGetType_v10000)) },
	{"cuGraphGetNodes_v10000",CuDriverFunction("cuGraphGetNodes",10000,0,reinterpret_cast<void*>(&cuGraphGetNodes_v10000)) },
	{"cuGraphGetRootNodes_v10000",CuDriverFunction("cuGraphGetRootNodes",10000,0,reinterpret_cast<void*>(&cuGraphGetRootNodes_v10000)) },
	{"cuGraphGetEdges_v10000",CuDriverFunction("cuGraphGetEdges",10000,0,reinterpret_cast<void*>(&cuGraphGetEdges_v10000)) },
	{"cuGraphGetEdges_v12030",CuDriverFunction("cuGraphGetEdges",12030,0,reinterpret_cast<void*>(&cuGraphGetEdges_v12030)) },
	{"cuGraphNodeGetDependencies_v10000",CuDriverFunction("cuGraphNodeGetDependencies",10000,0,reinterpret_cast<void*>(&cuGraphNodeGetDependencies_v10000)) },
	{"cuGraphNodeGetDependencies_v12030",CuDriverFunction("cuGraphNodeGetDependencies",12030,0,reinterpret_cast<void*>(&cuGraphNodeGetDependencies_v12030)) },
	{"cuGraphNodeGetDependentNodes_v10000",CuDriverFunction("cuGraphNodeGetDependentNodes",10000,0,reinterpret_cast<void*>(&cuGraphNodeGetDependentNodes_v10000)) },
	{"cuGraphNodeGetDependentNodes_v12030",CuDriverFunction("cuGraphNodeGetDependentNodes",12030,0,reinterpret_cast<void*>(&cuGraphNodeGetDependentNodes_v12030)) },
	{"cuGraphAddDependencies_v10000",CuDriverFunction("cuGraphAddDependencies",10000,0,reinterpret_cast<void*>(&cuGraphAddDependencies_v10000)) },
	{"cuGraphAddDependencies_v12030",CuDriverFunction("cuGraphAddDependencies",12030,0,reinterpret_cast<void*>(&cuGraphAddDependencies_v12030)) },
	{"cuGraphRemoveDependencies_v10000",CuDriverFunction("cuGraphRemoveDependencies",10000,0,reinterpret_cast<void*>(&cuGraphRemoveDependencies_v10000)) },
	{"cuGraphRemoveDependencies_v12030",CuDriverFunction("cuGraphRemoveDependencies",12030,0,reinterpret_cast<void*>(&cuGraphRemoveDependencies_v12030)) },
	{"cuGraphDestroyNode_v10000",CuDriverFunction("cuGraphDestroyNode",10000,0,reinterpret_cast<void*>(&cuGraphDestroyNode_v10000)) },
	{"cuGraphInstantiateWithFlags_v11040",CuDriverFunction("cuGraphInstantiateWithFlags",11040,0,reinterpret_cast<void*>(&cuGraphInstantiateWithFlags_v11040)) },
	{"cuGraphInstantiateWithParams_v12000_ptsz",CuDriverFunction("cuGraphInstantiateWithParams",12000,2,reinterpret_cast<void*>(&cuGraphInstantiateWithParams_v12000_ptsz)) },
	{"cuGraphExecGetFlags_v12000",CuDriverFunction("cuGraphExecGetFlags",12000,0,reinterpret_cast<void*>(&cuGraphExecGetFlags_v12000)) },
	{"cuGraphExecKernelNodeSetParams_v10010",CuDriverFunction("cuGraphExecKernelNodeSetParams",10010,0,reinterpret_cast<void*>(&cuGraphExecKernelNodeSetParams_v10010)) },
	{"cuGraphExecKernelNodeSetParams_v12000",CuDriverFunction("cuGraphExecKernelNodeSetParams",12000,0,reinterpret_cast<void*>(&cuGraphExecKernelNodeSetParams_v12000)) },
	{"cuGraphExecMemcpyNodeSetParams_v10020",CuDriverFunction("cuGraphExecMemcpyNodeSetParams",10020,0,reinterpret_cast<void*>(&cuGraphExecMemcpyNodeSetParams_v10020)) },
	{"cuGraphExecMemsetNodeSetParams_v10020",CuDriverFunction("cuGraphExecMemsetNodeSetParams",10020,0,reinterpret_cast<void*>(&cuGraphExecMemsetNodeSetParams_v10020)) },
	{"cuGraphExecHostNodeSetParams_v10020",CuDriverFunction("cuGraphExecHostNodeSetParams",10020,0,reinterpret_cast<void*>(&cuGraphExecHostNodeSetParams_v10020)) },
	{"cuGraphExecChildGraphNodeSetParams_v11010",CuDriverFunction("cuGraphExecChildGraphNodeSetParams",11010,0,reinterpret_cast<void*>(&cuGraphExecChildGraphNodeSetParams_v11010)) },
	{"cuGraphExecEventRecordNodeSetEvent_v11010",CuDriverFunction("cuGraphExecEventRecordNodeSetEvent",11010,0,reinterpret_cast<void*>(&cuGraphExecEventRecordNodeSetEvent_v11010)) },
	{"cuGraphExecEventWaitNodeSetEvent_v11010",CuDriverFunction("cuGraphExecEventWaitNodeSetEvent",11010,0,reinterpret_cast<void*>(&cuGraphExecEventWaitNodeSetEvent_v11010)) },
	{"cuGraphExecExternalSemaphoresSignalNodeSetParams_v11020",CuDriverFunction("cuGraphExecExternalSemaphoresSignalNodeSetParams",11020,0,reinterpret_cast<void*>(&cuGraphExecExternalSemaphoresSignalNodeSetParams_v11020)) },
	{"cuGraphExecExternalSemaphoresWaitNodeSetParams_v11020",CuDriverFunction("cuGraphExecExternalSemaphoresWaitNodeSetParams",11020,0,reinterpret_cast<void*>(&cuGraphExecExternalSemaphoresWaitNodeSetParams_v11020)) },
	{"cuGraphUpload_v11010_ptsz",CuDriverFunction("cuGraphUpload",11010,2,reinterpret_cast<void*>(&cuGraphUpload_v11010_ptsz)) },
	{"cuGraphLaunch_v10000_ptsz",CuDriverFunction("cuGraphLaunch",10000,2,reinterpret_cast<void*>(&cuGraphLaunch_v10000_ptsz)) },
	{"cuGraphExecDestroy_v10000",CuDriverFunction("cuGraphExecDestroy",10000,0,reinterpret_cast<void*>(&cuGraphExecDestroy_v10000)) },
	{"cuGraphDestroy_v10000",CuDriverFunction("cuGraphDestroy",10000,0,reinterpret_cast<void*>(&cuGraphDestroy_v10000)) },
	{"cuGraphExecUpdate_v10020",CuDriverFunction("cuGraphExecUpdate",10020,0,reinterpret_cast<void*>(&cuGraphExecUpdate_v10020)) },
	{"cuGraphExecUpdate_v12000",CuDriverFunction("cuGraphExecUpdate",12000,0,reinterpret_cast<void*>(&cuGraphExecUpdate_v12000)) },
	{"cuGraphKernelNodeCopyAttributes_v11000",CuDriverFunction("cuGraphKernelNodeCopyAttributes",11000,0,reinterpret_cast<void*>(&cuGraphKernelNodeCopyAttributes_v11000)) },
	{"cuGraphKernelNodeGetAttribute_v11000",CuDriverFunction("cuGraphKernelNodeGetAttribute",11000,0,reinterpret_cast<void*>(&cuGraphKernelNodeGetAttribute_v11000)) },
	{"cuGraphKernelNodeSetAttribute_v11000",CuDriverFunction("cuGraphKernelNodeSetAttribute",11000,0,reinterpret_cast<void*>(&cuGraphKernelNodeSetAttribute_v11000)) },
	{"cuGraphDebugDotPrint_v11030",CuDriverFunction("cuGraphDebugDotPrint",11030,0,reinterpret_cast<void*>(&cuGraphDebugDotPrint_v11030)) },
	{"cuGraphAddMemAllocNode_v11040",CuDriverFunction("cuGraphAddMemAllocNode",11040,0,reinterpret_cast<void*>(&cuGraphAddMemAllocNode_v11040)) },
	{"cuGraphMemAllocNodeGetParams_v11040",CuDriverFunction("cuGraphMemAllocNodeGetParams",11040,0,reinterpret_cast<void*>(&cuGraphMemAllocNodeGetParams_v11040)) },
	{"cuGraphAddMemFreeNode_v11040",CuDriverFunction("cuGraphAddMemFreeNode",11040,0,reinterpret_cast<void*>(&cuGraphAddMemFreeNode_v11040)) },
	{"cuGraphMemFreeNodeGetParams_v11040",CuDriverFunction("cuGraphMemFreeNodeGetParams",11040,0,reinterpret_cast<void*>(&cuGraphMemFreeNodeGetParams_v11040)) },
	{"cuGraphNodeSetEnabled_v11060",CuDriverFunction("cuGraphNodeSetEnabled",11060,0,reinterpret_cast<void*>(&cuGraphNodeSetEnabled_v11060)) },
	{"cuGraphNodeGetEnabled_v11060",CuDriverFunction("cuGraphNodeGetEnabled",11060,0,reinterpret_cast<void*>(&cuGraphNodeGetEnabled_v11060)) },
	{"cuGraphAddNode_v12020",CuDriverFunction("cuGraphAddNode",12020,0,reinterpret_cast<void*>(&cuGraphAddNode_v12020)) },
	{"cuGraphAddNode_v12030",CuDriverFunction("cuGraphAddNode",12030,0,reinterpret_cast<void*>(&cuGraphAddNode_v12030)) },
	{"cuGraphNodeSetParams_v12020",CuDriverFunction("cuGraphNodeSetParams",12020,0,reinterpret_cast<void*>(&cuGraphNodeSetParams_v12020)) },
	{"cuGraphExecNodeSetParams_v12020",CuDriverFunction("cuGraphExecNodeSetParams",12020,0,reinterpret_cast<void*>(&cuGraphExecNodeSetParams_v12020)) },
	{"cuGraphConditionalHandleCreate_v12030",CuDriverFunction("cuGraphConditionalHandleCreate",12030,0,reinterpret_cast<void*>(&cuGraphConditionalHandleCreate_v12030)) },
	{"cuDeviceGraphMemTrim_v11040",CuDriverFunction("cuDeviceGraphMemTrim",11040,0,reinterpret_cast<void*>(&cuDeviceGraphMemTrim_v11040)) },
	{"cuDeviceGetGraphMemAttribute_v11040",CuDriverFunction("cuDeviceGetGraphMemAttribute",11040,0,reinterpret_cast<void*>(&cuDeviceGetGraphMemAttribute_v11040)) },
	{"cuDeviceSetGraphMemAttribute_v11040",CuDriverFunction("cuDeviceSetGraphMemAttribute",11040,0,reinterpret_cast<void*>(&cuDeviceSetGraphMemAttribute_v11040)) },
	{"cuOccupancyMaxActiveBlocksPerMultiprocessor_v6050",CuDriverFunction("cuOccupancyMaxActiveBlocksPerMultiprocessor",6050,0,reinterpret_cast<void*>(&cuOccupancyMaxActiveBlocksPerMultiprocessor_v6050)) },
	{"cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags_v7000",CuDriverFunction("cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags",7000,0,reinterpret_cast<void*>(&cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags_v7000)) },
	{"cuOccupancyMaxPotentialBlockSize_v6050",CuDriverFunction("cuOccupancyMaxPotentialBlockSize",6050,0,reinterpret_cast<void*>(&cuOccupancyMaxPotentialBlockSize_v6050)) },
	{"cuOccupancyMaxPotentialBlockSizeWithFlags_v7000",CuDriverFunction("cuOccupancyMaxPotentialBlockSizeWithFlags",7000,0,reinterpret_cast<void*>(&cuOccupancyMaxPotentialBlockSizeWithFlags_v7000)) },
	{"cuOccupancyAvailableDynamicSMemPerBlock_v10020",CuDriverFunction("cuOccupancyAvailableDynamicSMemPerBlock",10020,0,reinterpret_cast<void*>(&cuOccupancyAvailableDynamicSMemPerBlock_v10020)) },
	{"cuOccupancyMaxPotentialClusterSize_v11070",CuDriverFunction("cuOccupancyMaxPotentialClusterSize",11070,0,reinterpret_cast<void*>(&cuOccupancyMaxPotentialClusterSize_v11070)) },
	{"cuOccupancyMaxActiveClusters_v11070",CuDriverFunction("cuOccupancyMaxActiveClusters",11070,0,reinterpret_cast<void*>(&cuOccupancyMaxActiveClusters_v11070)) },
	{"cuTexRefSetArray_v2000",CuDriverFunction("cuTexRefSetArray",2000,0,reinterpret_cast<void*>(&cuTexRefSetArray_v2000)) },
	{"cuTexRefSetMipmappedArray_v5000",CuDriverFunction("cuTexRefSetMipmappedArray",5000,0,reinterpret_cast<void*>(&cuTexRefSetMipmappedArray_v5000)) },
	{"cuTexRefSetAddress_v3020",CuDriverFunction("cuTexRefSetAddress",3020,0,reinterpret_cast<void*>(&cuTexRefSetAddress_v3020)) },
	{"cuTexRefSetAddress2D_v4010",CuDriverFunction("cuTexRefSetAddress2D",4010,0,reinterpret_cast<void*>(&cuTexRefSetAddress2D_v4010)) },
	{"cuTexRefSetFormat_v2000",CuDriverFunction("cuTexRefSetFormat",2000,0,reinterpret_cast<void*>(&cuTexRefSetFormat_v2000)) },
	{"cuTexRefSetAddressMode_v2000",CuDriverFunction("cuTexRefSetAddressMode",2000,0,reinterpret_cast<void*>(&cuTexRefSetAddressMode_v2000)) },
	{"cuTexRefSetFilterMode_v2000",CuDriverFunction("cuTexRefSetFilterMode",2000,0,reinterpret_cast<void*>(&cuTexRefSetFilterMode_v2000)) },
	{"cuTexRefSetMipmapFilterMode_v5000",CuDriverFunction("cuTexRefSetMipmapFilterMode",5000,0,reinterpret_cast<void*>(&cuTexRefSetMipmapFilterMode_v5000)) },
	{"cuTexRefSetMipmapLevelBias_v5000",CuDriverFunction("cuTexRefSetMipmapLevelBias",5000,0,reinterpret_cast<void*>(&cuTexRefSetMipmapLevelBias_v5000)) },
	{"cuTexRefSetMipmapLevelClamp_v5000",CuDriverFunction("cuTexRefSetMipmapLevelClamp",5000,0,reinterpret_cast<void*>(&cuTexRefSetMipmapLevelClamp_v5000)) },
	{"cuTexRefSetMaxAnisotropy_v5000",CuDriverFunction("cuTexRefSetMaxAnisotropy",5000,0,reinterpret_cast<void*>(&cuTexRefSetMaxAnisotropy_v5000)) },
	{"cuTexRefSetBorderColor_v8000",CuDriverFunction("cuTexRefSetBorderColor",8000,0,reinterpret_cast<void*>(&cuTexRefSetBorderColor_v8000)) },
	{"cuTexRefSetFlags_v2000",CuDriverFunction("cuTexRefSetFlags",2000,0,reinterpret_cast<void*>(&cuTexRefSetFlags_v2000)) },
	{"cuTexRefGetAddress_v3020",CuDriverFunction("cuTexRefGetAddress",3020,0,reinterpret_cast<void*>(&cuTexRefGetAddress_v3020)) },
	{"cuTexRefGetArray_v2000",CuDriverFunction("cuTexRefGetArray",2000,0,reinterpret_cast<void*>(&cuTexRefGetArray_v2000)) },
	{"cuTexRefGetMipmappedArray_v5000",CuDriverFunction("cuTexRefGetMipmappedArray",5000,0,reinterpret_cast<void*>(&cuTexRefGetMipmappedArray_v5000)) },
	{"cuTexRefGetAddressMode_v2000",CuDriverFunction("cuTexRefGetAddressMode",2000,0,reinterpret_cast<void*>(&cuTexRefGetAddressMode_v2000)) },
	{"cuTexRefGetFilterMode_v2000",CuDriverFunction("cuTexRefGetFilterMode",2000,0,reinterpret_cast<void*>(&cuTexRefGetFilterMode_v2000)) },
	{"cuTexRefGetFormat_v2000",CuDriverFunction("cuTexRefGetFormat",2000,0,reinterpret_cast<void*>(&cuTexRefGetFormat_v2000)) },
	{"cuTexRefGetMipmapFilterMode_v5000",CuDriverFunction("cuTexRefGetMipmapFilterMode",5000,0,reinterpret_cast<void*>(&cuTexRefGetMipmapFilterMode_v5000)) },
	{"cuTexRefGetMipmapLevelBias_v5000",CuDriverFunction("cuTexRefGetMipmapLevelBias",5000,0,reinterpret_cast<void*>(&cuTexRefGetMipmapLevelBias_v5000)) },
	{"cuTexRefGetMipmapLevelClamp_v5000",CuDriverFunction("cuTexRefGetMipmapLevelClamp",5000,0,reinterpret_cast<void*>(&cuTexRefGetMipmapLevelClamp_v5000)) },
	{"cuTexRefGetMaxAnisotropy_v5000",CuDriverFunction("cuTexRefGetMaxAnisotropy",5000,0,reinterpret_cast<void*>(&cuTexRefGetMaxAnisotropy_v5000)) },
	{"cuTexRefGetBorderColor_v8000",CuDriverFunction("cuTexRefGetBorderColor",8000,0,reinterpret_cast<void*>(&cuTexRefGetBorderColor_v8000)) },
	{"cuTexRefGetFlags_v2000",CuDriverFunction("cuTexRefGetFlags",2000,0,reinterpret_cast<void*>(&cuTexRefGetFlags_v2000)) },
	{"cuTexRefCreate_v2000",CuDriverFunction("cuTexRefCreate",2000,0,reinterpret_cast<void*>(&cuTexRefCreate_v2000)) },
	{"cuTexRefDestroy_v2000",CuDriverFunction("cuTexRefDestroy",2000,0,reinterpret_cast<void*>(&cuTexRefDestroy_v2000)) },
	{"cuSurfRefSetArray_v3000",CuDriverFunction("cuSurfRefSetArray",3000,0,reinterpret_cast<void*>(&cuSurfRefSetArray_v3000)) },
	{"cuSurfRefGetArray_v3000",CuDriverFunction("cuSurfRefGetArray",3000,0,reinterpret_cast<void*>(&cuSurfRefGetArray_v3000)) },
	{"cuTexObjectCreate_v5000",CuDriverFunction("cuTexObjectCreate",5000,0,reinterpret_cast<void*>(&cuTexObjectCreate_v5000)) },
	{"cuTexObjectDestroy_v5000",CuDriverFunction("cuTexObjectDestroy",5000,0,reinterpret_cast<void*>(&cuTexObjectDestroy_v5000)) },
	{"cuTexObjectGetResourceDesc_v5000",CuDriverFunction("cuTexObjectGetResourceDesc",5000,0,reinterpret_cast<void*>(&cuTexObjectGetResourceDesc_v5000)) },
	{"cuTexObjectGetTextureDesc_v5000",CuDriverFunction("cuTexObjectGetTextureDesc",5000,0,reinterpret_cast<void*>(&cuTexObjectGetTextureDesc_v5000)) },
	{"cuTexObjectGetResourceViewDesc_v5000",CuDriverFunction("cuTexObjectGetResourceViewDesc",5000,0,reinterpret_cast<void*>(&cuTexObjectGetResourceViewDesc_v5000)) },
	{"cuSurfObjectCreate_v5000",CuDriverFunction("cuSurfObjectCreate",5000,0,reinterpret_cast<void*>(&cuSurfObjectCreate_v5000)) },
	{"cuSurfObjectDestroy_v5000",CuDriverFunction("cuSurfObjectDestroy",5000,0,reinterpret_cast<void*>(&cuSurfObjectDestroy_v5000)) },
	{"cuSurfObjectGetResourceDesc_v5000",CuDriverFunction("cuSurfObjectGetResourceDesc",5000,0,reinterpret_cast<void*>(&cuSurfObjectGetResourceDesc_v5000)) },
	{"cuTensorMapEncodeTiled_v12000",CuDriverFunction("cuTensorMapEncodeTiled",12000,0,reinterpret_cast<void*>(&cuTensorMapEncodeTiled_v12000)) },
	{"cuTensorMapEncodeIm2col_v12000",CuDriverFunction("cuTensorMapEncodeIm2col",12000,0,reinterpret_cast<void*>(&cuTensorMapEncodeIm2col_v12000)) },
	{"cuTensorMapReplaceAddress_v12000",CuDriverFunction("cuTensorMapReplaceAddress",12000,0,reinterpret_cast<void*>(&cuTensorMapReplaceAddress_v12000)) },
	{"cuDeviceCanAccessPeer_v4000",CuDriverFunction("cuDeviceCanAccessPeer",4000,0,reinterpret_cast<void*>(&cuDeviceCanAccessPeer_v4000)) },
	{"cuCtxEnablePeerAccess_v4000",CuDriverFunction("cuCtxEnablePeerAccess",4000,0,reinterpret_cast<void*>(&cuCtxEnablePeerAccess_v4000)) },
	{"cuCtxDisablePeerAccess_v4000",CuDriverFunction("cuCtxDisablePeerAccess",4000,0,reinterpret_cast<void*>(&cuCtxDisablePeerAccess_v4000)) },
	{"cuDeviceGetP2PAttribute_v8000",CuDriverFunction("cuDeviceGetP2PAttribute",8000,0,reinterpret_cast<void*>(&cuDeviceGetP2PAttribute_v8000)) },
	{"cuGraphicsUnregisterResource_v3000",CuDriverFunction("cuGraphicsUnregisterResource",3000,0,reinterpret_cast<void*>(&cuGraphicsUnregisterResource_v3000)) },
	{"cuGraphicsSubResourceGetMappedArray_v3000",CuDriverFunction("cuGraphicsSubResourceGetMappedArray",3000,0,reinterpret_cast<void*>(&cuGraphicsSubResourceGetMappedArray_v3000)) },
	{"cuGraphicsResourceGetMappedMipmappedArray_v5000",CuDriverFunction("cuGraphicsResourceGetMappedMipmappedArray",5000,0,reinterpret_cast<void*>(&cuGraphicsResourceGetMappedMipmappedArray_v5000)) },
	{"cuGraphicsResourceGetMappedPointer_v3020",CuDriverFunction("cuGraphicsResourceGetMappedPointer",3020,0,reinterpret_cast<void*>(&cuGraphicsResourceGetMappedPointer_v3020)) },
	{"cuGraphicsResourceSetMapFlags_v6050",CuDriverFunction("cuGraphicsResourceSetMapFlags",6050,0,reinterpret_cast<void*>(&cuGraphicsResourceSetMapFlags_v6050)) },
	{"cuGraphicsMapResources_v7000_ptsz",CuDriverFunction("cuGraphicsMapResources",7000,2,reinterpret_cast<void*>(&cuGraphicsMapResources_v7000_ptsz)) },
	{"cuGraphicsUnmapResources_v7000_ptsz",CuDriverFunction("cuGraphicsUnmapResources",7000,2,reinterpret_cast<void*>(&cuGraphicsUnmapResources_v7000_ptsz)) },
	{"cuGetExportTable_v3000",CuDriverFunction("cuGetExportTable",3000,0,reinterpret_cast<void*>(&cuGetExportTable_v3000)) },
	{"cuFuncGetModule_v11000",CuDriverFunction("cuFuncGetModule",11000,0,reinterpret_cast<void*>(&cuFuncGetModule_v11000)) },
	{"cuGetProcAddress_v11030",CuDriverFunction("cuGetProcAddress",11030,0,reinterpret_cast<void*>(&cuGetProcAddress_v11030)) },
	{"cuGetProcAddress_v12000",CuDriverFunction("cuGetProcAddress",12000,0,reinterpret_cast<void*>(&cuGetProcAddress_v12000)) },
	{"cuMemcpyHtoD_v3020",CuDriverFunction("cuMemcpyHtoD",3020,0,reinterpret_cast<void*>(&cuMemcpyHtoD_v3020)) },
	{"cuMemcpyDtoH_v3020",CuDriverFunction("cuMemcpyDtoH",3020,0,reinterpret_cast<void*>(&cuMemcpyDtoH_v3020)) },
	{"cuMemcpyDtoD_v3020",CuDriverFunction("cuMemcpyDtoD",3020,0,reinterpret_cast<void*>(&cuMemcpyDtoD_v3020)) },
	{"cuMemcpyDtoA_v3020",CuDriverFunction("cuMemcpyDtoA",3020,0,reinterpret_cast<void*>(&cuMemcpyDtoA_v3020)) },
	{"cuMemcpyAtoD_v3020",CuDriverFunction("cuMemcpyAtoD",3020,0,reinterpret_cast<void*>(&cuMemcpyAtoD_v3020)) },
	{"cuMemcpyHtoA_v3020",CuDriverFunction("cuMemcpyHtoA",3020,0,reinterpret_cast<void*>(&cuMemcpyHtoA_v3020)) },
	{"cuMemcpyAtoH_v3020",CuDriverFunction("cuMemcpyAtoH",3020,0,reinterpret_cast<void*>(&cuMemcpyAtoH_v3020)) },
	{"cuMemcpyAtoA_v3020",CuDriverFunction("cuMemcpyAtoA",3020,0,reinterpret_cast<void*>(&cuMemcpyAtoA_v3020)) },
	{"cuMemcpyHtoAAsync_v3020",CuDriverFunction("cuMemcpyHtoAAsync",3020,0,reinterpret_cast<void*>(&cuMemcpyHtoAAsync_v3020)) },
	{"cuMemcpyAtoHAsync_v3020",CuDriverFunction("cuMemcpyAtoHAsync",3020,0,reinterpret_cast<void*>(&cuMemcpyAtoHAsync_v3020)) },
	{"cuMemcpy2D_v3020",CuDriverFunction("cuMemcpy2D",3020,0,reinterpret_cast<void*>(&cuMemcpy2D_v3020)) },
	{"cuMemcpy2DUnaligned_v3020",CuDriverFunction("cuMemcpy2DUnaligned",3020,0,reinterpret_cast<void*>(&cuMemcpy2DUnaligned_v3020)) },
	{"cuMemcpy3D_v3020",CuDriverFunction("cuMemcpy3D",3020,0,reinterpret_cast<void*>(&cuMemcpy3D_v3020)) },
	{"cuMemcpyHtoDAsync_v3020",CuDriverFunction("cuMemcpyHtoDAsync",3020,0,reinterpret_cast<void*>(&cuMemcpyHtoDAsync_v3020)) },
	{"cuMemcpyDtoHAsync_v3020",CuDriverFunction("cuMemcpyDtoHAsync",3020,0,reinterpret_cast<void*>(&cuMemcpyDtoHAsync_v3020)) },
	{"cuMemcpyDtoDAsync_v3020",CuDriverFunction("cuMemcpyDtoDAsync",3020,0,reinterpret_cast<void*>(&cuMemcpyDtoDAsync_v3020)) },
	{"cuMemcpy2DAsync_v3020",CuDriverFunction("cuMemcpy2DAsync",3020,0,reinterpret_cast<void*>(&cuMemcpy2DAsync_v3020)) },
	{"cuMemcpy3DAsync_v3020",CuDriverFunction("cuMemcpy3DAsync",3020,0,reinterpret_cast<void*>(&cuMemcpy3DAsync_v3020)) },
	{"cuMemsetD8_v3020",CuDriverFunction("cuMemsetD8",3020,0,reinterpret_cast<void*>(&cuMemsetD8_v3020)) },
	{"cuMemsetD16_v3020",CuDriverFunction("cuMemsetD16",3020,0,reinterpret_cast<void*>(&cuMemsetD16_v3020)) },
	{"cuMemsetD32_v3020",CuDriverFunction("cuMemsetD32",3020,0,reinterpret_cast<void*>(&cuMemsetD32_v3020)) },
	{"cuMemsetD2D8_v3020",CuDriverFunction("cuMemsetD2D8",3020,0,reinterpret_cast<void*>(&cuMemsetD2D8_v3020)) },
	{"cuMemsetD2D16_v3020",CuDriverFunction("cuMemsetD2D16",3020,0,reinterpret_cast<void*>(&cuMemsetD2D16_v3020)) },
	{"cuMemsetD2D32_v3020",CuDriverFunction("cuMemsetD2D32",3020,0,reinterpret_cast<void*>(&cuMemsetD2D32_v3020)) },
	{"cuMemcpy_v4000",CuDriverFunction("cuMemcpy",4000,0,reinterpret_cast<void*>(&cuMemcpy_v4000)) },
	{"cuMemcpyAsync_v4000",CuDriverFunction("cuMemcpyAsync",4000,0,reinterpret_cast<void*>(&cuMemcpyAsync_v4000)) },
	{"cuMemcpyPeer_v4000",CuDriverFunction("cuMemcpyPeer",4000,0,reinterpret_cast<void*>(&cuMemcpyPeer_v4000)) },
	{"cuMemcpyPeerAsync_v4000",CuDriverFunction("cuMemcpyPeerAsync",4000,0,reinterpret_cast<void*>(&cuMemcpyPeerAsync_v4000)) },
	{"cuMemcpy3DPeer_v4000",CuDriverFunction("cuMemcpy3DPeer",4000,0,reinterpret_cast<void*>(&cuMemcpy3DPeer_v4000)) },
	{"cuMemcpy3DPeerAsync_v4000",CuDriverFunction("cuMemcpy3DPeerAsync",4000,0,reinterpret_cast<void*>(&cuMemcpy3DPeerAsync_v4000)) },
	{"cuMemsetD8Async_v3020",CuDriverFunction("cuMemsetD8Async",3020,0,reinterpret_cast<void*>(&cuMemsetD8Async_v3020)) },
	{"cuMemsetD16Async_v3020",CuDriverFunction("cuMemsetD16Async",3020,0,reinterpret_cast<void*>(&cuMemsetD16Async_v3020)) },
	{"cuMemsetD32Async_v3020",CuDriverFunction("cuMemsetD32Async",3020,0,reinterpret_cast<void*>(&cuMemsetD32Async_v3020)) },
	{"cuMemsetD2D8Async_v3020",CuDriverFunction("cuMemsetD2D8Async",3020,0,reinterpret_cast<void*>(&cuMemsetD2D8Async_v3020)) },
	{"cuMemsetD2D16Async_v3020",CuDriverFunction("cuMemsetD2D16Async",3020,0,reinterpret_cast<void*>(&cuMemsetD2D16Async_v3020)) },
	{"cuMemsetD2D32Async_v3020",CuDriverFunction("cuMemsetD2D32Async",3020,0,reinterpret_cast<void*>(&cuMemsetD2D32Async_v3020)) },
	{"cuStreamGetPriority_v5050",CuDriverFunction("cuStreamGetPriority",5050,0,reinterpret_cast<void*>(&cuStreamGetPriority_v5050)) },
	{"cuStreamGetFlags_v5050",CuDriverFunction("cuStreamGetFlags",5050,0,reinterpret_cast<void*>(&cuStreamGetFlags_v5050)) },
	{"cuStreamGetCtx_v9020",CuDriverFunction("cuStreamGetCtx",9020,0,reinterpret_cast<void*>(&cuStreamGetCtx_v9020)) },
	{"cuStreamWaitEvent_v3020",CuDriverFunction("cuStreamWaitEvent",3020,0,reinterpret_cast<void*>(&cuStreamWaitEvent_v3020)) },
	{"cuStreamAddCallback_v5000",CuDriverFunction("cuStreamAddCallback",5000,0,reinterpret_cast<void*>(&cuStreamAddCallback_v5000)) },
	{"cuStreamAttachMemAsync_v6000",CuDriverFunction("cuStreamAttachMemAsync",6000,0,reinterpret_cast<void*>(&cuStreamAttachMemAsync_v6000)) },
	{"cuStreamQuery_v2000",CuDriverFunction("cuStreamQuery",2000,0,reinterpret_cast<void*>(&cuStreamQuery_v2000)) },
	{"cuStreamSynchronize_v2000",CuDriverFunction("cuStreamSynchronize",2000,0,reinterpret_cast<void*>(&cuStreamSynchronize_v2000)) },
	{"cuEventRecord_v2000",CuDriverFunction("cuEventRecord",2000,0,reinterpret_cast<void*>(&cuEventRecord_v2000)) },
	{"cuEventRecordWithFlags_v11010",CuDriverFunction("cuEventRecordWithFlags",11010,0,reinterpret_cast<void*>(&cuEventRecordWithFlags_v11010)) },
	{"cuLaunchKernel_v4000",CuDriverFunction("cuLaunchKernel",4000,0,reinterpret_cast<void*>(&cuLaunchKernel_v4000)) },
	{"cuLaunchKernelEx_v11060",CuDriverFunction("cuLaunchKernelEx",11060,0,reinterpret_cast<void*>(&cuLaunchKernelEx_v11060)) },
	{"cuLaunchHostFunc_v10000",CuDriverFunction("cuLaunchHostFunc",10000,0,reinterpret_cast<void*>(&cuLaunchHostFunc_v10000)) },
	{"cuGraphicsMapResources_v3000",CuDriverFunction("cuGraphicsMapResources",3000,0,reinterpret_cast<void*>(&cuGraphicsMapResources_v3000)) },
	{"cuGraphicsUnmapResources_v3000",CuDriverFunction("cuGraphicsUnmapResources",3000,0,reinterpret_cast<void*>(&cuGraphicsUnmapResources_v3000)) },
	{"cuStreamWriteValue32_v8000",CuDriverFunction("cuStreamWriteValue32",8000,0,reinterpret_cast<void*>(&cuStreamWriteValue32_v8000)) },
	{"cuStreamWaitValue32_v8000",CuDriverFunction("cuStreamWaitValue32",8000,0,reinterpret_cast<void*>(&cuStreamWaitValue32_v8000)) },
	{"cuStreamWriteValue64_v9000",CuDriverFunction("cuStreamWriteValue64",9000,0,reinterpret_cast<void*>(&cuStreamWriteValue64_v9000)) },
	{"cuStreamWaitValue64_v9000",CuDriverFunction("cuStreamWaitValue64",9000,0,reinterpret_cast<void*>(&cuStreamWaitValue64_v9000)) },
	{"cuStreamBatchMemOp_v8000",CuDriverFunction("cuStreamBatchMemOp",8000,0,reinterpret_cast<void*>(&cuStreamBatchMemOp_v8000)) },
	{"cuStreamWriteValue32_v11070",CuDriverFunction("cuStreamWriteValue32",11070,0,reinterpret_cast<void*>(&cuStreamWriteValue32_v11070)) },
	{"cuStreamWaitValue32_v11070",CuDriverFunction("cuStreamWaitValue32",11070,0,reinterpret_cast<void*>(&cuStreamWaitValue32_v11070)) },
	{"cuStreamWriteValue64_v11070",CuDriverFunction("cuStreamWriteValue64",11070,0,reinterpret_cast<void*>(&cuStreamWriteValue64_v11070)) },
	{"cuStreamWaitValue64_v11070",CuDriverFunction("cuStreamWaitValue64",11070,0,reinterpret_cast<void*>(&cuStreamWaitValue64_v11070)) },
	{"cuStreamBatchMemOp_v11070",CuDriverFunction("cuStreamBatchMemOp",11070,0,reinterpret_cast<void*>(&cuStreamBatchMemOp_v11070)) },
	{"cuMemPrefetchAsync_v8000",CuDriverFunction("cuMemPrefetchAsync",8000,0,reinterpret_cast<void*>(&cuMemPrefetchAsync_v8000)) },
	{"cuMemPrefetchAsync_v12020",CuDriverFunction("cuMemPrefetchAsync",12020,0,reinterpret_cast<void*>(&cuMemPrefetchAsync_v12020)) },
	{"cuLaunchCooperativeKernel_v9000",CuDriverFunction("cuLaunchCooperativeKernel",9000,0,reinterpret_cast<void*>(&cuLaunchCooperativeKernel_v9000)) },
	{"cuSignalExternalSemaphoresAsync_v10000",CuDriverFunction("cuSignalExternalSemaphoresAsync",10000,0,reinterpret_cast<void*>(&cuSignalExternalSemaphoresAsync_v10000)) },
	{"cuWaitExternalSemaphoresAsync_v10000",CuDriverFunction("cuWaitExternalSemaphoresAsync",10000,0,reinterpret_cast<void*>(&cuWaitExternalSemaphoresAsync_v10000)) },
	{"cuStreamBeginCapture_v10010",CuDriverFunction("cuStreamBeginCapture",10010,0,reinterpret_cast<void*>(&cuStreamBeginCapture_v10010)) },
	{"cuStreamBeginCaptureToGraph_v12030",CuDriverFunction("cuStreamBeginCaptureToGraph",12030,0,reinterpret_cast<void*>(&cuStreamBeginCaptureToGraph_v12030)) },
	{"cuStreamEndCapture_v10000",CuDriverFunction("cuStreamEndCapture",10000,0,reinterpret_cast<void*>(&cuStreamEndCapture_v10000)) },
	{"cuStreamIsCapturing_v10000",CuDriverFunction("cuStreamIsCapturing",10000,0,reinterpret_cast<void*>(&cuStreamIsCapturing_v10000)) },
	{"cuStreamGetCaptureInfo_v10010",CuDriverFunction("cuStreamGetCaptureInfo",10010,0,reinterpret_cast<void*>(&cuStreamGetCaptureInfo_v10010)) },
	{"cuStreamGetCaptureInfo_v11030",CuDriverFunction("cuStreamGetCaptureInfo",11030,0,reinterpret_cast<void*>(&cuStreamGetCaptureInfo_v11030)) },
	{"cuStreamGetCaptureInfo_v12030",CuDriverFunction("cuStreamGetCaptureInfo",12030,0,reinterpret_cast<void*>(&cuStreamGetCaptureInfo_v12030)) },
	{"cuStreamUpdateCaptureDependencies_v11030",CuDriverFunction("cuStreamUpdateCaptureDependencies",11030,0,reinterpret_cast<void*>(&cuStreamUpdateCaptureDependencies_v11030)) },
	{"cuStreamUpdateCaptureDependencies_v12030",CuDriverFunction("cuStreamUpdateCaptureDependencies",12030,0,reinterpret_cast<void*>(&cuStreamUpdateCaptureDependencies_v12030)) },
	{"cuGraphInstantiateWithParams_v12000",CuDriverFunction("cuGraphInstantiateWithParams",12000,0,reinterpret_cast<void*>(&cuGraphInstantiateWithParams_v12000)) },
	{"cuGraphUpload_v11010",CuDriverFunction("cuGraphUpload",11010,0,reinterpret_cast<void*>(&cuGraphUpload_v11010)) },
	{"cuGraphLaunch_v10000",CuDriverFunction("cuGraphLaunch",10000,0,reinterpret_cast<void*>(&cuGraphLaunch_v10000)) },
	{"cuStreamCopyAttributes_v11000",CuDriverFunction("cuStreamCopyAttributes",11000,0,reinterpret_cast<void*>(&cuStreamCopyAttributes_v11000)) },
	{"cuStreamGetAttribute_v11000",CuDriverFunction("cuStreamGetAttribute",11000,0,reinterpret_cast<void*>(&cuStreamGetAttribute_v11000)) },
	{"cuStreamSetAttribute_v11000",CuDriverFunction("cuStreamSetAttribute",11000,0,reinterpret_cast<void*>(&cuStreamSetAttribute_v11000)) },
	{"cuMemMapArrayAsync_v11010",CuDriverFunction("cuMemMapArrayAsync",11010,0,reinterpret_cast<void*>(&cuMemMapArrayAsync_v11010)) },
	{"cuMemFreeAsync_v11020",CuDriverFunction("cuMemFreeAsync",11020,0,reinterpret_cast<void*>(&cuMemFreeAsync_v11020)) },
	{"cuMemAllocAsync_v11020",CuDriverFunction("cuMemAllocAsync",11020,0,reinterpret_cast<void*>(&cuMemAllocAsync_v11020)) },
	{"cuMemAllocFromPoolAsync_v11020",CuDriverFunction("cuMemAllocFromPoolAsync",11020,0,reinterpret_cast<void*>(&cuMemAllocFromPoolAsync_v11020)) },
	{"cuFlushGPUDirectRDMAWrites_v11030",CuDriverFunction("cuFlushGPUDirectRDMAWrites",11030,0,reinterpret_cast<void*>(&cuFlushGPUDirectRDMAWrites_v11030)) },
	{"cuUserObjectCreate_v11030",CuDriverFunction("cuUserObjectCreate",11030,0,reinterpret_cast<void*>(&cuUserObjectCreate_v11030)) },
	{"cuUserObjectRetain_v11030",CuDriverFunction("cuUserObjectRetain",11030,0,reinterpret_cast<void*>(&cuUserObjectRetain_v11030)) },
	{"cuUserObjectRelease_v11030",CuDriverFunction("cuUserObjectRelease",11030,0,reinterpret_cast<void*>(&cuUserObjectRelease_v11030)) },
	{"cuGraphRetainUserObject_v11030",CuDriverFunction("cuGraphRetainUserObject",11030,0,reinterpret_cast<void*>(&cuGraphRetainUserObject_v11030)) },
	{"cuGraphReleaseUserObject_v11030",CuDriverFunction("cuGraphReleaseUserObject",11030,0,reinterpret_cast<void*>(&cuGraphReleaseUserObject_v11030)) },
	{"cuModuleGetLoadingMode_v11070",CuDriverFunction("cuModuleGetLoadingMode",11070,0,reinterpret_cast<void*>(&cuModuleGetLoadingMode_v11070)) },
	{"cuMemGetHandleForAddressRange_v11070",CuDriverFunction("cuMemGetHandleForAddressRange",11070,0,reinterpret_cast<void*>(&cuMemGetHandleForAddressRange_v11070)) },
	{"cuLibraryLoadData_v12000",CuDriverFunction("cuLibraryLoadData",12000,0,reinterpret_cast<void*>(&cuLibraryLoadData_v12000)) },
	{"cuLibraryLoadFromFile_v12000",CuDriverFunction("cuLibraryLoadFromFile",12000,0,reinterpret_cast<void*>(&cuLibraryLoadFromFile_v12000)) },
	{"cuLibraryUnload_v12000",CuDriverFunction("cuLibraryUnload",12000,0,reinterpret_cast<void*>(&cuLibraryUnload_v12000)) },
	{"cuLibraryGetKernel_v12000",CuDriverFunction("cuLibraryGetKernel",12000,0,reinterpret_cast<void*>(&cuLibraryGetKernel_v12000)) },
	{"cuLibraryGetModule_v12000",CuDriverFunction("cuLibraryGetModule",12000,0,reinterpret_cast<void*>(&cuLibraryGetModule_v12000)) },
	{"cuLibraryGetKernelCount",CuDriverFunction("cuLibraryGetKernelCount",0,0,reinterpret_cast<void*>(&cuLibraryGetKernelCount)) },
	{"cuLibraryEnumerateKernels",CuDriverFunction("cuLibraryEnumerateKernels",0,0,reinterpret_cast<void*>(&cuLibraryEnumerateKernels)) },
	{"cuKernelGetFunction_v12000",CuDriverFunction("cuKernelGetFunction",12000,0,reinterpret_cast<void*>(&cuKernelGetFunction_v12000)) },
	{"cuLibraryGetGlobal_v12000",CuDriverFunction("cuLibraryGetGlobal",12000,0,reinterpret_cast<void*>(&cuLibraryGetGlobal_v12000)) },
	{"cuLibraryGetManaged_v12000",CuDriverFunction("cuLibraryGetManaged",12000,0,reinterpret_cast<void*>(&cuLibraryGetManaged_v12000)) },
	{"cuKernelGetAttribute_v12000",CuDriverFunction("cuKernelGetAttribute",12000,0,reinterpret_cast<void*>(&cuKernelGetAttribute_v12000)) },
	{"cuKernelSetAttribute_v12000",CuDriverFunction("cuKernelSetAttribute",12000,0,reinterpret_cast<void*>(&cuKernelSetAttribute_v12000)) },
	{"cuKernelSetCacheConfig_v12000",CuDriverFunction("cuKernelSetCacheConfig",12000,0,reinterpret_cast<void*>(&cuKernelSetCacheConfig_v12000)) },
	{"cuKernelGetName_v12030",CuDriverFunction("cuKernelGetName",12030,0,reinterpret_cast<void*>(&cuKernelGetName_v12030)) },
	{"cuKernelGetParamInfo_v12040",CuDriverFunction("cuKernelGetParamInfo",12040,0,reinterpret_cast<void*>(&cuKernelGetParamInfo_v12040)) },
	{"cuLibraryGetUnifiedFunction_v12000",CuDriverFunction("cuLibraryGetUnifiedFunction",12000,0,reinterpret_cast<void*>(&cuLibraryGetUnifiedFunction_v12000)) },
	{"cuCoredumpGetAttribute_v12010",CuDriverFunction("cuCoredumpGetAttribute",12010,0,reinterpret_cast<void*>(&cuCoredumpGetAttribute_v12010)) },
	{"cuCoredumpGetAttributeGlobal_v12010",CuDriverFunction("cuCoredumpGetAttributeGlobal",12010,0,reinterpret_cast<void*>(&cuCoredumpGetAttributeGlobal_v12010)) },
	{"cuCoredumpSetAttribute_v12010",CuDriverFunction("cuCoredumpSetAttribute",12010,0,reinterpret_cast<void*>(&cuCoredumpSetAttribute_v12010)) },
	{"cuCoredumpSetAttributeGlobal_v12010",CuDriverFunction("cuCoredumpSetAttributeGlobal",12010,0,reinterpret_cast<void*>(&cuCoredumpSetAttributeGlobal_v12010)) },
	{"cuDeviceRegisterAsyncNotification_v12040",CuDriverFunction("cuDeviceRegisterAsyncNotification",12040,0,reinterpret_cast<void*>(&cuDeviceRegisterAsyncNotification_v12040)) },
	{"cuDeviceUnregisterAsyncNotification_v12040",CuDriverFunction("cuDeviceUnregisterAsyncNotification",12040,0,reinterpret_cast<void*>(&cuDeviceUnregisterAsyncNotification_v12040)) },
	{"cuGreenCtxCreate_v12040",CuDriverFunction("cuGreenCtxCreate",12040,0,reinterpret_cast<void*>(&cuGreenCtxCreate_v12040)) },
	{"cuGreenCtxDestroy_v12040",CuDriverFunction("cuGreenCtxDestroy",12040,0,reinterpret_cast<void*>(&cuGreenCtxDestroy_v12040)) },
	{"cuDeviceGetDevResource_v12040",CuDriverFunction("cuDeviceGetDevResource",12040,0,reinterpret_cast<void*>(&cuDeviceGetDevResource_v12040)) },
	{"cuCtxGetDevResource_v12040",CuDriverFunction("cuCtxGetDevResource",12040,0,reinterpret_cast<void*>(&cuCtxGetDevResource_v12040)) },
	{"cuGreenCtxGetDevResource_v12040",CuDriverFunction("cuGreenCtxGetDevResource",12040,0,reinterpret_cast<void*>(&cuGreenCtxGetDevResource_v12040)) },
	{"cuGreenCtxRecordEvent_v12040",CuDriverFunction("cuGreenCtxRecordEvent",12040,0,reinterpret_cast<void*>(&cuGreenCtxRecordEvent_v12040)) },
	{"cuGreenCtxWaitEvent_v12040",CuDriverFunction("cuGreenCtxWaitEvent",12040,0,reinterpret_cast<void*>(&cuGreenCtxWaitEvent_v12040)) },
	{"cuDevResourceGenerateDesc_v12040",CuDriverFunction("cuDevResourceGenerateDesc",12040,0,reinterpret_cast<void*>(&cuDevResourceGenerateDesc_v12040)) },
	{"cuDevSmResourceSplitByCount_v12040",CuDriverFunction("cuDevSmResourceSplitByCount",12040,0,reinterpret_cast<void*>(&cuDevSmResourceSplitByCount_v12040)) },
	{"cuStreamGetGreenCtx_v12040",CuDriverFunction("cuStreamGetGreenCtx",12040,0,reinterpret_cast<void*>(&cuStreamGetGreenCtx_v12040)) },
	{"cuCtxFromGreenCtx_v12040",CuDriverFunction("cuCtxFromGreenCtx",12040,0,reinterpret_cast<void*>(&cuCtxFromGreenCtx_v12040)) },
	{"cuMemHostRegister_v4000",CuDriverFunction("cuMemHostRegister",4000,0,reinterpret_cast<void*>(&cuMemHostRegister_v4000)) },
	{"cuGraphicsResourceSetMapFlags_v3000",CuDriverFunction("cuGraphicsResourceSetMapFlags",3000,0,reinterpret_cast<void*>(&cuGraphicsResourceSetMapFlags_v3000)) },
	{"cuLinkCreate_v5050",CuDriverFunction("cuLinkCreate",5050,0,reinterpret_cast<void*>(&cuLinkCreate_v5050)) },
	{"cuLinkAddData_v5050",CuDriverFunction("cuLinkAddData",5050,0,reinterpret_cast<void*>(&cuLinkAddData_v5050)) },
	{"cuLinkAddFile_v5050",CuDriverFunction("cuLinkAddFile",5050,0,reinterpret_cast<void*>(&cuLinkAddFile_v5050)) },
	{"cuTexRefSetAddress2D_v3020",CuDriverFunction("cuTexRefSetAddress2D",3020,0,reinterpret_cast<void*>(&cuTexRefSetAddress2D_v3020)) },
	{"cuDeviceTotalMem_v2000",CuDriverFunction("cuDeviceTotalMem",2000,0,reinterpret_cast<void*>(&cuDeviceTotalMem_v2000)) },
	{"cuCtxCreate_v2000",CuDriverFunction("cuCtxCreate",2000,0,reinterpret_cast<void*>(&cuCtxCreate_v2000)) },
	{"cuModuleGetGlobal_v2000",CuDriverFunction("cuModuleGetGlobal",2000,0,reinterpret_cast<void*>(&cuModuleGetGlobal_v2000)) },
	{"cuMemGetInfo_v2000",CuDriverFunction("cuMemGetInfo",2000,0,reinterpret_cast<void*>(&cuMemGetInfo_v2000)) },
	{"cuMemAlloc_v2000",CuDriverFunction("cuMemAlloc",2000,0,reinterpret_cast<void*>(&cuMemAlloc_v2000)) },
	{"cuMemAllocPitch_v2000",CuDriverFunction("cuMemAllocPitch",2000,0,reinterpret_cast<void*>(&cuMemAllocPitch_v2000)) },
	{"cuMemFree_v2000",CuDriverFunction("cuMemFree",2000,0,reinterpret_cast<void*>(&cuMemFree_v2000)) },
	{"cuMemGetAddressRange_v2000",CuDriverFunction("cuMemGetAddressRange",2000,0,reinterpret_cast<void*>(&cuMemGetAddressRange_v2000)) },
	{"cuMemAllocHost_v2000",CuDriverFunction("cuMemAllocHost",2000,0,reinterpret_cast<void*>(&cuMemAllocHost_v2000)) },
	{"cuMemHostGetDevicePointer_v2020",CuDriverFunction("cuMemHostGetDevicePointer",2020,0,reinterpret_cast<void*>(&cuMemHostGetDevicePointer_v2020)) },
	{"cuMemcpyHtoD_v2000",CuDriverFunction("cuMemcpyHtoD",2000,0,reinterpret_cast<void*>(&cuMemcpyHtoD_v2000)) },
	{"cuMemcpyDtoH_v2000",CuDriverFunction("cuMemcpyDtoH",2000,0,reinterpret_cast<void*>(&cuMemcpyDtoH_v2000)) },
	{"cuMemcpyDtoD_v2000",CuDriverFunction("cuMemcpyDtoD",2000,0,reinterpret_cast<void*>(&cuMemcpyDtoD_v2000)) },
	{"cuMemcpyDtoA_v2000",CuDriverFunction("cuMemcpyDtoA",2000,0,reinterpret_cast<void*>(&cuMemcpyDtoA_v2000)) },
	{"cuMemcpyAtoD_v2000",CuDriverFunction("cuMemcpyAtoD",2000,0,reinterpret_cast<void*>(&cuMemcpyAtoD_v2000)) },
	{"cuMemcpyHtoA_v2000",CuDriverFunction("cuMemcpyHtoA",2000,0,reinterpret_cast<void*>(&cuMemcpyHtoA_v2000)) },
	{"cuMemcpyAtoH_v2000",CuDriverFunction("cuMemcpyAtoH",2000,0,reinterpret_cast<void*>(&cuMemcpyAtoH_v2000)) },
	{"cuMemcpyAtoA_v2000",CuDriverFunction("cuMemcpyAtoA",2000,0,reinterpret_cast<void*>(&cuMemcpyAtoA_v2000)) },
	{"cuMemcpyHtoAAsync_v2000",CuDriverFunction("cuMemcpyHtoAAsync",2000,0,reinterpret_cast<void*>(&cuMemcpyHtoAAsync_v2000)) },
	{"cuMemcpyAtoHAsync_v2000",CuDriverFunction("cuMemcpyAtoHAsync",2000,0,reinterpret_cast<void*>(&cuMemcpyAtoHAsync_v2000)) },
	{"cuMemcpy2D_v2000",CuDriverFunction("cuMemcpy2D",2000,0,reinterpret_cast<void*>(&cuMemcpy2D_v2000)) },
	{"cuMemcpy2DUnaligned_v2000",CuDriverFunction("cuMemcpy2DUnaligned",2000,0,reinterpret_cast<void*>(&cuMemcpy2DUnaligned_v2000)) },
	{"cuMemcpy3D_v2000",CuDriverFunction("cuMemcpy3D",2000,0,reinterpret_cast<void*>(&cuMemcpy3D_v2000)) },
	{"cuMemcpyHtoDAsync_v2000",CuDriverFunction("cuMemcpyHtoDAsync",2000,0,reinterpret_cast<void*>(&cuMemcpyHtoDAsync_v2000)) },
	{"cuMemcpyDtoHAsync_v2000",CuDriverFunction("cuMemcpyDtoHAsync",2000,0,reinterpret_cast<void*>(&cuMemcpyDtoHAsync_v2000)) },
	{"cuMemcpyDtoDAsync_v3000",CuDriverFunction("cuMemcpyDtoDAsync",3000,0,reinterpret_cast<void*>(&cuMemcpyDtoDAsync_v3000)) },
	{"cuMemcpy2DAsync_v2000",CuDriverFunction("cuMemcpy2DAsync",2000,0,reinterpret_cast<void*>(&cuMemcpy2DAsync_v2000)) },
	{"cuMemcpy3DAsync_v2000",CuDriverFunction("cuMemcpy3DAsync",2000,0,reinterpret_cast<void*>(&cuMemcpy3DAsync_v2000)) },
	{"cuMemsetD8_v2000",CuDriverFunction("cuMemsetD8",2000,0,reinterpret_cast<void*>(&cuMemsetD8_v2000)) },
	{"cuMemsetD16_v2000",CuDriverFunction("cuMemsetD16",2000,0,reinterpret_cast<void*>(&cuMemsetD16_v2000)) },
	{"cuMemsetD32_v2000",CuDriverFunction("cuMemsetD32",2000,0,reinterpret_cast<void*>(&cuMemsetD32_v2000)) },
	{"cuMemsetD2D8_v2000",CuDriverFunction("cuMemsetD2D8",2000,0,reinterpret_cast<void*>(&cuMemsetD2D8_v2000)) },
	{"cuMemsetD2D16_v2000",CuDriverFunction("cuMemsetD2D16",2000,0,reinterpret_cast<void*>(&cuMemsetD2D16_v2000)) },
	{"cuMemsetD2D32_v2000",CuDriverFunction("cuMemsetD2D32",2000,0,reinterpret_cast<void*>(&cuMemsetD2D32_v2000)) },
	{"cuArrayCreate_v2000",CuDriverFunction("cuArrayCreate",2000,0,reinterpret_cast<void*>(&cuArrayCreate_v2000)) },
	{"cuArrayGetDescriptor_v2000",CuDriverFunction("cuArrayGetDescriptor",2000,0,reinterpret_cast<void*>(&cuArrayGetDescriptor_v2000)) },
	{"cuArray3DCreate_v2000",CuDriverFunction("cuArray3DCreate",2000,0,reinterpret_cast<void*>(&cuArray3DCreate_v2000)) },
	{"cuArray3DGetDescriptor_v2000",CuDriverFunction("cuArray3DGetDescriptor",2000,0,reinterpret_cast<void*>(&cuArray3DGetDescriptor_v2000)) },
	{"cuTexRefSetAddress_v2000",CuDriverFunction("cuTexRefSetAddress",2000,0,reinterpret_cast<void*>(&cuTexRefSetAddress_v2000)) },
	{"cuTexRefSetAddress2D_v2020",CuDriverFunction("cuTexRefSetAddress2D",2020,0,reinterpret_cast<void*>(&cuTexRefSetAddress2D_v2020)) },
	{"cuTexRefGetAddress_v2000",CuDriverFunction("cuTexRefGetAddress",2000,0,reinterpret_cast<void*>(&cuTexRefGetAddress_v2000)) },
	{"cuGraphicsResourceGetMappedPointer_v3000",CuDriverFunction("cuGraphicsResourceGetMappedPointer",3000,0,reinterpret_cast<void*>(&cuGraphicsResourceGetMappedPointer_v3000)) },
	{"cuCtxDestroy_v2000",CuDriverFunction("cuCtxDestroy",2000,0,reinterpret_cast<void*>(&cuCtxDestroy_v2000)) },
	{"cuCtxPopCurrent_v2000",CuDriverFunction("cuCtxPopCurrent",2000,0,reinterpret_cast<void*>(&cuCtxPopCurrent_v2000)) },
	{"cuCtxPushCurrent_v2000",CuDriverFunction("cuCtxPushCurrent",2000,0,reinterpret_cast<void*>(&cuCtxPushCurrent_v2000)) },
	{"cuStreamDestroy_v2000",CuDriverFunction("cuStreamDestroy",2000,0,reinterpret_cast<void*>(&cuStreamDestroy_v2000)) },
	{"cuEventDestroy_v2000",CuDriverFunction("cuEventDestroy",2000,0,reinterpret_cast<void*>(&cuEventDestroy_v2000)) },
	{"cuDevicePrimaryCtxRelease_v7000",CuDriverFunction("cuDevicePrimaryCtxRelease",7000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxRelease_v7000)) },
	{"cuDevicePrimaryCtxReset_v7000",CuDriverFunction("cuDevicePrimaryCtxReset",7000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxReset_v7000)) },
	{"cuDevicePrimaryCtxSetFlags_v7000",CuDriverFunction("cuDevicePrimaryCtxSetFlags",7000,0,reinterpret_cast<void*>(&cuDevicePrimaryCtxSetFlags_v7000)) },
	{"cuStreamBeginCapture_v10000",CuDriverFunction("cuStreamBeginCapture",10000,0,reinterpret_cast<void*>(&cuStreamBeginCapture_v10000)) },
	{"cuStreamBeginCapture_v10000_ptsz",CuDriverFunction("cuStreamBeginCapture",10000,2,reinterpret_cast<void*>(&cuStreamBeginCapture_v10000_ptsz)) },
	{"cuIpcOpenMemHandle_v4010",CuDriverFunction("cuIpcOpenMemHandle",4010,0,reinterpret_cast<void*>(&cuIpcOpenMemHandle_v4010)) },
	{"cuGraphInstantiate_v10000",CuDriverFunction("cuGraphInstantiate",10000,0,reinterpret_cast<void*>(&cuGraphInstantiate_v10000)) },
	{"cuGraphInstantiate_v11000",CuDriverFunction("cuGraphInstantiate",11000,0,reinterpret_cast<void*>(&cuGraphInstantiate_v11000)) },

};




CUresult cuGetProcAddress(const char * symbol, void **pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus) {
    printf("Intercepted cuGetProcAddress: Requesting symbol %s (flags=%lu, version=%d): %p\n", symbol, flags, cudaVersion, *pfn);
	CUresult res = realCuGetProcAddress(symbol, pfn, cudaVersion, flags, symbolStatus);
    if (strcmp(symbol, "cuGetProcAddress") == 0) {
        *pfn = (void*)&cuGetProcAddress;  // 拦截自身
		return CUDA_SUCCESS;
    } 

	std::string funcName=std::string(symbol)+"_v"+std::to_string(cudaVersion);


	if (flags==2){
		auto it = cuDriverFunctionTable.find(funcName+"_ptsz");
		if (it==cuDriverFunctionTable.end()){
			it=cuDriverFunctionTable.find(funcName+"_ptds");
		}
		if (it!=cuDriverFunctionTable.end()){
			*pfn=it->second.funcPtr;
			return CUDA_SUCCESS;
		}
		else{
			printf("CUDA Driver API NOT HOOK: %s\n",funcName.c_str());
		}
	}
	else{

		auto it = cuDriverFunctionTable.find(funcName);
		
		if (it==cuDriverFunctionTable.end()){
			it=cuDriverFunctionTable.find(funcName+"_ptds");
		}
		if (it==cuDriverFunctionTable.end()){
			it=cuDriverFunctionTable.find(funcName+"_ptsz");
		}
		if (it!=cuDriverFunctionTable.end()){
			*pfn=it->second.funcPtr;
			return CUDA_SUCCESS;
		}
		else{

			printf("CUDA Driver API NOT HOOK: %s\n",funcName.c_str());
		}

	}

	return res;
;
}
