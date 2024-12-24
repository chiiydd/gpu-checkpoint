#include <bits/types/time_t.h>
#include <cstddef>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>


#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "communication.h"

#include "cuda_hidden.h"


void hexdump(const uint8_t* data, size_t size,bool verbose)
{
    size_t pos = 0;
    while (pos < size) {
        if (verbose){
            printf("%#05zx: ", reinterpret_cast<uint64_t>(data)+pos);

        }
        for (int i = 0; i < 16; i++) {
            if (pos + i < size) {
                printf("%02x", data[pos + i]);
            } else {
                printf("  ");
            }
            if (i % 4 == 3) {
                printf(" ");
            }
        }
        if(verbose){
            printf(" | ");
        
            for (int i = 0; i < 16; i++) {
                if (pos + i < size) {
                    if (data[pos + i] >= 0x20 && data[pos + i] <= 0x7e) {
                        printf("%c", data[pos + i]);
                    } else {
                        printf(".");
                    }
                } else {
                    printf(" ");
                }
            }
            printf("|\n");
        }else{
            printf("\n");
        }

        pos += 16;
    }
}
int communicate_with_server_hidden(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure) {
    int skt_client;
    struct sockaddr_un sa_client;

    printf("[communicate_with_server_hidden] Sending OP:%d\n",send_structure->op);
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
    void * buffer;
    
    switch (send_structure->op) {
        case CuDriverCall::hidden_3_0:
            if(write(skt_client, send_structure->params.hidden_3_0.arg3, 0xB0)<0){
                perror("[communicate_with_server_hidden] write hidden_3_0's arg3 fails");
                return -1;
            }
            break;
        
        case CuDriverCall::hidden_3_1:
                if(write(skt_client, send_structure->params.hidden_3_1.arg2, 0x80)<0){
                    perror("[communicate_with_server_hidden] write hidden_3_1's arg2 fails");
                    return -1;
                }
            break;
        
        case CuDriverCall::hidden_5_0:
                if(read(skt_client, send_structure->params.hidden_5_0.arg3, 16)<0){
                    perror("[communicate_with_server_hidden] write hidden_5_0's arg3 fails");
                    return -1;
                }
        default:break;


    }
    return 0;
    
}





void* hooked_hidden_table[EXPECT_0+EXPECT_1+EXPECT_2+EXPECT_3+EXPECT_4+EXPECT_5+EXPECT_CALL_CNT] = {
    (void*)(EXPECT_5*sizeof(void*)),
    (void*)hidden_5_0,
    (void*)hidden_5_1,
    nullptr,
    (void*)(EXPECT_0*sizeof(void*)),
    (void*)hidden_0_0,
    (void*)hidden_get_device_ctx,
    (void*)hidden_0_2,
    (void*)hidden_0_3,
    (void*)hidden_0_4,
    (void*)hidden_get_module,
    (void*)hidden_0_6,
    (void*)hidden_0_7,
    (void*)hidden_0_8,
    nullptr,
    (void*)hidden_0_10,
    (void*)hidden_3_0,
    (void*)hidden_3_1,
    (void*)hidden_3_2,
    (void*)(EXPECT_1*sizeof(void*)),
    (void*)hidden_1_0,
    (void*)hidden_1_1,
    (void*)hidden_1_2,
    (void*)hidden_1_3,
    (void*)hidden_1_4,
    (void*)hidden_1_5,
    (void*)(EXPECT_2*sizeof(void*)),
    (void*)hidden_2_0,
    (void*)hidden_2_1,
    (void*)(EXPECT_4*sizeof(void*)),
    (void*)hidden_4_0,
    (void*)hidden_4_1,
    (void*)hidden_4_2,
    (void*)hidden_4_3,
};

