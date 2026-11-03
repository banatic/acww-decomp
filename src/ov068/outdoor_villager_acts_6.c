/* outdoor_villager_acts_6: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02267c34 @ 0x02267c34, 0x128 bytes, Thumb
 * func_ov068_02267b8c @ 0x02267b8c, 0xa8 bytes, Thumb
 * func_ov068_02267b3c @ 0x02267b3c, 0x50 bytes, Thumb
 * func_ov068_02267b0c @ 0x02267b0c, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_02267c34 UnkStruct_02267c34;

struct UnkStruct_02267c34 {
    char pad_00[0x5c];
    Vec unk_5C;
    char pad_68[0x334 - 0x68];
    int unk_334;
    char pad_338[0x558 - 0x338];
    int unk_558;
    char pad_55C[0x564 - 0x55c];
    int unk_564;
    char pad_568[0x83c - 0x568];
    int unk_83C;
    char pad_840[0x898 - 0x840];
    int unk_898;
    char pad_89C[0x9b4 - 0x89c];
    int unk_9B4;
    char pad_9B8[0xa0c - 0x9b8];
    int unk_A0C;
};

typedef struct UnkStruct_02267c34_2 UnkStruct_02267c34_2;

struct UnkStruct_02267c34_2 {
    char pad_00[0x38];
    u8 unk_38;
    char pad_39;
    u16 unk_3A;
};

typedef struct {
    char pad_00[0x1c];
    unsigned char unk_1C;
    int unk_20;
} UnkStruct_02267b3c;

typedef struct {
    char pad_00[0x564];
    char unk_564;
} UnkStruct_02267b3c_2;

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad_24[0x16];
    unsigned short unk_3A;
} UnkStruct_02267b0c;

extern unsigned short data_020c80f8;
extern short data_020c80f0;
extern Vec data_021fbee8;
extern int data_020c814c;
extern void func_ov068_0226cfd4(UnkStruct_02267c34 *b);
extern void func_0201651c(void *p, int a);
extern void func_ov068_02266c34(void *p, UnkStruct_02267c34 *b, int c, int d, int e, Vec *f, int g, int h, int i);
extern void func_0202e188(UnkStruct_02267c34 *b);
extern void func_02013c0c(void *p);
extern void func_02012444(void *p, int a, int b);
extern void func_0203edd0(UnkStruct_02267c34 *b);
extern void *func_02096190(int a);
extern s32 func_0201c2b0(UnkStruct_02267c34 *b, void *p);
extern int func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_0201cbbc(void *p);
extern int func_020164a0(void *p, int n);
extern int func_0203e0a8(void *p, int n);
extern int func_02019de8(void *p);
extern int func_0201c2c8(void *p, int n);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0203eddc(void *p);
extern void func_ov068_0226cce8(void *self, void *other, int n);
extern int func_02019e00(void *);
extern int func_02019c6c(void *, int, unsigned short);

int func_ov068_02267c34(UnkStruct_02267c34_2 *a, UnkStruct_02267c34 *b)
{
    int r6;
    u16 r7;

    func_ov068_0226cfd4(b);
    func_0201651c(&b->unk_334, 0);
    func_ov068_02266c34(&b->unk_898, b, 1, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    func_0202e188(b);
    func_02013c0c(&b->unk_558);

    r7 = data_020c80f8;
    func_02012444(&b->unk_9B4, r7, 0);

    if (a->unk_3A == 0) {
        a->unk_38 = 0;
    }
    a->unk_38++;

    r6 = 0xeb;
    if (a->unk_38 >= 3) {
        r6 = 0xec;
        func_0203e0a8((void *) b, 0);
        b->unk_A0C = 1;
        func_0203edd0(b);
        a->unk_38 = 3;
    } else {
        Vec *q = &b->unk_5C;
        volatile Vec v;
        void *p;
        v.x = b->unk_5C.x;
        v.y = q->y;
        v.z = q->z;

        p = func_02096190(4);
        if (p != 0) {
            s32 val = func_0201c2b0(b, p);
            if (val < 0) {
                val = (s16) -val;
            }
            if (val < data_020c80f0) {
                r6 = 0xec;
            }
        }
    }

    func_02019c20(&b->unk_564, 1, r6, 1, r7, 0);
    func_0201cbbc(&b->unk_83C);
    return 1;
}

void func_ov068_02267b8c(void *self, void *other)
{
    if (func_020164a0((unsigned char *) other + 0x334, 0) == 0xeb ||
        func_020164a0((unsigned char *) other + 0x334, 0) == 0xec) {
        if (((unsigned char *) self)[0x38] >= 3) {
            func_0203e0a8(other, 0);
        }
        if (func_02019de8((unsigned char *) other + 0x564) != 0) {
            if (((unsigned char *) self)[0x38] >= 3) {
                int result = func_0201c2c8(other, 4);
                func_02019d0c((unsigned char *) other + 0x564, 3, 1, 0, 0, 0, result, 0, 0, data_020c80f8, 0);
                ((unsigned char *) self)[0x1c] = 1;
            } else {
                func_0203eddc(other);
                func_ov068_0226cce8(self, other, 0);
                *(unsigned short *) ((unsigned char *) self + 0x3a) = 0x4b0;
            }
        }
    }
}

void func_ov068_02267b3c(UnkStruct_02267b3c *out, UnkStruct_02267b3c_2 *in)
{
    func_0203e0a8(in, 0);
    if (func_02019e00(&in->unk_564) == 3) {
        if (func_02019de8(&in->unk_564) != 0) {
            func_02019c6c(&in->unk_564, 1, data_020c80f8);
            out->unk_20 = 0x28;
            out->unk_1C = 2;
        }
    }
}

void func_ov068_02267b0c(UnkStruct_02267b0c *obj, int param2)
{
    if (obj->unk_20 == 0) {
        obj->unk_3A = 0x4b0;
        func_ov068_0226cce8((void *) obj, (void *) param2, 0);
        func_0203eddc((void *) param2);
    } else {
        func_0203e0a8((void *) param2, 0);
    }
}
