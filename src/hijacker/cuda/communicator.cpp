#include "communicator.h"
#include "communication.h"
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
    if (send_structure->op==CuDriverCall::CuMemcpyHtoD){
        if (write(skt_client, send_structure->params.cuMemcpyHtoD.srcHost, send_structure->params.cuMemcpyHtoD.ByteCount) < 0) {
            perror("write");
            close(skt_client);
            return -1;
        }
    }

    if (send_structure->op==CuDriverCall::CuMemcpyDtoH){
        if(read(skt_client,send_structure->params.cuMemcpyDtoH.dstHost,send_structure->params.cuMemcpyDtoH.ByteCount)<0){
            perror("read from gpu-proxy fails");
            close(skt_client);
            return -1;
        }
    }

    if (send_structure->op==CuDriverCall::CuDeviceGetName){
        if (read(skt_client,send_structure->params.cuDeviceGetName.name,send_structure->params.cuDeviceGetName.len)<0){
            perror("read from gpu-proxy fails");
            close(skt_client);
            return -1;
        }
    };
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