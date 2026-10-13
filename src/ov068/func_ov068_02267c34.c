/* func_ov068_02267c34 @ 0x02267c34, 0x128 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
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
extern void func_0203e0a8(UnkStruct_02267c34 *b, int a);
extern void func_0203edd0(UnkStruct_02267c34 *b);
extern void *func_02096190(int a);
extern s32 func_0201c2b0(UnkStruct_02267c34 *b, void *p);
extern void func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_0201cbbc(void *p);

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
        func_0203e0a8(b, 0);
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
