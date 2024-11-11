#include "communicator.h"
#include "communication.h"
#include "cuda_original.h"
#include <stdio.h>
#include <unistd.h>
int communicate_with_server(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure) {
    int skt_client;
    struct sockaddr_un sa_client;

    printf("Sending OP:%d\n",send_structure->op);
    // 如果没有指定socket_name，使用默认值
    if (!socket_name) {
        socket_name = "CUDA_PROXY_SOCKET";
    }

    // 创建客户端socket
    if ((skt_client = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    // 初始化 sockaddr_un 结构体
    memset(&sa_client, 0, sizeof(sa_client));
    sa_client.sun_family = AF_UNIX;
    strcpy(sa_client.sun_path, socket_name);

    // 连接服务端
    if (connect(skt_client, (struct sockaddr *)&sa_client, sizeof(sa_client)) < 0) {
        perror("connect");
        close(skt_client);
        return -1;
    }

    // 发送消息
    if (write(skt_client, send_structure, sizeof(CuDriverCallStructure)) < 0) {
        perror("write");
        close(skt_client);
        return -1;
    }
    else if (send_structure->op==CuDriverCall::CuMemcpyHtoD){
        if (write(skt_client, send_structure->params.cuMemcpyHtoD.srcHost, send_structure->params.cuMemcpyHtoD.ByteCount) < 0) {
            perror("write");
            close(skt_client);
            return -1;
        }
    }

    else if (send_structure->op==CuDriverCall::CuMemcpyDtoH){
        if(read(skt_client,send_structure->params.cuMemcpyDtoH.dstHost,send_structure->params.cuMemcpyDtoH.ByteCount)<0){
            perror("read from gpu-proxy fails");
            close(skt_client);
            return -1;
        }
    }

    else if (send_structure->op==CuDriverCall::CuDeviceGetName){
        printf("sending device name\n");
        if (read(skt_client,send_structure->params.cuDeviceGetName.name,send_structure->params.cuDeviceGetName.len)<0){
            printf("read from gpu-proxy fails");
            close(skt_client);
            return -1;
        }
    }else if (send_structure->op == CuDriverCall::CuModuleGetFunction){
        if(write(skt_client, send_structure->params.cuModuleGetFunction.name, send_structure->params.cuModuleGetFunction.nameLength)<0){

            perror("CuModuleGetFunction name sending fails");
            close(skt_client);
            return -1;
        }
    }


    // 接收来自服务端的响应
    if (read(skt_client, recv_structure, sizeof(CuDriverCallStructure)) < 0) {
        perror("read");
        close(skt_client);
        return -1;
    }

    printf("result: %d\n", recv_structure->result);

    // 关闭socket
    close(skt_client);
    return 0; // 成功
}
int communicate_with_server_extra(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure,void *jitOptions,void **jitOptionsValues,void* libraryOptions,void **libraryOptionValues) {
    int skt_client;
    struct sockaddr_un sa_client;

    printf("Sending OP:%d\n",send_structure->op);
    // 如果没有指定socket_name，使用默认值
    if (!socket_name) {
        socket_name = "CUDA_PROXY_SOCKET";
    }

    // 创建客户端socket
    if ((skt_client = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    // 初始化 sockaddr_un 结构体
    memset(&sa_client, 0, sizeof(sa_client));
    sa_client.sun_family = AF_UNIX;
    strcpy(sa_client.sun_path, socket_name);

    // 连接服务端
    if (connect(skt_client, (struct sockaddr *)&sa_client, sizeof(sa_client)) < 0) {
        perror("connect");
        close(skt_client);
        return -1;
    }

    // 发送消息
    if (write(skt_client, send_structure, sizeof(CuDriverCallStructure)) < 0) {
        perror("write");
        close(skt_client);
        return -1;
    }
 
    if(send_structure->op==CuDriverCall::CuLibraryLoadData){

        unsigned int numJitOptions =send_structure->params.cuLibraryLoadData.numJitOptions;
        unsigned int numLibraryOptions =send_structure->params.cuLibraryLoadData.numLibraryOptions;
        if (numJitOptions!=0){
            if(write(skt_client, jitOptions, sizeof(CUjit_option)*numJitOptions)<0){
                perror("sending jitOptions fails");
                return -1;
            }
            for(int i=0;i<numJitOptions;i++){
                if(write(skt_client, jitOptionsValues[i], sizeof(int))<0){
                    perror("sending jitOptionsValues fails");
                    return -1;
                }
            }
        }
        if (numLibraryOptions!=0){
            if(write(skt_client, libraryOptions, sizeof(CUlibraryOption)*numLibraryOptions)<0){
                perror("sending libraryOptions fails");
                return -1;
            }
            for(int i=0;i<numLibraryOptions;i++){
                if(write(skt_client, libraryOptionValues[i], sizeof(int))<0){
                    perror("sending libraryOptionValues fails");
                    return -1;
                }
            }
        }
        if (write(skt_client, send_structure->params.cuLibraryLoadData.wrapper.data, send_structure->params.cuLibraryLoadData.fatbinSize)<0){
            perror("sending fatbinary fails");
            return -1;
        }
    }

    // 接收来自服务端的响应
    if (read(skt_client, recv_structure, sizeof(CuDriverCallStructure)) < 0) {
        perror("read");
        close(skt_client);
        return -1;
    }

    printf("result: %d\n", recv_structure->result);

    // 关闭socket
    close(skt_client);
    return 0; // 成功
}

int communicate_with_server_launchkernel(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure,void *parameters_metadata) {
    int skt_client;
    struct sockaddr_un sa_client;

    printf("Sending OP:%d\n",send_structure->op);
    // 如果没有指定socket_name，使用默认值
    if (!socket_name) {
        socket_name = "CUDA_PROXY_SOCKET";
    }

    // 创建客户端socket
    if ((skt_client = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    // 初始化 sockaddr_un 结构体
    memset(&sa_client, 0, sizeof(sa_client));
    sa_client.sun_family = AF_UNIX;
    strcpy(sa_client.sun_path, socket_name);

    // 连接服务端
    if (connect(skt_client, (struct sockaddr *)&sa_client, sizeof(sa_client)) < 0) {
        perror("connect");
        close(skt_client);
        return -1;
    }

    // 发送消息
    if (write(skt_client, send_structure, sizeof(CuDriverCallStructure)) < 0) {
        perror("write");
        close(skt_client);
        return -1;
    }
 
    if (send_structure->op == CuDriverCall::CuLaunchKernel){
        if (write(skt_client, parameters_metadata, send_structure->params.cuLaunchKernel.parametersMetadataLen) < 0) {
            perror("write");
            close(skt_client);
            return -1;
        }

    }else{
        perror("wrong op");
        close(skt_client);
        return -1;
    }

    // 接收来自服务端的响应
    if (read(skt_client, recv_structure, sizeof(CuDriverCallStructure)) < 0) {
        perror("read");
        close(skt_client);
        return -1;
    }

    printf("result: %d\n", recv_structure->result);

    // 关闭socket
    close(skt_client);
    return 0; // 成功
}