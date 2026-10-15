/* func_ov096_0229d7d0 @ 0x0229d7d0, 0xa8 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229d7d0 {
    char pad_00[0xbb];
    u8 unk_BB;
} UnkStruct_0229d7d0;

extern int func_ov096_0229e158(void *receiver);
extern int func_0204c120(int, int, int);
extern int func_ov096_0229f55c(void *receiver);
extern void func_ov096_0229fb9c(UnkStruct_0229d7d0 *);
extern void func_ov096_0229f874(UnkStruct_0229d7d0 *, int, int, int);
extern void func_ov096_0229e0f8(UnkStruct_0229d7d0 *, int);
extern unsigned char *func_ov096_0229f8cc(UnkStruct_0229d7d0 *, int, int, int, int);

void func_ov096_0229d7d0(UnkStruct_0229d7d0 *o)
{
    int v;
    int w;

    switch (o->unk_BB) {
        case 0xb:
            v = func_0204c120(func_ov096_0229e158(o), 0, 0);
            break;
        case 0xc:
            v = func_0204c120(100, 0, 0);
            break;
        case 0xd:
            v = func_0204c120(1000, 0, 0);
            break;
        case 0xe:
            v = func_0204c120(10000, 0, 0);
            break;
    }
    w = func_ov096_0229f55c(o);
    if (w == 0x26) {
        func_ov096_0229fb9c(o);
        func_ov096_0229f874(o, 0xc, 0xff, 1);
    } else {
        func_ov096_0229e0f8(o, v);
        func_ov096_0229f8cc(o, 0x25, w, v, 0);
    }
}
