#ifndef _CD_CLIENT_HIDDEN_H_
#define _CD_CLIENT_HIDDEN_H_


/* this file is for the hidden function exported from some driver
 * library (presumably) via the cuGetExportTable API (which is undocumented).
 * During initialization cuGetExportTable is called 4 times with different
 * parameters. Each call seems to copy a varying amount of function pointers
 * to the first paramter. The memory for these function pointers is
 * callee allocated and the first element is the length in bytes of the 
 * entire list of pointers. Additionally the last element is NULL.
 * The last call does not provide a length element (Nvidia seems
 * unessecary cruel here)
 *
 * The first call to cuGetExportTable exports 8 function pointers.
 *
 * The second call exports 6 function pointers.
 *
 * The third call exports 2 function pointers.
 *
 * The fourth call exports 3 function pointers.
 *
 * I guess we can assume even these hidden functions adhere to nvidias
 * code style of functions always return cuResult, with 0 being success.
 *
 * To circument thes ugly and mean hack we do a bit of hacking ourselves:
 */

#include <bits/types/time_t.h>
#include <cstdint>
#include <stdlib.h>
#define EXPECT_CALL_CNT 6
#define EXPECT_0 12
#define EXPECT_1 7
#define EXPECT_2 3
#define EXPECT_3 3
#define EXPECT_4 5 
#define EXPECT_5 3

const int expect_elem_cnt[EXPECT_CALL_CNT] = {
    EXPECT_0,
    EXPECT_1,
    EXPECT_2,
    EXPECT_3,
    EXPECT_4,
    EXPECT_5,
};
const int hidden_offset[EXPECT_CALL_CNT] = {
    EXPECT_5+1, // 1 for empty
    EXPECT_5+1 + EXPECT_0+EXPECT_3,
    EXPECT_5+1 + EXPECT_0+EXPECT_3 +EXPECT_1,
    EXPECT_5+1 + EXPECT_0,
    EXPECT_5+1 + EXPECT_0+EXPECT_3 +EXPECT_1+EXPECT_2,
    0,
};

const int expect_elems_total = EXPECT_0+EXPECT_1+EXPECT_2+EXPECT_3+EXPECT_4+EXPECT_5;
void hexdump(const uint8_t* data, size_t size,bool verbose=true);
extern void* hooked_hidden_table[EXPECT_0+EXPECT_1+EXPECT_2+EXPECT_3+EXPECT_4+EXPECT_5+EXPECT_CALL_CNT];


int hidden_0_0(void* arg1);
unsigned int hidden_get_device_ctx(uint64_t* cu_ctx, uint32_t cu_device);
int hidden_0_2(void* arg1);
int hidden_0_3(void* arg1);
int hidden_0_4(void* arg1);
int hidden_get_module(void** arg1, void** arg2, void* arg3, void* arg4, int arg5);
int hidden_0_6(void* arg1);
int hidden_0_7(void * arg1);
int hidden_0_8(void* arg1);
int hidden_0_10(void *arg1);
int hidden_1_0(int arg1, void* arg2);
void hidden_1_1(uint64_t* arg1, uint64_t *arg2);
int hidden_1_2(void* arg1);
int hidden_1_3(void* arg1, void* arg2);
int hidden_1_4(void* arg1);
void hidden_1_5(uint64_t* arg1, uint64_t* arg2);

int hidden_2_0(void* arg1);
int hidden_2_1(void* arg1);

int hidden_3_0(int arg1, void** arg2, void** arg3);
int hidden_3_1(void* arg1, void* arg2);
int hidden_3_2(void** arg1, int arg2, void** arg3);

int hidden_4_0(void* arg1);
int hidden_4_1(int64_t arg1,int * arg2,int64_t * arg3);
// unsigned int hidden_4_2(char * ,void*,int64_t);
unsigned int hidden_4_2(void);
int hidden_4_3(void* arg1);

int32_t hidden_5_0(uint32_t arg1,uint64_t arg2, uint64_t arg3);
int hidden_5_1(void*);

// void hexdump(const uint8_t* data, size_t size,bool verbose=true);
#endif //_CD_CLIENT_HIDDEN_H_