int hidden_0_0(void* arg1) 
{
    printf("[hidden_0_0] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;

}


unsigned int hidden_get_device_ctx(uint64_t * cu_ctx, uint32_t cu_device)
{

    printf("[hidden_get_device_ctx] called: cu_ctx = %lx, cu_device = %u\n", *cu_ctx, cu_device);
    CuDriverCallStructure request{
        .op=CuDriverCall::hidden_get_device_ctx,
        .params={
            .hidden_get_device_ctx={
                .dev=cu_device
            }
        }
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);
    *cu_ctx=reply.returnParams.device;
    return reply.result;
}



int hidden_0_2(void* arg1) 
{
    printf("[hidden_0_2] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

int hidden_0_3(void* arg1) 
{
    printf("[hidden_0_3] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

int hidden_0_4(void* arg1) 
{
    printf("[hidden_0_4] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}



int hidden_get_module(void** cu_module, void** arg2, void* arg3, void* arg4, int arg5) 
{
    printf("[hidden_get_module] called: cu_module = %p, arg2 = %p, arg3 = %p, arg4 = %p, arg5 = %d\n", cu_module, arg2, arg3, arg4, arg5);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

/* called as part of 
 * cudart::globalState::destroyModule(cudart::globalModule*) 
 */
int hidden_0_6(void* arg1) 
{
    printf("[hidden_0_6] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

int hidden_0_7(void* arg1) 
{
    printf("[hidden_0_7] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}
int hidden_0_8(void* arg1) 
{
    printf("[hidden_0_8] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}
int hidden_0_10(void *arg1){
    printf("[hidden_0_10] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}


int hidden_1_0(int arg1, void* arg2)
{
    printf("[hidden_1_0] called: arg1 = %d, arg2 = %p\n", arg1, arg2);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}


/* called as part of
 * cudart::globalState::initializeDriverInternal()
 */
void hidden_1_1(uint64_t * arg1, uint64_t *arg2)
{
    printf("[hidden_1_1] called: arg1 = %p, arg2 = %p\n", arg1, arg2);

    printf("[hidden_1_1] called: arg1 = 0x%lx, arg2 = %lu\n", *arg1, *arg2);

    CuDriverCallStructure request{
        .op=CuDriverCall::Hidden_1_1,
        .params={.empty{}}
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);

    *arg1=reply.returnParams.hidden_1_1.arg1;
    *arg2=reply.returnParams.hidden_1_1.arg2;


}

int hidden_1_2(void* arg1) 
{
    printf("[hidden_1_2] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

/* parameter seems correct. Is called directly from cudart api functions
 * e.g., cudaMalloc. Return value is not checked at all.
 */
int hidden_1_3(void* arg1, void* arg2) 
{
    printf("[hidden_1_3] called: arg1 = %p, arg2 = %p\n", arg1, arg2);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

int hidden_1_4(void* arg1) 
{
    printf("[hidden_1_4] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

/* called as part of
 * cudart::globalState::initializeDriverInternal()
 * I have no clue what this does and whether the below is correct.
 * The calling function seems to do not much else than check that the pointers are
 * non-NULL (better verify this before assuming this statement is correct).
 */
void hidden_1_5(uint64_t * arg1, uint64_t * arg2) 
{
    printf("[hidden_1_5] called: arg1 = %p, arg2 = %p\n", arg1, arg2);
    printf("[hidden_1_5] arg1 = %lu, arg2 = %lu\n", *arg1, *arg2);

    CuDriverCallStructure request{
        .op=CuDriverCall::Hidden_1_5,
        .params={.empty{}}
    };

    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);
    *arg1=reply.returnParams.hidden_1_5.arg1;
    *arg2=reply.returnParams.hidden_1_5.arg2;
}


int hidden_2_0(void* arg1) 
{
    printf("[hidden_2_0] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

/* parameter seems correct. Is called directly from cudart api functions
 * e.g., cudaMalloc. Return value is not checked at all.
 */
int hidden_2_1(void* arg1)
{
    printf("[hidden_2_1] called: arg1 = %p\n", arg1);


    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}


/* called as part of cudart::contextStateManager::
 * initRuntimeContextState_nonreentrant(cudart::contextState**)
 * the second parameter is a NULL-terminated function pointer array
 * the third parameter is the module (CUmodule*)
 */
int hidden_3_0(int64_t arg1, uint64_t arg2, uint64_t* arg3,uint64_t arg4)
{
    printf("[hidden_3_0] called: arg1 = %ld, arg2 = %p, arg3 = %p, arg4 = %p\n", arg1, (uint64_t*)arg2, arg3, (uint64_t*)arg4);

    CuDriverCallStructure reqeust{
        .op=CuDriverCall::hidden_3_0,
        .params={
            .hidden_3_0={
                .arg1=arg1,
                .arg2=arg2,
                .arg3=arg3,
                .arg4=arg4
            }
        }
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &reqeust, &reply);
    return reply.result;
}

/* called as part of cudart::contextStateManager::
 * destroyContextState(cudart::contextState*, bool)
 */
int hidden_3_1(void* arg1, void* arg2)
{
    printf("[hidden_3_1] called: arg1 = %p, arg2 = %p\n", arg1, arg2);

    CuDriverCallStructure request{
        .op=CuDriverCall::hidden_3_1,
        .params={
            .hidden_3_1={
                .arg1=arg1,
                .arg2=arg2
            }
        }
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);
    return reply.result;

}


int hidden_3_2(void *arg1,uint64_t arg2,void * arg3)
{
    printf("[hidden_3_2] called: arg1 = %p, arg2 = %ld, arg3 = %p\n", arg1, arg2, arg3);

    CuDriverCallStructure request{
        .op=CuDriverCall::hidden_3_2,
        .params={
            .hidden_3_2={
                .arg1=arg1,
                .arg2=arg2,
                .arg3=arg3
            }
        }
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);
    return reply.result;

}


int hidden_4_0(void* arg1) 
{
    printf("[hidden_4_0] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

int hidden_4_1(int64_t arg1,int * arg2,int64_t * arg3)
{
    printf("[hidden_4_1] called: arg1 = %ld, arg2 = %p, arg3 = %p\n", arg1, arg2, arg3);

    CuDriverCallStructure request{
        .op=CuDriverCall::hidden_4_1,
        .params={
            .hidden_4_1={
                .arg1=arg1,
            }
        }
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);
    *arg2=reply.returnParams.hidden_4_1.arg2;
    *arg3=reply.returnParams.hidden_4_1.arg3;

    return reply.result;


}



unsigned int hidden_4_2(){
    printf("[hidden_4_2] called\n");
    printf("unimplemented\n");
    return 0;
}

int hidden_4_3(void* arg1) 
{
    printf("[hidden_4_3] called: arg1 = %p\n", arg1);

    printf("%s() -> UNIMPLEMENTED!\n", __FUNCTION__);
    return 0;
}

int32_t hidden_5_0(uint32_t arg1,uint64_t  arg2, uint64_t* arg3) 
{
    printf("[hidden_5_0] called: arg1 = %u, arg2 = 0x%lx, arg3 = %p\n", arg1, arg2, arg3);
    CuDriverCallStructure request{
        .op=CuDriverCall::hidden_5_0,
        .params={
            .hidden_5_0={
                .arg1=arg1,
                .arg2=arg2,
                .arg3=arg3,
            }
        }
    };
    CuDriverCallReplyStructure reply;
    communicate_with_server_hidden(nullptr, &request, &reply);
    memcpy(arg3, reply.returnParams.uuid, 16);
    return reply.result;

}

int hidden_5_1(void * arg1){
    printf("[hidden_5_1] called: arg1 = %p\n", arg1);
    
    printf("unimplemented\n");
    return 0;
}