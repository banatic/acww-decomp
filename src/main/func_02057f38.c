/* func_02057f38 @ 0x02057f38, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int x, y, z;
};

struct UnkStruct_02057f38 {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

struct UnkStruct_02057f38_2 {
    u8 pad_00[0x60];
    struct Vec unk_60;
    struct Vec unk_6C;
    struct Vec unk_78;
    struct Vec unk_84;
    struct Vec unk_90;
    u8 pad_9C[0xcc - 0x9c];
    struct UnkStruct_02057f38 *unk_CC;
    u8 pad_D0[4];
    u8 unk_D4;
    u8 pad_D5;
    u16 unk_D6;
};

extern u8 data_020cbaf4[];
extern struct Vec data_021c9390;

extern void func_0205967c(struct UnkStruct_02057f38_2 *, struct Vec *);
extern void func_020ea6e0(struct Vec *, int);
extern void VEC_Add(struct Vec *, struct Vec *, struct Vec *);
extern void func_020e895c(int *, int, int);
extern int _s32_div_f(int, int);

void func_02057f38(struct UnkStruct_02057f38_2 *o)
{
    int lim;
    int tx, ty, tz;

    lim = data_020cbaf4[1];
    if (o->unk_D6 < lim) {
        func_0205967c(o, &o->unk_6C);
        if (o->unk_CC) {
            o->unk_78.x = data_021c9390.x;
            o->unk_78.y = data_021c9390.y;
            o->unk_78.z = data_021c9390.z;
            func_020ea6e0(&o->unk_78, o->unk_CC->unk_8E);
        }
        VEC_Add(&o->unk_6C, &o->unk_78, &o->unk_6C);
        func_020e895c(&o->unk_60.x, o->unk_6C.x, o->unk_90.x);
        func_020e895c(&o->unk_60.y, o->unk_6C.y, o->unk_90.y);
        func_020e895c(&o->unk_60.z, o->unk_6C.z, o->unk_90.z);
        o->unk_D6++;
        if (o->unk_D6 >= lim) {
            o->unk_6C.x = 0;
            o->unk_6C.y = 0;
            o->unk_6C.z = 0;
            o->unk_84.x = data_021c9390.x;
            o->unk_84.y = data_021c9390.y;
            o->unk_84.z = data_021c9390.z;
            o->unk_78.x = 0;
            o->unk_78.y = 0;
            o->unk_78.z = 0;
            tz = _s32_div_f(o->unk_84.z, 8);
            if (tz < 0) {
                tz = -tz;
            }
            ty = _s32_div_f(o->unk_84.y, 8);
            if (ty < 0) {
                ty = -ty;
            }
            tx = _s32_div_f(o->unk_84.x, 8);
            if (tx < 0) {
                tx = -tx;
            }
            o->unk_90.x = tx;
            o->unk_90.y = ty;
            o->unk_90.z = tz;
            o->unk_D4 = 2;
        }
    }
}
