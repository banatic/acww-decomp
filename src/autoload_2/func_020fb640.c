/* func_020fb640 @ 0x020fb640, 0x2a4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct UnkStruct_020fb640_2 {
    u16 a;
    u16 b;
    u16 c;
};

struct UnkStruct_020fb640_3 {
    u32 b0_lo : 16;
    u32 b0_t : 1;
    u32 b0_hi : 15;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    struct UnkStruct_020fb640_2 unk_1C;
    u16 unk_22;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    u16 unk_38;
    u16 unk_3A;
    int unk_3C;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    u32 f44_lo : 24;
    u32 f44_a : 2;
    u32 f44_b : 2;
    u32 f44_hi : 4;
    u32 f48_x : 1;
    u32 f48_y : 1;
    u32 f48_hi : 30;
};

struct UnkStruct_020fb640_5 {
    char pad[0x10];
    u32 f10_a : 2;
    u32 f10_b : 2;
    u32 f10_c : 1;
    u32 f10_d : 1;
    u32 f10_hi : 26;
};

struct UnkStruct_020fb640_4 {
    struct UnkStruct_020fb640_3 *hdr;
    char pad[0x14 - 4];
    struct UnkStruct_020fb640_5 *sub;
};

struct UnkStruct_020fb640 {
    int x;
    int y;
    int z;
};

union U68 {
    u32 w;
    struct {
        u8 a;
        u8 b;
    } c;
};

struct UnkStruct_020fb640_6 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    struct UnkStruct_020fb640_4 *unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    short unk_38;
    short unk_3A;
    struct UnkStruct_020fb640_2 unk_3C;
    short unk_42;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    int unk_54;
    short unk_58;
    short unk_5A;
    int unk_5C;
    short unk_60;
    short unk_62;
    short unk_64;
    short unk_66;
    union U68 unk_68;
    char pad_6C[0x78 - 0x6c];
    int unk_78;
    int unk_7C;
    int unk_80;
};

void func_020fb640(struct UnkStruct_020fb640_6 *p, struct UnkStruct_020fb640_4 *a, struct UnkStruct_020fb640 *b)
{
    p->unk_18 = a;
    p->unk_1C = 0;
    p->unk_20 = b->x + p->unk_18->hdr->unk_04;
    p->unk_24 = b->y + p->unk_18->hdr->unk_08;
    p->unk_28 = b->z + p->unk_18->hdr->unk_0C;
    p->unk_2C = p->unk_30 = p->unk_34 = 0;
    p->unk_38 = 0;
    p->unk_3A = 0;
    p->unk_3C = p->unk_18->hdr->unk_1C;
    p->unk_42 = 0;
    p->unk_44 = p->unk_18->hdr->unk_14;
    p->unk_48 = p->unk_18->hdr->unk_18;
    p->unk_4C = p->unk_18->hdr->unk_24;
    p->unk_50 = p->unk_18->hdr->unk_28;
    p->unk_54 = p->unk_18->hdr->unk_2C;
    p->unk_58 = p->unk_18->hdr->unk_3A;
    p->unk_5A = 0x7fff;
    p->unk_68.c.a = p->unk_18->hdr->unk_40;
    p->unk_68.c.b = p->unk_18->hdr->unk_41;
    p->unk_68.w &= ~0x70000;
    p->unk_68.w &= 0x7ffff;
    p->unk_5C = (int) 0x80000000;
    p->unk_60 = (short) (0x1000 << p->unk_18->hdr->f44_a);
    p->unk_62 = (short) (0x1000 << p->unk_18->hdr->f44_b);
    if (p->unk_18->hdr->f48_x) {
        p->unk_60 *= -1;
    }
    if (p->unk_18->hdr->f48_y) {
        p->unk_62 *= -1;
    }
    if (p->unk_18->hdr->b0_t) {
        p->unk_64 = (short) (0x1000 << p->unk_18->sub->f10_a);
        p->unk_66 = (short) (0x1000 << p->unk_18->sub->f10_b);
        if (p->unk_18->sub->f10_c) {
            p->unk_64 *= -1;
        }
        if (p->unk_18->sub->f10_d) {
            p->unk_66 *= -1;
        }
    }
    p->unk_00 = p->unk_04 = 0;
    p->unk_08 = p->unk_10 = 0;
    p->unk_0C = p->unk_14 = 0;
    p->unk_78 = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
}
