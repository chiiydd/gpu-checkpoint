#include <bits/types/time_t.h>
#include <cstddef>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>


#include <string.h>



#include "cuda_hidden.h"



static void* hidden_table[EXPECT_0+EXPECT_1+EXPECT_2+EXPECT_3+EXPECT_4+EXPECT_5] = {0};
// static int call_cnt = 0;

/* append a ptr table segment to the static array above
 */
void* hidden_add_table(void* export_table, size_t len,int call_cnt)
{
    if (call_cnt >= EXPECT_CALL_CNT) {
        printf("call_cnt >= EXPECT_CALL_CNT\n");
        return NULL;
    }
    if(expect_elem_cnt[call_cnt] != len) {
        printf("expect_elem_cnt[call_cnt] != len\n");
        return NULL;
    }
    // if (call_cnt == 3) {
        memcpy(hidden_table+hidden_offset[call_cnt], export_table, len*sizeof(void*));
    // } else {
    //     //there is a length element at the beginning of some tables
    //     memcpy(hidden_table+hidden_offset[call_cnt],
    //            export_table+sizeof(void*),
    //            (len-1)*sizeof(void*));
    // }

    call_cnt++;

    return hidden_table+hidden_offset[call_cnt-1];
}

/* get the function pointer to a specific hidden function
 */
void *hidden_table_get(size_t call, size_t index)
{
    if (call >= EXPECT_CALL_CNT || index >= expect_elem_cnt[call])
        return NULL;

    return hidden_table[hidden_call_offset[call]+index];
}






void* hooked_hidden_table[EXPECT_0+EXPECT_1+EXPECT_2+EXPECT_3+EXPECT_4+EXPECT_5] = {
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
    (void*)hidden_3_0,
    (void*)hidden_3_1,
    (void*)hidden_3_2,
    (void*)(EXPECT_4*sizeof(void*)),
    (void*)hidden_4_0,
    (void*)hidden_4_1,
    (void*)hidden_4_2,
    (void*)hidden_4_3,
    (void*)(EXPECT_5*sizeof(void*)),
    (void*)hidden_5_0,
    (void*)hidden_5_1,
};

