

#include <cstdlib>
#include <cstring>
#include<cuda.h>
#include<stdio.h>
#include<communication.h>

#include<sys/socket.h>
#include<sys/un.h>
#include <unistd.h>
const int PORT=8888;
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
    }
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

    
    cudaCallStructure structure;
    while(1){
        if(read(skt_accept, &structure, sizeof(cudaCallStructure))<0){
            perror("read");
            exit(EXIT_FAILURE);
        }
        
    }

}

CUresult proxy_call(cudaCallStructure *structure){
    
    switch (structure->op) {
    
        case  CudaMalloc:
            break;

        case CudaMemcpy:
            break;
        case CudaFree:
            break;

        case CudaLaunchKernel:
            break;
        
        default:
            break;
    }
    return CUDA_SUCCESS;
}


