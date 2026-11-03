/* text_box: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02050d6c @ 0x02050d6c, 0xb8 bytes, Thumb
 * func_02050cb4 @ 0x02050cb4, 0xb8 bytes, Thumb
 * func_02050ca8 @ 0x02050ca8, 0xc bytes, Thumb
 * func_02050c90 @ 0x02050c90, 0x18 bytes, Thumb
 * func_02050c84 @ 0x02050c84, 0xc bytes, Thumb
 */

#include "types.h"

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

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    void *unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char unk_3A;
    unsigned char unk_3B;
    unsigned char unk_3C;
    unsigned char unk_3D;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned char unk_54;
    unsigned char unk_55;
    unsigned char unk_56;
    unsigned char unk_57;
    int unk_58;
    int unk_5C;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    unsigned char unk_74;
    unsigned char unk_75;
    int unk_78;
} UnkStruct_02050cb4;

typedef struct {
    int x;
    int y;
} Pair;

extern void *func_02137550(void *a, int b);
extern char data_021c8230;
extern void func_020edb3c(void *self);
extern unsigned char data_020dcf28[];

struct UnkStruct_02050d6c *func_02050d6c(struct UnkStruct_02050d6c *o, u32 a1, u32 a2, u32 a3)
{
    u8 local[8];
    u8 *p;

    o->unk_00 = (u32) ((char *) data_020dcf28);
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

UnkStruct_02050cb4 *func_02050cb4(UnkStruct_02050cb4 *self, int p1, int p2, int p3)
{
    int local[2];
    int *src;

    self->unk_00 = ((char *) data_020dcf28);
    self->unk_04 = 0;

    src = func_02137550(local, 8);
    *(Pair *) &self->unk_08 = *(Pair *) src;

    self->unk_10 = 0;
    self->unk_18 = -1;
    self->unk_1C = p1;
    self->unk_20 = p2;
    self->unk_24 = p3;
    self->unk_28 = &data_021c8230;
    self->unk_2C = 5;
    self->unk_30 = 0;
    self->unk_34 = 1;

    self->unk_38 = 1;
    self->unk_39 = 0xf;
    self->unk_3A = 0;
    self->unk_3B = 0;
    self->unk_3C = 0;
    self->unk_3D = 0;

    self->unk_40 = 0;
    self->unk_44 = 0;
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;

    self->unk_54 = 0;
    self->unk_55 = 0;
    self->unk_56 = 0;
    self->unk_57 = 0;

    self->unk_58 = 0;
    self->unk_5C = -1;
    self->unk_60 = p2 << 5;
    self->unk_64 = -1;
    self->unk_68 = 0;
    self->unk_6C = 0;
    self->unk_70 = 0;

    self->unk_74 = 1;
    self->unk_75 = 0;
    self->unk_78 = 0;

    return self;
}

void func_02050ca8(char **p)
{
    *p = ((char *) data_020dcf28);
}

void *func_02050c90(void *self)
{
    *(void **) self = (void *) ((char *) data_020dcf28);
    func_020edb3c(self);
    return self;
}

void func_02050c84(unsigned int *ptr)
{
    *ptr = (unsigned int) data_020dcf28;
}
