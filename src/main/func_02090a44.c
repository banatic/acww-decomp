/* func_02090a44 @ 0x02090a44, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Flags {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
};

struct UnkStruct_02090a44;

typedef void (*OutFunc)(struct UnkStruct_02090a44 *);

struct UnkStruct_02090a44 {
    int unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 pad[3];
    int unk_0C;
    OutFunc unk_10;
    int unk_14;
};

struct In {
    OutFunc func;
    int data;
};

struct Global {
    u8 pad[0x50];
    void *unk_50;
};

extern struct Global *data_021d52c4;
extern int func_020fa190(void *, int, int);

int func_02090a44(struct UnkStruct_02090a44 *out, int arg1, int arg2, int arg3, struct In *src, struct Flags flags)
{
    u8 b = flags.b;
    u8 c = flags.c;
    u8 d = flags.d;
    int ret = 0;

    out->unk_0C = func_020fa190(data_021d52c4->unk_50, arg1, arg2);
    if (out->unk_0C != 0) {
        out->unk_00 = arg1;
        out->unk_08 = 1;
        out->unk_10 = src->func;
        out->unk_14 = src->data;
        out->unk_04 = flags.a;
        out->unk_05 = b;
        out->unk_06 = c;
        out->unk_07 = d;
        src->func(out);
        ret = 1;
    }
    return ret;
}