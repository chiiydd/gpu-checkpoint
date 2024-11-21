#include<cuda.h>
#include <cstdlib>
#include <cstring>
#include<stdio.h>
#include<communication.h>
#include<sys/socket.h>
#include<sys/un.h>
#include <unistd.h>

#include <string>

std::string to_string(CuDriverCall call) {
    switch (call) {
        case CuDriverCall::CuMemAlloc: return "CuMemAlloc";
        case CuDriverCall::CuMemFree: return "CuMemFree";
        case CuDriverCall::CuMemcpyHtoD: return "CuMemcpyHtoD";
        case CuDriverCall::CuMemcpyDtoH: return "CuMemcpyDtoH";
        case CuDriverCall::CuDriverGetVersion: return "CuDriverGetVersion";
        case CuDriverCall::CuDeviceGet: return "CuDeviceGet";
        case CuDriverCall::CuDeviceGetCount: return "CuDeviceGetCount";
        case CuDriverCall::CuDeviceGetName: return "CuDeviceGetName";
        case CuDriverCall::CuDeviceGetUuid: return "CuDeviceGetUuid";
        case CuDriverCall::CuDeviceTotalMem: return "CuDeviceTotalMem";
        case CuDriverCall::CuGetExportTable: return "CuGetExportTable";
        case CuDriverCall::CuModuleGetLoadingMode: return "CuModuleGetLoadingMode";
        case CuDriverCall::CuDeviceGetAttribute: return "CuDeviceGetAttribute";
        case CuDriverCall::CuCtxGetCurrent: return "CuCtxGetCurrent";
        case CuDriverCall::CuCtxSetCurrent: return "CuCtxSetCurrent";
        case CuDriverCall::CuDevicePrimaryCtxRetain: return "CuDevicePrimaryCtxRetain";
        case CuDriverCall::CuLibraryLoadData: return "CuLibraryLoadData";
        case CuDriverCall::CuLibraryUnload: return "CuLibraryUnload";
        case CuDriverCall::CuDevicePrimaryCtxRelease: return "CuDevicePrimaryCtxRelease";
        case CuDriverCall::CuCtxPushCurrent: return "CuCtxPushCurrent";
        case CuDriverCall::CuCtxPopCurrent: return "CuCtxPopCurrent";
        case CuDriverCall::CuInit: return "CuInit";
        case CuDriverCall::CuCtxCreate: return "CuCtxCreate";
        case CuDriverCall::CuLibraryGetModule: return "CuLibraryGetModule";
        case CuDriverCall::CuModuleGetFunction: return "CuModuleGetFunction";
        case CuDriverCall::CuLaunchKernel: return "CuLaunchKernel";
        default: return "Unknown";
    }
}
void   launch_kernel_proxy(CuDriverCallStructure * request,CuDriverCallReplyStructure * reply,void * parametersMetadata){
    void **cuda_args;
    uint16_t *arg_offsets;
    size_t param_num = *((size_t*)parametersMetadata);
    arg_offsets = (uint16_t*)(parametersMetadata+sizeof(size_t));
    cuda_args = (void **)malloc(param_num*sizeof(void*));
    for (size_t i = 0; i < param_num; ++i) {
        cuda_args[i] = parametersMetadata+sizeof(size_t)+param_num*sizeof(uint16_t)+arg_offsets[i];
    }

    reply->result = cuLaunchKernel(request->params.cuLaunchKernel.f, 
            request->params.cuLaunchKernel.gridDimX,request->params.cuLaunchKernel.gridDimY, request->params.cuLaunchKernel.gridDimZ, 
            request->params.cuLaunchKernel.blockDimX, request->params.cuLaunchKernel.blockDimY, request->params.cuLaunchKernel.blockDimZ,
            request->params.cuLaunchKernel.sharedMemBytes, request->params.cuLaunchKernel.hStream, cuda_args, NULL);
}
CUresult proxy_call(int socket_handle,CuDriverCallStructure *request,CuDriverCallReplyStructure * reply);
int proxy_init(){
    // CUresult result;
    // const char* errorString;
    // // 初始化 CUDA
    // result=cuInit(0);
    // if (result != CUDA_SUCCESS){
    //     cuGetErrorString(result, &errorString);

    //     printf("cuInit failed:%s\n",errorString);
    //     return 1;
    // }
    // CUcontext context;
    // CUdevice cuDevice;
    // cuDeviceGet(&cuDevice, 0);
    // result=cuCtxCreate(&context, 0, cuDevice);

    // if (result != CUDA_SUCCESS){
    //     cuGetErrorString(result, &errorString);
    //     printf("cuCtxCreate failed:%s\n",errorString);
    //     return -1;
    // }
    return 0;
}