int hidden_0_0(void* arg1) 
{
    printf("[hidden_0_0] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 0);

    return real_func(arg1);
}


int hidden_get_device_ctx(void** cu_ctx, int cu_device)
{

    printf("[hidden_get_device_ctx] called: cu_ctx = %p, cu_device = %d\n", cu_ctx, cu_device);

    int (*real_func)(void**, int);
    real_func = (int(*)(void**, int)) hidden_table_get(0, 1);
    return real_func(cu_ctx, cu_device);
}



int hidden_0_2(void* arg1) 
{
    printf("[hidden_0_2] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 2);
    return real_func(arg1);
}

int hidden_0_3(void* arg1) 
{
    printf("[hidden_0_3] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 3);
    return real_func(arg1);
}

int hidden_0_4(void* arg1) 
{
    printf("[hidden_0_4] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 4);
    return real_func(arg1);
}



int hidden_get_module(void** cu_module, void** arg2, void* arg3, void* arg4, int arg5) 
{
    printf("[hidden_get_module] called: cu_module = %p, arg2 = %p, arg3 = %p, arg4 = %p, arg5 = %d\n", cu_module, arg2, arg3, arg4, arg5);

    int (*real_func)(void**, void**, void*, void*, int);
    real_func = (int(*)(void**, void**, void*, void*, int)) hidden_table_get(0, 5);
    return real_func(cu_module, arg2, arg3, arg4, arg5);
}

/* called as part of 
 * cudart::globalState::destroyModule(cudart::globalModule*) 
 */
int hidden_0_6(void* arg1) 
{
    printf("[hidden_0_6] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 6);
    return real_func(arg1);
}

int hidden_0_7(void* arg1) 
{
    printf("[hidden_0_7] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 7);
    return real_func(arg1);
}
int hidden_0_8(void* arg1) 
{
    printf("[hidden_0_8] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(0, 8);
    return real_func(arg1);
}

/* Used
 */
int hidden_1_0(int arg1, void* arg2)
{
    printf("[hidden_1_0] called: arg1 = %d, arg2 = %p\n", arg1, arg2);

    int (*real_func)(int, void*);
    real_func = (int(*)(int, void*)) hidden_table_get(1, 0);
    return real_func(arg1, arg2);
}

/* called as part of
 * cudart::globalState::initializeDriverInternal()
 */
void hidden_1_1(int64_t * arg1, int64_t *arg2)
{
    printf("[hidden_1_1] called: arg1 = %ld, arg2 = %lu\n", *arg1, *arg2);

    void (*real_func)(int64_t*, int64_t*);
    real_func = (void(*)(int64_t*,int64_t*)) hidden_table_get(1, 1);
    real_func(arg1, arg2);
    printf("[hidden_1_1] result = %lu\n", *arg2);

}

int hidden_1_2(void* arg1) 
{
    printf("[hidden_1_2] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(1, 2);
    return real_func(arg1);
}

/* parameter seems correct. Is called directly from cudart api functions
 * e.g., cudaMalloc. Return value is not checked at all.
 */
int hidden_1_3(void* arg1, void* arg2) 
{
    printf("[hidden_1_3] called: arg1 = %p, arg2 = %p\n", arg1, arg2);

    int (*real_func)(void*, void*);
    real_func = (int(*)(void*, void*)) hidden_table_get(1, 3);
    return real_func(arg1, arg2);
}

int hidden_1_4(void* arg1) 
{
    printf("[hidden_1_4] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(1, 4);
    return real_func(arg1);
}

/* called as part of
 * cudart::globalState::initializeDriverInternal()
 * I have no clue what this does and whether the below is correct.
 * The calling function seems to do not much else than check that the pointers are
 * non-NULL (better verify this before assuming this statement is correct).
 */
void hidden_1_5(int64_t * arg1, uint64_t * arg2) 
{
    printf("[hidden_1_5] called: arg1 = %p, arg2 = %p\n", arg1, arg2);
    printf("[hidden_1_5] arg1 = %ld, arg2 = %lu\n", *arg1, *arg2);
    void (*real_func)(int64_t*, uint64_t*);
    real_func = (void(*)(int64_t*,uint64_t*)) hidden_table_get(1, 5);
    real_func(arg1, arg2);
    printf("[hidden_1_5] result = %d\n", *arg2);
}


int hidden_2_0(void* arg1) 
{
    printf("[hidden_2_0] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(2, 0);
    return real_func(arg1);
}

/* parameter seems correct. Is called directly from cudart api functions
 * e.g., cudaMalloc. Return value is not checked at all.
 */
int hidden_2_1(void* arg1)
{
    printf("[hidden_2_1] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(2, 1);
    return real_func(arg1);
}


/* called as part of cudart::contextStateManager::
 * initRuntimeContextState_nonreentrant(cudart::contextState**)
 * the second parameter is a NULL-terminated function pointer array
 * the third parameter is the module (CUmodule*)
 */
int hidden_3_0(int arg1, void** arg2, void** arg3)
{
    printf("[hidden_3_0] called: arg1 = %d, arg2 = %p, arg3 = %p\n", arg1, arg2, arg3);

    int (*real_func)(int, void**, void**);
    real_func = (int(*)(int, void**, void**)) hidden_table_get(3, 0);
    return real_func(arg1, arg2, arg3);
}

/* called as part of cudart::contextStateManager::
 * destroyContextState(cudart::contextState*, bool)
 */
int hidden_3_1(void* arg1, void* arg2)
{
    printf("[hidden_3_1] called: arg1 = %p, arg2 = %p\n", arg1, arg2);

    int (*real_func)(void*, void*);
    real_func = (int(*)(void*, void*)) hidden_table_get(3, 1);
    return real_func(arg1, arg2);

}

/* called as part of cudart::contextStateManager::
 * getRuntimeContextState(cudart::contextState**, bool)
 * This seems to export the Context from driver to runtime
 * The returned context is stored in the first parameter.
 * It returns *arg1=NULL as long as the context is not yet
 * initialized and during intilization.
 * The last parameter points to a NULL-terminated function pointer array
 */
int hidden_3_2(void** arg1, int arg2, void** arg3)
{
    printf("[hidden_3_2] called: arg1 = %p, arg2 = %d, arg3 = %p\n", arg1, arg2, arg3);

    int (*real_func)(void**, int, void**);
    real_func = (int(*)(void**, int, void**)) hidden_table_get(3, 2);
    return real_func(arg1, arg2, arg3);
}


int hidden_4_0(void* arg1) 
{
    printf("[hidden_4_0] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(4, 0);
    return real_func(arg1);
}

int hidden_4_1(void* arg1) 
{
    printf("[hidden_4_1] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(4, 1);
    return real_func(arg1);
}

unsigned int hidden_4_2(char * arg1,char * arg2,int64_t arg3) 
{
    printf("[hidden_4_2] called: arg1 = %p, arg2 = %02x, arg3 = %ld\n", arg1, (*(arg2+1))&0xff, arg3);

    unsigned int (*real_func)(char * ,char*,int64_t);
    real_func = (unsigned int(*)(char * ,char *,int64_t)) hidden_table_get(4, 2);
    unsigned int result=real_func(arg1,arg2,arg3);
    printf("[hidden_4_2] result = %u\n", result);
    return result;
}

int hidden_4_3(void* arg1) 
{
    printf("[hidden_4_3] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(4, 3);
    return real_func(arg1);
}

int64_t hidden_5_0(uint64_t arg1,time_t  arg2, char* arg3) 
{
    printf("[hidden_5_0] called: arg1 = %ld arg2 = %ld, arg3 = %p\n", arg1, arg2, arg3);

    int64_t (*real_func)(uint64_t, time_t, char*);
    real_func = (int64_t (*)(uint64_t,time_t,char*)) hidden_table_get(5, 0);
    int64_t result= real_func(arg1,arg2,arg3);
    printf("[hidden_5_0] result = %ld\n", result);
    return result;
}

int hidden_5_1(void* arg1) 
{
    printf("[hidden_5_1] called: arg1 = %p\n", arg1);

    int (*real_func)(void*);
    real_func = (int(*)(void*)) hidden_table_get(5, 1);
    return real_func(arg1);
}
