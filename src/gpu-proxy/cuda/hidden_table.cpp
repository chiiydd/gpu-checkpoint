#include <cuda.h>
#include "communication.h"
#include "cuda_subset.h"
#include <cstdio>
// const unsigned char  tableUUID[7][16]={
//     {	
//         0x6b,0xd5,0xfb,0x6c,
// 	    0x5b,0xf4,0xe7,0x4a,
// 	    0x89,0x87,0xd9,0x39,
// 	    0x12,0xfd,0x9d,0xf9
//     },
//     {
// 		0xa0,0x94,0x79,0x8c,
// 		0x2e,0x74,0x2e,0x74,
// 		0x93,0xf2,0x08,0x00,
// 		0x20,0x0c,0x0a,0x66,
//     },
//     {
// 		0x42,0xd8,0x5a,0x81,
// 		0x23,0xf6,0xcb,0x47,
// 		0x82,0x98,0xf6,0xe7,
// 		0x8a,0x3a,0xec,0xdc,
//     },
//     {
// 		0xc6,0x93,0x33,0x6e,
// 		0x11,0x21,0xdf,0x11,
// 		0xa8,0xc3,0x68,0xf3,
// 		0x55,0xd8,0x95,0x93,
//     },
//     {
// 		0x26,0x3e,0x88,0x60,
// 		0x7c,0xd2,0x61,0x43,
// 		0x92,0xf6,0xbb,0xd5,
// 		0x00,0x6d,0xfa,0x7e,  
//     },
//     {
// 		0xd4,0x08,0x20,0x55,
// 		0xbd,0xe6,0x70,0x4b,
// 		0x8d,0x34,0xba,0x12,
// 		0x3c,0x66,0xe1,0xf2,
//     }
    
// };
const CUuuid tableUUID[7] = {
    {static_cast<char>(0x6b), static_cast<char>(0xd5), static_cast<char>(0xfb), static_cast<char>(0x6c),
     static_cast<char>(0x5b), static_cast<char>(0xf4), static_cast<char>(0xe7), static_cast<char>(0x4a),
     static_cast<char>(0x89), static_cast<char>(0x87), static_cast<char>(0xd9), static_cast<char>(0x39),
     static_cast<char>(0x12), static_cast<char>(0xfd), static_cast<char>(0x9d), static_cast<char>(0xf9)},
    {static_cast<char>(0xa0), static_cast<char>(0x94), static_cast<char>(0x79), static_cast<char>(0x8c),
     static_cast<char>(0x2e), static_cast<char>(0x74), static_cast<char>(0x2e), static_cast<char>(0x74),
     static_cast<char>(0x93), static_cast<char>(0xf2), static_cast<char>(0x08), static_cast<char>(0x00),
     static_cast<char>(0x20), static_cast<char>(0x0c), static_cast<char>(0x0a), static_cast<char>(0x66)},
    {static_cast<char>(0x42), static_cast<char>(0xd8), static_cast<char>(0x5a), static_cast<char>(0x81),
     static_cast<char>(0x23), static_cast<char>(0xf6), static_cast<char>(0xcb), static_cast<char>(0x47),
     static_cast<char>(0x82), static_cast<char>(0x98), static_cast<char>(0xf6), static_cast<char>(0xe7),
     static_cast<char>(0x8a), static_cast<char>(0x3a), static_cast<char>(0xec), static_cast<char>(0xdc)},
    {static_cast<char>(0xc6), static_cast<char>(0x93), static_cast<char>(0x33), static_cast<char>(0x6e),
     static_cast<char>(0x11), static_cast<char>(0x21), static_cast<char>(0xdf), static_cast<char>(0x11),
     static_cast<char>(0xa8), static_cast<char>(0xc3), static_cast<char>(0x68), static_cast<char>(0xf3),
     static_cast<char>(0x55), static_cast<char>(0xd8), static_cast<char>(0x95), static_cast<char>(0x93)},
    {static_cast<char>(0x26), static_cast<char>(0x3e), static_cast<char>(0x88), static_cast<char>(0x60),
     static_cast<char>(0x7c), static_cast<char>(0xd2), static_cast<char>(0x61), static_cast<char>(0x43),
     static_cast<char>(0x92), static_cast<char>(0xf6), static_cast<char>(0xbb), static_cast<char>(0xd5),
     static_cast<char>(0x00), static_cast<char>(0x6d), static_cast<char>(0xfa), static_cast<char>(0x7e)},
    {static_cast<char>(0xd4), static_cast<char>(0x08), static_cast<char>(0x20), static_cast<char>(0x55),
     static_cast<char>(0xbd), static_cast<char>(0xe6), static_cast<char>(0x70), static_cast<char>(0x4b),
     static_cast<char>(0x8d), static_cast<char>(0x34), static_cast<char>(0xba), static_cast<char>(0x12),
     static_cast<char>(0x3c), static_cast<char>(0x66), static_cast<char>(0xe1), static_cast<char>(0xf2)}
};

