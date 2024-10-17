#include<cuda_original.h>

#include <cstdlib>
#include <cstring>
#include<stdio.h>
#include<communication.h>

#include<sys/socket.h>
#include<sys/un.h>
#include <unistd.h>

CUresult proxy_call(CuDriverCallStructure *request,CuDriverCallReplyStructure * reply);
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
    
    if (listen(skt_proxy, 5)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((skt_accept=accept(skt_proxy, NULL, NULL))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    
    CuDriverCallStructure request;
    CuDriverCallReplyStructure reply;
    while(1){
        if(read(skt_accept, &request, sizeof(CuDriverCallStructure))<0){
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("op:%d\n",request.op);

        proxy_call(&request,&reply);

        write(skt_accept, &reply, sizeof(CuDriverCallReplyStructure));
        
    }

}

CUresult proxy_call(CuDriverCallStructure *request,CuDriverCallReplyStructure * reply){
    
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
        case CuDriverCall::CuDeviceGetCount:
            reply->result=cuDeviceGetCount(&reply->returnParams.count);
            break;
        case CuDriverCall::CuMemcpyDtoH:
            break;
        case CuDriverCall::CuMemcpyHtoD:
            break;

        case CuDriverCall::CuCtxGetCurrent:
            break;
        case CuDriverCall::cuCtxPushCurrent:
            break;

        case CuDriverCall::CuDeviceGet:
            break;
        case CuDriverCall::CuDeviceGetAttribute:
            break;
        case CuDriverCall::CuDeviceGetName:
            break;
        case CuDriverCall::CuDeviceGetUuid:
            break;
        case CuDriverCall::cuDevicePrimaryCtxRelease:
            break;
        case CuDriverCall::CuDeviceTotalMem:
            break;
        case CuDriverCall::CuDevicePrimaryCtxRetain:
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

