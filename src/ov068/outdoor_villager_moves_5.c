/* outdoor_villager_moves_5: 6 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02268df8 @ 0x02268df8, 0x148 bytes, Thumb
 * func_ov068_02268ddc @ 0x02268ddc, 0x1c bytes, Thumb
 * func_ov068_02268d54 @ 0x02268d54, 0x88 bytes, Thumb
 * func_ov068_02268d04 @ 0x02268d04, 0x50 bytes, Thumb
 * func_ov068_02268c84 @ 0x02268c84, 0x80 bytes, Thumb
 * func_ov068_02268c30 @ 0x02268c30, 0x54 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec pos;
    Vec pos2;
    char pad_74[0x8e - 0x74];
    short unk_8E;
    char pad_90[4];
    short unk_94;
    char pad_96[0x350 - 0x96];
    char unk_350[0x564 - 0x350];
    char unk_564[0x83c - 0x564];
    char unk_83C[0x898 - 0x83c];
    char unk_898[0xa0c - 0x898];
    int unk_A0C;
} UnkStruct_02268df8;

typedef struct {
    fx32 x, y, z;
} Vec_02268c84;

typedef struct {
    fx32 x;
    volatile fx32 y;
    fx32 z;
} VecV;

typedef struct {
    char pad_00[0x1c];
    unsigned char unk_1C;
    char pad_1D[3];
    int unk_20;
} UnkStruct_02268c84;

typedef struct {
    unsigned char unk_00[0x1c];
    unsigned char unk_1C;
    unsigned char unk_1D[3];
    unsigned int unk_20;
} UnkStruct_02268c30;

extern void *data_021c80bc;          // 0x021c80bc
extern unsigned short data_020c80f8; // 0x020c80f8
extern const int data_021fbee8[];    // 0x021fbee8
extern int data_020c814c;            // 0x020c814c
extern int func_0204f490(void *, int *, int *, int *, int *, unsigned short *, unsigned short *, int, int);
extern void func_0204f778(Vec *, int, int, int, int);
extern int func_0200322c(Vec *, Vec *);
extern void func_0201aff4(void *, int);
extern int func_02019c6c(void *, int, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, const void *, int, int, int);
extern void func_02035684(int, int, int);
extern void func_020791a4(int);
extern void func_0201cbbc(void *);
extern void func_0203e2ec(void);
extern int func_0203e0a8(int a, int b);
extern int func_02095ea4(int a, int b);
extern int func_02016104(void *);
extern int func_0201c314(unsigned char *, int);
extern void func_02013c0c(void *);
extern int func_020147fc(void *, int, int, int);
extern int func_02014868(void *ptr);
extern int func_0203b144(void);
extern int func_02019d0c(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_0203e020(const unsigned char *p);
extern void func_0203e2e0(void);

int func_ov068_02268df8(void *self, UnkStruct_02268df8 *obj)
{
    unsigned short ids[2];
    int a, b, c, d;
    Vec v1;
    Vec v2;
    void *g;
    Vec *dp;
    Vec *dp2;

    g = data_021c80bc;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    if (g == 0) {
        goto tail;
    }
    ids[0] = 0x5014;
    ids[1] = 0x501a;
    if (func_0204f490(g, &a, &b, &c, &d, &ids[0], &ids[1], 1, 0) == 0) {
        goto tail;
    }
    v2.x = 0;
    v2.y = 0;
    v2.z = 0;
    func_0204f778(&v2, a, b, c, d);
    v1.x = v2.x;
    v1.y = v2.y;
    v1.z = v2.z;
    v1.x = v2.x - 0x2000;
    v1.z = v2.z + 0x8000;
    v1.y = 0;
    dp = &obj->pos;
    dp->x = v1.x;
    dp->y = v1.y;
    dp->z = v1.z;
    dp2 = &obj->pos2;
    dp2->x = dp->x;
    dp2->y = dp->y;
    dp2->z = dp->z;
    obj->unk_8E = (short) func_0200322c(&v1, &v2);
    obj->unk_94 = obj->unk_8E;
    func_0201aff4(obj->unk_350, obj->unk_8E);
tail:
    obj->unk_A0C = 0;
    func_02019c6c(obj->unk_564, 1, data_020c80f8);
    func_ov068_02266c34(obj->unk_898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_02035684(0x12, 0xf, 0);
    func_020791a4(-1);
    func_0201cbbc(obj->unk_83C);
    func_0203e2ec();
    return 1;
}

int func_ov068_02268ddc(int a, int b)
{
    func_0203e0a8(b, 0);
    func_02095ea4(0x1d, 4);
    return 0;
}

int func_ov068_02268d54(char *self, unsigned char *obj)
{
    int a, b;

    a = func_02016104(obj + 0x680);
    b = 0;
    if (a != 0) {
        b = func_0201c314(obj, a);
    }
    func_02013c0c(obj + 0x558);
    func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(obj + 0x618, 0, b, 1);
    func_0201cbbc(obj + 0x83c);
    self[0x1c] = 0;
    return 1;
}

void func_ov068_02268d04(void *self, void *base)
{
    if (func_02014868((char *) base + 0x618) != 0) {
        return;
    }
    func_0203b144();
    func_02019d0c((char *) base + 0x564, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(unsigned char *) ((char *) self + 0x1c) = 1;
}

void func_ov068_02268c84(UnkStruct_02268c84 *a1, void *a2)
{
    VecV v;
    Vec_02268c84 *s;
    if (func_02019e00((char *) a2 + 0x564) == 3) {
        if (func_02019de8((char *) a2 + 0x564) != 0) {
            s = (Vec_02268c84 *) ((char *) a2 + 0x5c);
            v.x = s->x;
            v.y = s->y;
            v.z = s->z;
            v.x = v.x - 0x2000;
            v.z = v.z + 0x8000;
            func_02019d0c((char *) a2 + 0x564, 2, 1, (fx32) v.x, (fx32) v.z, 0, 0, 0, 0, data_020c80f8, 0);
            a1->unk_20 = 0xc8;
            a1->unk_1C = 2;
        }
    }
}

void func_ov068_02268c30(UnkStruct_02268c30 *self, const unsigned char *other)
{
    if ((func_02019e00((void *) (other + 0x564)) == 2 && func_02019de8((void *) (other + 0x564)) != 0) || self->unk_20 == 0) {
        func_0203e020(other);
        func_02019c6c((void *) (other + 0x564), 1, (unsigned short) data_020c80f8);
        func_0203e2e0();
        self->unk_1C = 3;
    }
}
