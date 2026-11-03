/* scene_motion_kinds_8: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020198bc @ 0x020198bc, 0x8c bytes, Thumb
 * func_020198b0 @ 0x020198b0, 0xc bytes, Thumb
 * func_02019804 @ 0x02019804, 0xac bytes, Thumb
 * func_02019794 @ 0x02019794, 0x70 bytes, Thumb
 * func_020196e8 @ 0x020196e8, 0xac bytes, Thumb
 * func_02019678 @ 0x02019678, 0x70 bytes, Thumb
 * func_020195d8 @ 0x020195d8, 0xa0 bytes, Thumb
 * func_02019594 @ 0x02019594, 0x44 bytes, Thumb
 * func_020194fc @ 0x020194fc, 0x98 bytes, Thumb
 * func_020194c8 @ 0x020194c8, 0x34 bytes, Thumb
 * func_020194c0 @ 0x020194c0, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char pad_06[14];
    unsigned int unk_14;
    unsigned char pad_18[4];
    unsigned int unk_1C;
} UnkStruct_020198bc;

typedef struct {
    u32 pad_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u8 pad_18[2];
    s16 unk_1A;
    u16 unk_1C;
} SrcStruct;

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} StackStruct;

typedef struct {
    u8 pad_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0xe];
    u32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
} ObjStruct;

typedef struct {
    u8 pad_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[14];
    u32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
} UnkStruct_020195d8;

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u16 unk_1C;
} InfoStruct;

typedef struct {
    unsigned int pad_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int pad_14;
    short unk_18;
    short unk_1A;
    unsigned short unk_1C;
} UnkStruct_020194fc;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Vec3;

typedef struct {
    Vec3 unk_04;
    Vec3 unk_10;
} UnkStruct_020194fc_2;

typedef struct {
    char pad_00[0x8E];
    short unk_8E;
    char pad_90[0x2C0];
    char unk_350;
} UnkStruct_020194c8;

typedef struct {
    char pad_00[0x98];
    unsigned char unk_98;
} UnkStruct_020194c8_2;

extern void *func_02019de4(void *a);
extern void func_0201b044(void *a, void *b);
extern void func_0201afd4(void *a, void *b);
extern void func_0201aff4(void *a, int b);
extern void func_0201b350(void *a, int b);
extern void func_02012444(int a, int b, int c);
extern void func_02019af0(void *a, int b);
extern unsigned short data_020c80f8;
extern void func_0201b1a4(void *dst, void *base, int n, int m, u16 p);
extern void func_020123ec(u32 a, u16 b, u32 c);
extern void func_02019ac0(void *dst, u32 a, u32 b, u32 c, u32 d, s16 e, u16 f);
extern void func_0201b188(void *, void *);
extern int func_0201aff8(void *, void *, int);
extern int func_0201afc0(void *);
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, unsigned short, int);
extern void func_02019a58(void *, int, int, int);
extern u8 data_021fbee8[];
extern int func_0201afec(void *);

int func_020198bc(void *first, void *second)
{
    unsigned short hw;
    void *ptr;
    int val;

    ptr = func_02019de4(first);
    hw = *(unsigned short *) ((char *) ptr + 0x1c);
    func_0201b1a4((char *) second + 0x350, second, 0, 0, (unsigned short) hw);
    func_0201b044((char *) second + 0x350, ((unsigned char *) data_021fbee8));
    func_0201afd4((char *) second + 0x350, ((unsigned char *) data_021fbee8));
    func_0201aff4((char *) second + 0x350, *(short *) ((char *) second + 0x8e));
    func_0201b350((char *) second + 0x3aa, -2);

    val = *(int *) ((char *) second + 0x628);
    if (val != 0) {
        func_02012444(val, data_020c80f8, 0);
    }

    ((UnkStruct_020198bc *) first)->unk_04 = (unsigned char) ((UnkStruct_020198bc *) first)->unk_1C;
    ((UnkStruct_020198bc *) first)->unk_05 = (unsigned char) ((UnkStruct_020198bc *) first)->unk_14;
    func_02019af0(first, 0);
    return 0;
}

void func_020198b0(void *self, void *event)
{
    func_02019af0(self, (unsigned long) 1);
}

int func_02019804(ObjStruct *obj, char *base)
{
    StackStruct s[2];
    SrcStruct *src;
    u32 c0, a0, c1, a1;

    src = (SrcStruct *) func_02019de4((void *) ((int) obj));

    c0 = src->unk_08;
    a0 = src->unk_04;
    s[0].a = a0;
    s[0].b = 0;
    s[0].c = c0;

    c1 = src->unk_10;
    a1 = src->unk_0C;
    s[1].a = a1;
    s[1].b = 0;
    s[1].c = c1;

    func_0201b044((void *) (base + 0x350), (void *) (&s[0]));
    func_0201afd4((void *) (base + 0x350), (void *) (&s[1]));

    func_0201b1a4((void *) (base + 0x350), base, 1, src->unk_1A, src->unk_1C);
    func_0201b350((void *) (base + 0x3aa), 1);

    if (*(u32 *) (base + 0x628) != 0) {
        func_020123ec(*(u32 *) (base + 0x628), (*(u16 *) &data_020c80f8), 0);
    }

    obj->unk_04 = (u8) obj->unk_1C;
    obj->unk_05 = (u8) obj->unk_14;

    func_02019ac0((void *) ((char *) obj + 6), src->unk_04, src->unk_08, src->unk_0C, src->unk_10, src->unk_1A, src->unk_1C);
    func_02019af0(obj, 0);

    return 0;
}

void func_02019794(int p0, void *p1)
{
    func_0201b188((char *) p1 + 0x350, p1);
    if (func_0201aff8((char *) p1 + 0x350, p1, 0) != 0) {
        if (func_0201afc0((char *) p1 + 0x350) != 0) {
            void *p = func_02019de4((void *) p0);
            func_02019d0c(p0, 1, 1, ((int *) p)[1], ((int *) p)[2], 0, 0, 0, 0, data_020c80f8, 0);
        } else {
            func_02019af0((void *) p0, 1);
        }
    }
}

int func_020196e8(ObjStruct *obj, char *base)
{
    StackStruct s[2];
    SrcStruct *src;
    u32 c0, a0, c1, a1;

    src = (SrcStruct *) func_02019de4((void *) ((int) obj));

    c0 = src->unk_08;
    a0 = src->unk_04;
    s[0].a = a0;
    s[0].b = 0;
    s[0].c = c0;

    c1 = src->unk_10;
    a1 = src->unk_0C;
    s[1].a = a1;
    s[1].b = 0;
    s[1].c = c1;

    func_0201b044((void *) (base + 0x350), (void *) (&s[0]));
    func_0201afd4((void *) (base + 0x350), (void *) (&s[1]));

    func_0201b1a4((void *) (base + 0x350), base, 2, src->unk_1A, src->unk_1C);
    func_0201b350((void *) (base + 0x3aa), 1);

    if (*(u32 *) (base + 0x628) != 0) {
        func_020123ec(*(u32 *) (base + 0x628), (*(u16 *) &data_020c80f8), 0);
    }

    obj->unk_04 = (u8) obj->unk_1C;
    obj->unk_05 = (u8) obj->unk_14;

    func_02019ac0((void *) ((char *) obj + 6), src->unk_04, src->unk_08, src->unk_0C, src->unk_10, src->unk_1A, src->unk_1C);
    func_02019af0(obj, 0);

    return 0;
}

void func_02019678(int p0, void *p1)
{
    func_0201b188((char *) p1 + 0x350, p1);
    if (func_0201aff8((char *) p1 + 0x350, p1, 0) != 0) {
        if (func_0201afc0((char *) p1 + 0x350) != 0) {
            void *p = func_02019de4((void *) p0);
            func_02019d0c(p0, 1, 1, ((int *) p)[1], ((int *) p)[2], 0, 0, 0, 0, data_020c80f8, 0);
        } else {
            func_02019af0((void *) p0, 1);
        }
    }
}

int func_020195d8(UnkStruct_020195d8 *out, u8 *p)
{
    InfoStruct *info;
    u32 v;

    info = (InfoStruct *) func_02019de4(out);
    func_0201b1a4((u8 *) p + 0x350, p, 3, info->unk_1A, info->unk_1C);
    func_0201aff4((u8 *) p + 0x350, info->unk_18);
    func_0201b044((u8 *) p + 0x350, data_021fbee8);
    func_0201afd4((u8 *) p + 0x350, data_021fbee8);
    func_0201b350((u8 *) p + 0x3aa, -2);

    v = *(u32 *) (p + 0x628);
    if (v != 0) {
        func_020123ec(v, (*(u16 *) &data_020c80f8), 0);
    }

    out->unk_04 = out->unk_1C;
    out->unk_05 = out->unk_14;
    func_02019a58((u8 *) out + 6, info->unk_1A, info->unk_18, info->unk_1C);
    func_02019af0(out, 0);

    return 0;
}

void func_02019594(void *a, void *b)
{
    if (*(short *) ((char *) b + 0x8e) == func_0201afec((char *) b + 0x350)) {
        func_0201b1a4((char *) b + 0x350, b, 0, 0, *(unsigned short *) ((char *) func_02019de4(a) + 0x1c));
        func_02019af0(a, 1);
    }
}

int func_020194fc(void *a, char *b)
{
    UnkStruct_020194fc *p = (UnkStruct_020194fc *) func_02019de4(a);
    UnkStruct_020194fc_2 local;
    int z1, x1, z2, x2;

    z1 = p->unk_08;
    x1 = p->unk_04;
    local.unk_04.x = x1;
    local.unk_04.y = 0;
    local.unk_04.z = z1;

    z2 = p->unk_10;
    x2 = p->unk_0C;
    local.unk_10.x = x2;
    local.unk_10.y = 0;
    local.unk_10.z = z2;

    func_0201b1a4((void *) (b + 0x350), (void *) b, 3, p->unk_1A, (unsigned short) p->unk_1C);
    func_0201b044((void *) (b + 0x350), &local.unk_04);
    func_0201afd4((void *) (b + 0x350), &local.unk_10);
    func_0201aff4((void *) (b + 0x350), (short) p->unk_18);
    func_0201b350((void *) (b + 0x3aa), -2);

    if (*(unsigned int *) (b + 0x628) != 0) {
        func_020123ec(*(unsigned int *) (b + 0x628), (unsigned short) data_020c80f8, 0);
    }

    func_02019af0(a, 0);
    return 0;
}

void func_020194c8(UnkStruct_020194c8_2 *a1, UnkStruct_020194c8 *a2)
{
    if (a2->unk_8E == func_0201afec(&a2->unk_350)) {
        func_02019804((ObjStruct *) a1, (char *) a2);
        a1->unk_98 = 1;
    }
}

void func_020194c0(int argument0, void *argument1)
{
    func_02019794((int) argument0, (void *) argument1);
}
