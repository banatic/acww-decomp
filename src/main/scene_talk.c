/* scene_talk: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02014a44 @ 0x02014a44, 0x24 bytes, Thumb
 * func_02014a20 @ 0x02014a20, 0x24 bytes, Thumb
 * func_020149c4 @ 0x020149c4, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02014a20 {
    char pad_00[0x14];
    int unk_14;
} UnkStruct_02014a20;

typedef struct UnkStruct_02014a20_2 {
    char pad_00[0x40];
    UnkStruct_02014a20 *unk_40;
    char pad_44[0x60];
    unsigned char unk_A4;
    char pad_A5[0x7];
    unsigned char unk_AC;
} UnkStruct_02014a20_2;

struct Other {
    u32 pad_00;
    u32 unk_04;
};

struct UnkStruct_020149c4 {
    u32 unk_00;
    u32 w1;
    u32 w2;
};

struct Big {
    u8 pad_00[0x40];
    struct Other *other;
    u8 pad_44[0x55 - 0x44];
    u8 unk_55;
    u8 pad_56[0x5c - 0x56];
    struct UnkStruct_020149c4 sub;
    u8 pad_68[0xac - 0x68];
    u8 unk_AC;
};

struct Arg {
    u32 a;
    u32 b;
    u32 c;
};

extern int func_0201596c(void *ptr, int id);
extern struct Big *func_02015d78(struct Big *self, u8 value);
extern int func_0203ae28(struct Arg *arg);

int func_02014a44(unsigned char *data, unsigned char val)
{
    if (func_0201596c(data, 0xB)) {
        data[0xA4] = val;
        return 1;
    }
    return 0;
}

int func_02014a20(UnkStruct_02014a20_2 *arg)
{
    if (arg->unk_40) {
        arg->unk_40->unk_14 = 2;
        if (arg->unk_A4) {
            arg->unk_AC = 1;
        } else {
            arg->unk_AC = 2;
        }
    }
    return 0;
}

int func_020149c4(struct Big *self)
{
    u8 v;
    struct Arg arg;
    struct Big *r;
    struct UnkStruct_020149c4 *p;
    u32 w1;

    if (self->other != 0) {
        if (self->other->unk_04 == 5) {
            v = self->unk_55;
            r = func_02015d78(self, (u8) ((v + 1) & 1));
            if (r != 0) {
                p = &r->sub;
                arg.a = r->sub.unk_00;
                w1 = p->w1;
                arg.b = w1;
                arg.c = p->w2;
                arg.b = w1 + 0x2000;
                func_0203ae28(&arg);
            }
            self->unk_AC = 2;
        }
    }
    return 0;
}
