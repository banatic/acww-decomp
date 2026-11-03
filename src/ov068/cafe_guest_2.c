/* cafe_guest_2: 7 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022740f8 @ 0x022740f8, 0x6 bytes, Thumb
 * func_ov068_02273ff0 @ 0x02273ff0, 0x108 bytes, Thumb
 * func_ov068_02273eb0 @ 0x02273eb0, 0x140 bytes, Thumb
 * func_ov068_02273c7c @ 0x02273c7c, 0x234 bytes, Thumb
 * func_ov068_02273b70 @ 0x02273b70, 0x10c bytes, Thumb
 * func_ov068_02273b18 @ 0x02273b18, 0x58 bytes, Thumb
 * func_ov068_02273b04 @ 0x02273b04, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[184];
    unsigned long unk_B8;
} UnkStruct_022740f8;

typedef struct UnkStruct_02273ff0 {
    u8 pad_00[0x652];
    u16 unk_652;
    u32 unk_654;
    u8 pad1[0x730 - 0x658];
    u32 unk_730;
    u8 unk_734[0x14];
    u16 unk_748;
    u8 pad_74A[0x74b - 0x74a];
    u8 unk_74B;
} UnkStruct_02273ff0;

typedef struct UnkStruct_02273ff0_2 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad1[0xb4 - 0x44];
    UnkStruct_02273ff0 *base;
} UnkStruct_02273ff0_2;

typedef struct InitRet {
    u8 pad_00[4];
    u32 unk_04;
} InitRet;

typedef struct UnkStruct_02273eb0 {
    u8 pad_00[0x652];
    u16 unk_652;
    u32 unk_654;
    u8 pad1[0x748 - 0x658];
    u16 unk_748;
    u8 pad_74A[0x74b - 0x74a];
    u8 unk_74B;
} UnkStruct_02273eb0;

typedef struct UnkStruct_02273eb0_2 {
    u8 pad_00[0xb4];
    UnkStruct_02273eb0 *base;
    u8 pad1[0xd0 - 0xb8];
    u8 unk_D0;
} UnkStruct_02273eb0_2;

typedef struct {
    signed char unk_00;
    signed char unk_01;
    signed char unk_02;
    signed char unk_03;
    signed char unk_04;
    unsigned char pad_05[3];
    int unk_08;
} Other;

typedef struct {
    unsigned char pad_00[0xb4];
    void *unk_B4;
    unsigned char pad_B8[4];
    signed char unk_BC;
    signed char unk_BD;
    signed char unk_BE;
    signed char unk_BF;
    signed char unk_C0;
    unsigned char pad_C1[0xf];
    unsigned char unk_D0;
} UnkStruct_02273c7c;

typedef struct UnkStruct_02273b70 {
    u8 pad_00[0x652];
    u16 unk_652;
    u32 unk_654;
    u8 pad1[0x730 - (0x654 + 4)];
    u32 unk_730;
    u8 pad2[0x748 - (0x730 + 4)];
    u16 unk_748;
    u8 unk_74A;
    u8 unk_74B;
} UnkStruct_02273b70;

typedef struct UnkStruct_02273b70_2 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad1[0xb4 - (0x40 + 4)];
    UnkStruct_02273b70 *sub;
} UnkStruct_02273b70_2;

typedef struct UnkStruct_02273b70_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
    u16 unk_04;
    u16 pad2;
} UnkStruct_02273b70_3;

struct UnkStruct_02273b18 {
    u8 pad_00[0x40];
    u32 *unk_40;
    u8 pad_44[0x70];
    u32 unk_B4;
};

extern void *func_0206fc44(void);
extern void MI_CpuCopy8(void *dst, const void *src, u32 size);
extern void *func_02062fbc(void *p);
extern void *func_02062e50(void *p);
extern void func_020a8874(void *dst, const void *src, u32 count);
extern int func_020a8a70(void *a, void *b, u32 c, u32 d);
extern void func_020683b4(void *a, u32 b, void *c, u32 d);
extern int func_0206fc6c(void);
extern u32 func_0206fc8c(void);
extern void func_02015de4(UnkStruct_02273ff0_2 *self, u16 *half, u32 a, u32 b);
extern u16 func_ov068_02273980(void);
extern void func_0206844c(void *a, void *b, u32 c);
extern void *func_02062e00(void *p);
extern void *func_02062f4c(void *p);
extern u32 data_ov068_02277ca4[];
extern InitRet *func_020682e0(int);
extern void func_02064da0(int, int);
extern void func_02064db8(int, int, int);
extern void func_0201acbc(void *, int, int, int, int, int);
extern int func_020e8840(void *);
extern void func_ov004_02246ea8(void);
extern int func_020644cc(int);
extern s16 *func_0209d358(int, int);
extern void func_020356c4(int, int, int, int);
extern void func_ov004_02246a2c(void);
extern Other *func_0200420c(void);
extern void func_ov004_02246a04(void);
extern void func_ov004_02246e88(void);
extern void func_ov004_0224692c(void);
extern void func_ov004_02246e98(void);
extern void func_0201a038(void *dst, void *src);
extern void func_020542e0(void *ptr);
extern int func_02019c20(void *ptr, int a, int b, int c, int d, int e);
extern int func_02019c6c(void *ptr, int a, int b);
extern void func_0201a028(void *ptr);
extern int func_ov004_02246900(void);
extern void func_ov004_02246954(int a);
extern void func_ov004_022469dc(void);
extern void *data_ov068_02277b94[];
extern void *data_ov068_022779a8;
extern volatile unsigned short data_020c80f8;
extern int func_0209a000(void *, int _x);
extern int func_0202ea80(int, int);
extern void func_ov004_02246988(void);
extern void func_02035638(u16);

void func_ov068_022740f8(UnkStruct_022740f8 *p, unsigned long v)
{
    p->unk_B8 = v;
}

void func_ov068_02273ff0(UnkStruct_02273ff0_2 *self)
{
    u8 byte0;
    u16 half0;
    u8 buf1[0x28];
    u8 buf2[0x24];
    u32 ret;
    u16 val;

    MI_CpuCopy8(func_0206fc44(), self->base->unk_734, 0x14);
    func_02062fbc(buf1);
    func_02062e50(buf2);
    func_020a8874(buf2, self->base->unk_734, 10);
    func_020a8a70(buf1, buf2, 0, 0);
    func_020683b4(self->unk_40, 0, buf1, 7);

    if (func_0206fc6c() != 0) {
        self->base->unk_74B = 0;
        ret = func_0206fc8c();
        if (ret < 70) {
            val = (u16) (ret + 0x1323);
        } else {
            val = 0x1323;
        }
        self->base->unk_652 = val;
        half0 = self->base->unk_652;
        func_02015de4(self, &half0, 1, 7);
    } else {
        self->base->unk_74B = 1;
        self->base->unk_652 = ((void) *(UnkStruct_02273ff0 *volatile *) &self->base, func_ov068_02273980());
    }

    byte0 = 8;
    func_0206844c(self->unk_40, &byte0, data_ov068_02277ca4[self->base->unk_730]);
    func_02062e00(buf2);
    func_02062f4c(buf1);
}

void func_ov068_02273eb0(UnkStruct_02273eb0_2 *self)
{
    volatile unsigned char _frame[8];
    u16 val;
    u32 result;

    (void) &_frame;
    if (func_020682e0(0)->unk_04 != 5) {
        return;
    }

    if (self->base->unk_748 == 0x2d) {
        func_02064da0(0, 30);
        func_02064db8(1, 1, 0);
        func_0201acbc((void *) ((char *) self->base + 0x3b0), 0, 0xfffff3e8, 0, 0x276, 0x276);
    }

    if (func_020e8840(&self->base->unk_748) != 0) {
        return;
    }

    func_ov004_02246ea8();
    self->base->unk_654 = 0;

    if (self->base->unk_74B != 0) {
        self->base->unk_654 = func_020644cc(3) + 0xa9;

        if (*func_0209d358(0, 0x4e) != 0) {
            int idx;
            idx = *func_0209d358(0, 0x4e) - 1;
            if (idx < 0) {
                idx = 0;
            } else if (idx > 3) {
                idx = 3;
            }
            self->base->unk_654 = idx + 0xa9;
        }
    } else {
        val = self->base->unk_652;
        if (val >= 0x1323 && val <= 0x1368) {
            result = val - 0x1323;
        } else {
            result = -1;
        }

        self->base->unk_654 = result + 0x63;
    }

    func_020356c4(0xf, (u16) self->base->unk_654, 0x7f, 0);
    self->unk_D0 = 0;
    func_ov004_02246a2c();
    func_ov068_022740f8((UnkStruct_022740f8 *) self, 3);
}

void func_ov068_02273c7c(UnkStruct_02273c7c *self)
{
    int val;
    Other *other = func_0200420c();
    func_ov004_02246a04();
    if (other != 0) {
        if (!((other->unk_03 == 1) && (self->unk_BF == 1))) {
            if (other->unk_04 == self->unk_C0) {
            } else if (other->unk_04 == 2) {
                func_ov004_02246e88();
                func_ov004_0224692c();
            } else if (((unsigned char) other->unk_04) <= 1) {
                func_ov004_02246e98();
            }
            if (other->unk_01 == self->unk_BD) {
            } else if (other->unk_01 == (-1)) {
                func_0201a038(((char *) self->unk_B4) + 0x2ac, &data_ov068_022779a8);
            } else {
                func_0201a038(((char *) self->unk_B4) + 0x2ac, data_ov068_02277b94[other->unk_01]);
            }
            if ((other->unk_02 == self->unk_BE) && (other->unk_00 == self->unk_BC)) {
            } else {
                if (other->unk_02 == 1) {
                    func_0201acbc(((char *) self->unk_B4) + 0x3b0, 0, 0, 0, 0x100, 0x200);
                } else {
                    func_0201acbc(((char *) self->unk_B4) + 0x3b0, 0, (int) 0xfffff3e8, 0, 0x100, 0x200);
                }
                val = data_020c80f8;
                if (self->unk_D0 == 0) {
                    val = 0x28;
                    self->unk_D0 = 1;
                }
                if (other->unk_00 == 3) {
                    func_02019c20(((char *) self->unk_B4) + 0x564, 2, 0x103, 0, val, 0);
                } else if (other->unk_00 == 4) {
                    func_02019c20(((char *) self->unk_B4) + 0x564, 2, 0x104, 0, val, 0);
                }
            }
            if (((unsigned char) ((signed char) (other->unk_00 - 3))) <= 1) {
                *((int *) (((char *) self->unk_B4) + 0x190)) = 0;
                *((int *) (((char *) self->unk_B4) + 0x198)) = other->unk_08;
                func_020542e0(((char *) self->unk_B4) + 0xec);
                *((int *) (((char *) self->unk_B4) + 0x198)) = 0;
            }
            if (other->unk_03 != self->unk_BF) {
                if (other->unk_03 == 0) {
                    func_ov004_02246a04();
                    func_ov004_02246954(0);
                    func_ov004_022469dc();
                }
                if (other->unk_03 == 1) {
                    func_0201a038(((char *) self->unk_B4) + 0x2ac, &data_ov068_022779a8);
                    func_0201a028(((char *) self->unk_B4) + 0x2ac);
                    func_02019c6c(((char *) self->unk_B4) + 0x564, 2, 0x28);
                }
            }
        }
    }
    func_ov004_022469dc();
    MI_CpuCopy8(other, (const void *) (&self->unk_BC), 0x14);
    if (func_ov004_02246900() != 0) {
        *((short *) (((char *) self->unk_B4) + 0x748)) = 0x14;
        func_ov068_022740f8((UnkStruct_022740f8 *) self, 4);
    }
}

void func_ov068_02273b70(UnkStruct_02273b70_2 *self)
{
    UnkStruct_02273b70_3 local;

    if (func_020e8840(&self->sub->unk_748) != 0) {
        return;
    }

    self->sub->unk_74A = 0;

    if (self->sub->unk_74B != 0) {
        local.unk_00 = 0xb;
        func_0206844c((void *) self->unk_40, &local.unk_00, data_ov068_02277ca4[self->sub->unk_730]);
    } else {
        local.unk_04 = self->sub->unk_652;
        if (func_0209a000(&local.unk_04, 0) != 0) {
            goto L_funcD;
        }
        local.unk_01 = 0xd;
        func_0206844c((void *) self->unk_40, &local.unk_01, data_ov068_02277ca4[self->sub->unk_730]);
        goto L_after;
    L_funcD:
        func_0202ea80(0xd, 1);
        local.unk_02 = 0xc;
        func_0206844c((void *) self->unk_40, &local.unk_02, data_ov068_02277ca4[self->sub->unk_730]);
    }
L_after:
    func_ov004_02246988();
    func_02035638((u16) self->sub->unk_654);
    self->sub->unk_748 = 0x1e;
    func_02064da0(1, 1);
    func_02064db8(0, 0x1e, 0);
    func_ov068_022740f8((UnkStruct_022740f8 *) self, 5);
}

void func_ov068_02273b18(struct UnkStruct_02273b18 *self)
{
    if ((__arm int) func_020e8840((void *) (self->unk_B4 + 0x748)) != 0) {
        return;
    }
    func_0201acbc((void *) (self->unk_B4 + 0x3b0), 0, 0, 0x1000, 0x276, 0x276);
    self->unk_40[2] = 1;
    func_ov068_022740f8((UnkStruct_022740f8 *) self, 0);
}

int func_ov068_02273b04(int *p)
{
    int r = 0;
    if (p[0x196] == 0) {
        r = 1;
    }
    return r;
}