int hidden_get_device_ctx_svc(CuDriverCallStructure *request, CuDriverCallReplyStructure *reply) {
    printf("[hidden_get_device_ctx_svc] called with dev :%d\n",request->params.hidden_get_device_ctx.dev);
    void **ppExportTable;
    cuGetExportTable(ppExportTable,&tableUUID[0]);
    CUresult (*real_func)(CUcontext *, uint32_t)= (CUresult (*)(CUcontext*,uint32_t) )ppExportTable[2];

    reply->result=real_func(&reply->returnParams.ctx,request->params.hidden_get_device_ctx.dev);
    
    return 0;
}

int hidden_1_1_svc(CuDriverCallStructure *request, CuDriverCallReplyStructure *reply) {
    printf("[hidden_1_1_svc] called\n");
    void **ppExportTable;
    cuGetExportTable(ppExportTable,&tableUUID[1]);
    void (*real_func)(uint64_t *, uint64_t *)= (void (*)(uint64_t*,uint64_t*) )ppExportTable[2];
    real_func(&reply->returnParams.hidden_1_1.arg1,&reply->returnParams.hidden_1_1.arg2);
    return 0;
}
int hidden_1_5_svc(CuDriverCallStructure *request, CuDriverCallReplyStructure *reply) {
    printf("[hidden_1_5_svc] called\n");
    void **ppExportTable;
    cuGetExportTable(ppExportTable,&tableUUID[1]);
    void (*real_func)(uint64_t *, uint64_t *)= (void (*)(uint64_t*,uint64_t*) )ppExportTable[6];
    real_func(&reply->returnParams.hidden_1_1.arg1,&reply->returnParams.hidden_1_1.arg2);
    return 0;
}



int hidden_4_1(CuDriverCallStructure *request, CuDriverCallReplyStructure *reply) {
    printf("[hidden_4_1_svc] called\n");
    void **ppExportTable;
    cuGetExportTable(ppExportTable,&tableUUID[4]);
    CUresult (*real_func)(int64_t, int *, int64_t *)= (CUresult (*)(int64_t, int *, int64_t *) )ppExportTable[2];


    reply->result=real_func(request->params.hidden_4_1.arg1,reply->returnParams.hidden_4_1.arg2,&reply->returnParams.hidden_4_1.arg3);
    return 0;
}


int hidden_5_0_svc(CuDriverCallStructure *request, CuDriverCallReplyStructure *reply) {
    printf("[hidden_5_0_svc] called\n");
    void **ppExportTable;
    cuGetExportTable(ppExportTable,&tableUUID[5]);
    CUresult (*real_func)(uint32_t, uint64_t, char *)= (CUresult (*)(uint32_t, uint64_t, char *) )ppExportTable[0];
    reply->result=real_func(request->params.hidden_5_0.arg1,request->params.hidden_5_0.arg2,reply->returnParams.uuid);
    return 0;
}





