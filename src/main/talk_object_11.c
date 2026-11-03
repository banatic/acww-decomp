/* talk_object_11: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067e68 @ 0x02067e68, 0x1c bytes, Thumb
 * func_02067e4c @ 0x02067e4c, 0x1c bytes, Thumb
 * func_02067e04 @ 0x02067e04, 0x48 bytes, Thumb
 * func_02067dbc @ 0x02067dbc, 0x48 bytes, Thumb
 * func_02067d7c @ 0x02067d7c, 0x40 bytes, Thumb
 * func_02067c74 @ 0x02067c74, 0x108 bytes, Thumb
 * func_02067c20 @ 0x02067c20, 0x54 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x1e98];
    unsigned char byte;
} UnkStruct_02067e04;

typedef struct UnkStruct_02067c74 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x14];
    u8 unk_1C[0x80];
    s32 unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} UnkStruct_02067c74;

struct UnkStruct_02067c20 {
    unsigned char pad_00[0x1a64];
    int unk_1A64;
    short unk_1A68;
    short unk_1A6A;
    int unk_1A6C;
    int unk_1A70;
    int unk_1A74;
};

extern void func_020a7e0c(void);
extern void func_020a7dec(void);
extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern void func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e70(void);
extern int func_020a80c4(int a, int b, int c, int d);
extern int func_020a7fd4(void);
extern int func_020a7fac(void);
extern int func_020a7ee4(void);
extern s16 FX_SinCosTable_[];
extern int func_020e88dc(s32 *, s32, s32);
extern s32 FX_MulFunc(s32, s32);
extern void func_02068d44(void *, s32, s32);
extern int func_0209dee8(void);
extern void func_0209df94(short *);
extern void func_0209def4(short *);
extern int func_0209ded0(void);
extern int func_0209dedc(void);
extern int func_0209dcac(void);

void func_02067e68(unsigned char *arg0)
{
    if (arg0[0x1e98] == 0) {
        func_020a7e0c();
    }
}

void func_02067e4c(unsigned char *arg0)
{
    if (arg0[0x1e98] == 0) {
        func_020a7dec();
    }
}

int func_02067e04(UnkStruct_02067e04 *self)
{
    int ret = 0;

    if (self->byte == 0) {
        int a = func_020a7e50();
        if (a != 0) {
            int b = func_020a7ffc();
            if (b != 0) {
                func_020a7e64();
                ret = 1;
            }
        } else {
            int c = func_020a7e44();
            if (c != 0) {
                int d = func_020a812c();
                if (d != 0) {
                    func_020a7e70();
                    ret = 1;
                }
            }
        }
    }

    return ret;
}

int func_02067dbc(unsigned char *param)
{
    int r4 = 0;
    if (param[0x1e98] != 0) {
        goto end;
    }
    if (func_02067e04((UnkStruct_02067e04 *) param) != 0) {
        goto end;
    }
    if (func_020a80c4(8, 0xf8, 0x70, 0xc0) == 0) {
        goto next;
    }
    r4 = 1;
    goto end;
next:
    if (func_020a7fd4() != 0) {
        goto set_r4;
    }
    if (func_020a7fac() == 0) {
        goto end;
    }
set_r4:
    r4 = 1;
end:
    return r4;
}

int func_02067d7c(unsigned char *param)
{
    int result = 0;
    if (param[0x1e98] == 0) {
        if (func_02067e04((UnkStruct_02067e04 *) param) == 0) {
            if (func_020a80c4(8, 0xf8, 0x70, 0xc0) != 0) {
                result = 1;
            } else if (func_020a7ee4() != 0) {
                result = 1;
            }
        }
    }
    return result;
}

static __inline int fsin(s16 a)
{
    return FX_SinCosTable_[(((u16) a) >> 4) * 2 + 1];
}

static __inline int fcos(s16 a)
{
    return FX_SinCosTable_[(((u16) a) >> 4) * 2];
}

void func_02067c74(UnkStruct_02067c74 *p)
{
    int ok;
    int busy;
    s32 m1, m2;
    s16 ang;

    if (p->unk_A4 != 0) {
        ok = (p->unk_04 == 3 || p->unk_04 == 2);
        busy = (func_020e88dc(&p->unk_A4, 0, p->unk_A8) != 0);
        if (ok && !busy) {
            p->unk_A0 = p->unk_A0 + 0x4000;
            m1 = FX_MulFunc(p->unk_A4, p->unk_AC);
            m2 = FX_MulFunc(p->unk_A4, p->unk_B0);
            ang = p->unk_A0;
            m1 = FX_MulFunc(fsin(ang + 0x2000), m1);
            m2 = FX_MulFunc(fcos(ang * 2 - 0x4000), m2);
            func_02068d44(p->unk_1C, -(m1 >> 12), p->unk_9C + (m2 >> 12));
        } else {
            p->unk_A0 = 0;
            p->unk_A4 = 0;
            p->unk_A8 = 0;
            p->unk_AC = 0;
            p->unk_B0 = 0;
            func_02068d44(p->unk_1C, 0, p->unk_9C);
        }
    }
}

void func_02067c20(struct UnkStruct_02067c20 *self)
{
    self->unk_1A64 = func_0209dee8();
    func_0209df94(&self->unk_1A68);
    func_0209def4(&self->unk_1A6A);
    self->unk_1A6C = func_0209ded0();
    self->unk_1A70 = func_0209dedc();
    self->unk_1A74 = func_0209dcac();
}
