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
        case CuDriverCall::CuInit: return "CuInit";
        default: return "Unknown";
    }
}
CUresult proxy_call(int socket_handle,CuDriverCallStructure *request,CuDriverCallReplyStructure * reply);
int proxy_init(){
    CUresult result;
    const char* errorString;
    // 初始化 CUDA
    result=cuInit(0);
    if (result != CUDA_SUCCESS){
        cuGetErrorString(result, &errorString);

        printf("cuInit failed:%s\n",errorString);
        return 1;
    }
    CUcontext context;
    CUdevice cuDevice;
    cuDeviceGet(&cuDevice, 0);
    result=cuCtxCreate(&context, 0, cuDevice);

    if (result != CUDA_SUCCESS){
        cuGetErrorString(result, &errorString);
        printf("cuCtxCreate failed:%s\n",errorString);
        return -1;
    }
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
    switch (request->op) {
    
        case CuDriverCall::CuDriverGetVersion:
            reply->result=cuDriverGetVersion(&reply->returnParams.driverVersion);
            break;
        case CuDriverCall::CuInit:
                reply->result=cuInit(0);
            break;
        
        case CuDriverCall::CuGetExportTable:
            break;
        
        case CuDriverCall::CuModuleGetLoadingMode:
            reply->result=cuModuleGetLoadingMode(&reply->returnParams.mode);
        case  CuDriverCall::CuMemAlloc:

            reply->result=cuMemAlloc_v2(&reply->returnParams.dptr, request->params.cuMemAlloc.size);
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

        case CuDriverCall::CuCtxGetCurrent:
            reply->result=cuCtxGetCurrent(&reply->returnParams.ctx);
        case CuDriverCall::CuCtxSetCurrent:
            reply->result=cuCtxSetCurrent(request->params.cuCtxSetCurrent.ctx);
            break;
        case CuDriverCall::CuCtxPushCurrent:
            reply->result=cuCtxPushCurrent_v2(request->params.cuCtxPushCurrent.ctx);

            break;

        case CuDriverCall::CuDeviceGet:
            reply->result=cuDeviceGet(&reply->returnParams.device, request->params.cuDeviceGet.ordinal);
            break;
        case CuDriverCall::CuDeviceGetAttribute:
            reply->result=cuDeviceGetAttribute(&reply->returnParams.pi, request->params.cuDeviceGetAttribute.attrib, request->params.cuDeviceGetAttribute.dev);
            break;
        case CuDriverCall::CuDeviceGetName:
            break;
        case CuDriverCall::CuDeviceGetUuid:
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

