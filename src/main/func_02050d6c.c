/* func_02050d6c @ 0x02050d6c, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02137550(void *a, int b);
extern char data_020dcf28;
extern char data_021c8230;

struct Pair {
    u32 a;
    u32 b;
};

struct UnkStruct_02050d6c {
    u32 unk_00;
    u32 unk_04;
    struct Pair pair;
    u32 unk_10;
    u32 pad_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u8 unk_38;
    u8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    u8 unk_3C;
    u8 unk_3D;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    u32 unk_4C;
    u32 unk_50;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u32 unk_58;
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u8 unk_74;
    u8 unk_75;
    u32 unk_78;
};

struct UnkStruct_02050d6c *func_02050d6c(struct UnkStruct_02050d6c *o, u32 a1, u32 a2, u32 a3)
{
    u8 local[8];
    u8 *p;

    o->unk_00 = (u32) &data_020dcf28;
    o->unk_04 = 0;
    p = func_02137550(local, 8);
    o->pair = *(struct Pair *) p;
    o->unk_10 = 0;
    o->unk_18 = a1;
    o->unk_1C = 0;
    o->unk_20 = a2;
    o->unk_24 = a3;
    o->unk_28 = (u32) &data_021c8230;
    o->unk_2C = 2;
    o->unk_30 = 0;
    o->unk_34 = 1;
    o->unk_38 = 1;
    o->unk_39 = 0xf;
    o->unk_3A = 0;
    o->unk_3B = 0;
    o->unk_3C = 0;
    o->unk_3D = 0;
    o->unk_40 = 0;
    o->unk_44 = 0;
    o->unk_48 = 0;
    o->unk_4C = 0;
    o->unk_50 = 1;
    o->unk_54 = 0;
    o->unk_55 = 0;
    o->unk_56 = 0;
    o->unk_57 = 0;
    o->unk_58 = 0;
    o->unk_5C = (u32) -1;
    o->unk_60 = a2 << 5;
    o->unk_64 = (u32) -1;
    o->unk_68 = 0;
    o->unk_6C = 0;
    o->unk_70 = 0;
    o->unk_74 = 1;
    o->unk_75 = 0;
    o->unk_78 = 0;
    return o;
}
