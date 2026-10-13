/* func_020a67d8 @ 0x020a67d8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the data_020ccf94->idx load chain before self + 0x2c is formed; without it the add comes first */

#include "types.h"

typedef struct UnkStruct_020a67d8 {
    u8 pad_00[0x64];
    u32 idx;
} UnkStruct_020a67d8;
typedef struct UnkStruct_020a67d8_2 {
    u8 pad_00[0x2c];
    void *arr[1];
} UnkStruct_020a67d8_2;
extern UnkStruct_020a67d8 *data_020ccf94;
void func_020a76d8(void **p, u32 *out);
void func_020a76d0(void **p);
void func_02073820(UnkStruct_020a67d8 *obj);
void func_020737f0(UnkStruct_020a67d8 *obj, u8 *data, int n);
void func_02073770(UnkStruct_020a67d8 *obj, int a, int b);
void func_020a67d8(UnkStruct_020a67d8_2 *self)
{
    u8 ch;
    u32 idx;
    u32 val;
    UnkStruct_020a67d8 *ptr;
    u32 *ptr2;
    UnkStruct_020a67d8 *obj;
    void **ptr3;
    UnkStruct_020a67d8 **ptr4;
    void **ptr5;
    void **p;
    idx = data_020ccf94->idx;
    if ((!ptr3) && (!ptr3)) {
    }
    ptr5 = (void **) ((((char *) self) + 0x2c) + (idx * 4));
    p = ptr5;
    ptr3 = p;
    ptr2 = &val;
    func_020a76d8(ptr3, ptr2);
    if (val != 0) {
        ch = (u8) val;
        ptr4 = &data_020ccf94;
        obj = *ptr4;
        func_02073820(obj);
        ptr = obj;
        func_020737f0(obj, &ch, 1);
        func_02073770(ptr, 0xa, 0);
        func_020a76d0(ptr3);
    }
}
