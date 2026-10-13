/* func_ov066_0226783c @ 0x0226783c, 0xcc bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct S2b {
    u8 pad_00[0x44];
    int unk_44;
};

struct UnkStruct_0226783c {
    u8 pad_00[0x4];
    struct S2b *unk_04;
    u8 pad1[0x64];
    int (*unk_6C)(void *);
};

struct UnkStruct_0226783c_2 {
    u8 pad_00[0x95];
    unsigned char unk_95;
};

struct UnkStruct_0226783c_3 {
    u8 pad_00[0x28];
    int unk_28;
    u8 pad1[0x10];
    signed int : 5;
    signed int b5 : 1;
    signed int b6 : 1;
    signed int b7 : 1;
};

struct Param {
    u8 pad_00[4];
    unsigned char unk_04;
    u8 pad1;
    unsigned char unk_06;
};

extern struct UnkStruct_0226783c_3 *data_ov066_0226bdec;
extern struct UnkStruct_0226783c *data_ov066_0226bdf0;
extern struct UnkStruct_0226783c_2 *data_ov066_0226bdf4;

int func_ov066_0226783c(void *arg0, struct Param *p)
{
    struct UnkStruct_0226783c_3 *s = data_ov066_0226bdec;

    if (s->b5) {
        if (data_ov066_0226bdf0->unk_04->unk_44 != s->unk_28) {
            goto fail;
        }
    }
    if (s->b6) {
        if (p->unk_04 != data_ov066_0226bdf4->unk_95) {
            goto fail;
        }
    }
    if (s->b7) {
        if (p->unk_06 != 5) {
            goto fail;
        }
    }
    if (data_ov066_0226bdf0->unk_6C != 0) {
        goto call_func;
    }
    return 1;
call_func:
    return data_ov066_0226bdf0->unk_6C(arg0);
fail:
    return 0;
}