void proxy_start(){
    //建立socket server服务
    
    struct sockaddr_un sa_proxy;

    int skt_proxy,skt_accept;

    const char * socket_name=getenv("CUDA_PROXY_SOCKET");

    if (!socket_name){
        socket_name="CUDA_PROXY_SOCKET";
    }

    unlink(socket_name);

    memset(&sa_proxy, 0, sizeof(sa_proxy));

    strcpy(sa_proxy.sun_path, socket_name);
    sa_proxy.sun_family=AF_UNIX;

    if((skt_proxy=socket(AF_UNIX, SOCK_STREAM, 0))<0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if(bind(skt_proxy, (struct sockaddr *)&sa_proxy, sizeof(sa_proxy))<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    if (listen(skt_proxy, 100)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }


    
    CuDriverCallStructure request;
    CuDriverCallReplyStructure reply;
    while(1){
        if ((skt_accept=accept(skt_proxy, NULL, NULL))<0){
            perror("accept");
            continue;
        }

        if(read(skt_accept, &request, sizeof(CuDriverCallStructure))<0){
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("op:%s\n",to_string(request.op).c_str());

        proxy_call(skt_accept,&request,&reply);

        write(skt_accept, &reply, sizeof(CuDriverCallReplyStructure));
        close(skt_accept);
        
    }

}

CUresult proxy_call(int socket_handle,CuDriverCallStructure *request,CuDriverCallReplyStructure * reply){
    
    void * buffer;
    char * name;
    CUjit_option * jitOptions;
    void ** jitOptionValues;
    CUlibraryOption * libraryOptions;
    void ** libraryOptionValues;
    switch (request->op) {
    
        case CuDriverCall::CuDriverGetVersion:
            reply->result=cuDriverGetVersion(&reply->returnParams.driverVersion);
            break;
        case CuDriverCall::CuInit:
                reply->result=cuInit(request->params.cuInit.flags);
                printf("CuInit:%d\n",reply->result);
            break;
        
        case CuDriverCall::CuDeviceGetUuid:
                CUuuid uuid;
                reply->result=cuDeviceGetUuid(&uuid, request->params.cuDeviceGetUuid.dev);
                if(reply->result==CUDA_SUCCESS){
                    memcpy(reply->returnParams.uuid,uuid.bytes,sizeof(uuid.bytes));
                }
            break;
        case CuDriverCall::CuGetExportTable:
            break;
        
        case CuDriverCall::CuModuleGetLoadingMode:
            reply->result=cuModuleGetLoadingMode(&reply->returnParams.mode);
            printf("cuModuleGetLoadingMode:%d\n",reply->returnParams.mode);
            printf("cuModuleGetLoadingMode result:%d\n",reply->result);
            break;
        case  CuDriverCall::CuMemAlloc:

            reply->result=cuMemAlloc_v2(&reply->returnParams.dptr, request->params.cuMemAlloc.bytesize);
            break;
        case CuDriverCall::CuMemFree:
            reply->result=cuMemFree_v2(request->params.cuMemFree.dptr);
            break;
        case CuDriverCall::CuDeviceGetCount:
            reply->result=cuDeviceGetCount(&reply->returnParams.count);
            break;
        case CuDriverCall::CuMemcpyHtoD:
            buffer=malloc(request->params.cuMemcpyHtoD.ByteCount);
            if(read(socket_handle,buffer,request->params.cuMemcpyHtoD.ByteCount)<0){
                perror("CuMemcpyDtoH:reading from cilent fails.\n");
                exit(EXIT_FAILURE);
            }
            reply->result=cuMemcpyHtoD_v2(request->params.cuMemcpyHtoD.dstDevice, buffer, request->params.cuMemcpyHtoD.ByteCount);
            free(buffer);
            break;
        case CuDriverCall::CuMemcpyDtoH:
            buffer=malloc(request->params.cuMemcpyDtoH.ByteCount);
            reply->result=cuMemcpyDtoH_v2(buffer, request->params.cuMemcpyDtoH.srcDevice, request->params.cuMemcpyDtoH.ByteCount);
            if(write(socket_handle,buffer,request->params.cuMemcpyDtoH.ByteCount)<0){
                perror("CuMemcpyDtoH:writing to cilent fails.\n");
            }
            free(buffer);
            break;

        case CuDriverCall::CuCtxCreate:
            reply->result=cuCtxCreate(&reply->returnParams.ctx,request->params.cuCtxCreate.flags,request->params.cuCtxCreate.dev);
        case CuDriverCall::CuCtxGetCurrent:
            reply->result=cuCtxGetCurrent(&reply->returnParams.ctx);
        case CuDriverCall::CuCtxSetCurrent:
            reply->result=cuCtxSetCurrent(request->params.cuCtxSetCurrent.ctx);
            break;
        case CuDriverCall::CuCtxPushCurrent:
            reply->result=cuCtxPushCurrent_v2(request->params.cuCtxPushCurrent.ctx);

            break;
        case CUDriverCall::CuCtxPopCurrent:
            reply->result=cuCtxPopCurrent_v2(&reply->returnParams.ctx);
            break;
        case CuDriverCall::CuDeviceGet:
            reply->result=cuDeviceGet(&reply->returnParams.device, request->params.cuDeviceGet.ordinal);
            break;
        case CuDriverCall::CuDeviceGetAttribute:
            reply->result=cuDeviceGetAttribute(&reply->returnParams.pi, request->params.cuDeviceGetAttribute.attrib, request->params.cuDeviceGetAttribute.dev);
            break;
        case CuDriverCall::CuDeviceGetName:
            buffer=malloc(request->params.cuDeviceGetName.len);
            reply->result=cuDeviceGetName((char *)buffer, request->params.cuDeviceGetName.len, request->params.cuDeviceGetName.device);
            if(write(socket_handle, buffer, request->params.cuDeviceGetName.len)<0){
                perror("CuDeviceGetName:writing to cilent fails.\n");
            }
            free(buffer);
            break;

        case CuDriverCall::CuDevicePrimaryCtxRelease:
            reply->result=cuDevicePrimaryCtxRelease(request->params.cuDevicePrimaryCtxRelease.dev);
            break;
        case CuDriverCall::CuDeviceTotalMem:
            reply->result=cuDeviceTotalMem(&reply->returnParams.bytes, request->params.cuDeviceTotalMem.dev);
            break;
        case CuDriverCall::CuDevicePrimaryCtxRetain:
            reply->result=cuDevicePrimaryCtxRetain(&reply->returnParams.ctx, request->params.cuDevicePrimaryCtxRetain.dev);
            break;

        case CuDriverCall::CuLibraryLoadData:
            if(request->params.cuLibraryLoadData.numJitOptions!=0){
                jitOptions=(CUjit_option *)malloc(sizeof(CUjit_option)*request->params.cuLibraryLoadData.numJitOptions);
                if(read(socket_handle,jitOptions,sizeof(CUjit_option)*request->params.cuLibraryLoadData.numJitOptions)<0){
                    perror("CuLibraryLoadData:reading from cilent fails.\n");
                    exit(EXIT_FAILURE);
                }
                jitOptionValues=(void **)malloc(sizeof(void *)*request->params.cuLibraryLoadData.numJitOptions);
                for(int i=0;i<request->params.cuLibraryLoadData.numJitOptions;i++){
                    jitOptionValues[i]=malloc(sizeof(int));
                    if(read(socket_handle,jitOptionValues[i],sizeof(int))<0){
                        perror("CuLibraryLoadData:reading from cilent fails.\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if(request->params.cuLibraryLoadData.numLibraryOptions!=0){
                libraryOptions=(CUlibraryOption *)malloc(sizeof(CUlibraryOption)*request->params.cuLibraryLoadData.numLibraryOptions);
                if(read(socket_handle,libraryOptions,sizeof(CUjit_option)*request->params.cuLibraryLoadData.numLibraryOptions)<0){
                    perror("CuLibraryLoadData:reading from cilent fails.\n");
                    exit(EXIT_FAILURE);
                }
                libraryOptionValues=(void **)malloc(sizeof(void *)*request->params.cuLibraryLoadData.numLibraryOptions);
                for(int i=0;i<request->params.cuLibraryLoadData.numLibraryOptions;i++){
                    libraryOptionValues[i]=malloc(sizeof(int));
                    if(read(socket_handle,libraryOptionValues[i],sizeof(int))<0){
                        perror("CuLibraryLoadData:reading from cilent fails.\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            buffer=malloc(request->params.cuLibraryLoadData.fatbinSize);
            if(read(socket_handle,buffer,request->params.cuLibraryLoadData.fatbinSize)<0){
                perror("CuLibraryLoadData:reading fat binary from cilent fails.\n");
                exit(EXIT_FAILURE);
            }
            reply->result=cuLibraryLoadData(&reply->returnParams.lib,buffer,jitOptions,jitOptionValues,request->params.cuLibraryLoadData.numJitOptions,libraryOptions,libraryOptionValues,request->params.cuLibraryLoadData.numLibraryOptions);
            free(buffer);
            break;
        case CuDriverCall::CuLaunchKernel:
            if(read(socket_handle,buffer,request->params.cuLaunchKernel.parametersMetadataLen)<0){
                perror("CuLaunchKernel:reading parametersMetadata from cilent fails.\n");
                exit(EXIT_FAILURE);
            }
            launch_kernel_proxy(request, reply, buffer);
            break;
        case CuDriverCall::CuLibraryGetModule:
            reply->result= cuLibraryGetModule(&reply->returnParams.mod,request->params.cuLibraryGetModule.library);
            break;
        case CuDriverCall::CuModuleGetFunction:
            name=(char *)malloc(request->params.cuModuleGetFunction.nameLength);
            if(read(socket_handle, name, request->params.cuModuleGetFunction.nameLength)<0){
                perror("CuModuleGetFunction:reading from cilent fails.\n");
                exit(EXIT_FAILURE);
            }
            reply->result=cuModuleGetFunction(&reply->returnParams.hfunc,request->params.cuModuleGetFunction.mod,request->params.cuModuleGetFunction.name);
            free(name);
            break;
        default:
            break;
    }
    return CUDA_SUCCESS;
}


int main(){
    proxy_init();
    proxy_start();
    return 0;
}

