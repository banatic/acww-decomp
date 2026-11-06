/* sky_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bad44 @ 0x020bad44, 0x11c bytes, Thumb
 * func_020babb4 @ 0x020babb4, 0x190 bytes, Thumb
 * func_020bab74 @ 0x020bab74, 0x40 bytes, Thumb
 * func_020bab04 @ 0x020bab04, 0x70 bytes, Thumb
 * func_020baad8 @ 0x020baad8, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    short unk_08;
    unsigned char pad[0x8f6];
} E_t;

typedef struct {
    unsigned char unk_00;
    unsigned char type;
    unsigned short a;
    unsigned short b;
} UnkStruct_020bad44;

typedef struct {
    unsigned char unk_00;
    unsigned char type;
    unsigned short a;
    unsigned short b;
} UnkStruct_020babb4;

typedef struct {
    u16 pad_00;
    u16 unk_02; // offset 2
    u16 unk_04; // offset 4
} UnkStruct_020bab74;

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
    char pad_20[0x1e];
    short unk_3E;
} UnkStruct_020bab04;

extern void func_0209def4(void *);
extern int func_0206fea4(void);
extern void func_02001afc(unsigned char mask);
extern void func_02001b0c(int arg);
extern struct {
    char pad0[0x1c];
    int idx;
    char pad1[0x1c];
    unsigned short w3c;
    unsigned short w3e;
} data_021f8ab0;
extern int data_021f8ac4[];
extern unsigned char data_021fba88[];
extern struct {
    int pad;
    int idx;
} data_021f75b0;
extern E_t data_021f75b8[];
extern void func_02001b34(int);
extern void func_02001b44(int);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern void func_02001d1c(int);
extern void func_02001cc4(int, int, int, int);
extern unsigned char data_021f70f0[];
extern unsigned char data_021f7270[];
extern void func_020bb090(void);
extern void func_020bae60(void);
extern void func_020bb3a4(int **p);
extern int func_020bbb20(int *p);
extern int func_0206fd34(void);
extern int func_0203adb0(void);
extern int func_020bb1b0(int **p);
extern int data_021c67a4;
extern void func_020bb240(int *p);
extern void func_020bbb6c(int *p, unsigned int *a, unsigned int *b);
extern void func_020bba14(void);

void func_020bad44(void)
{
    int r4;
    UnkStruct_020bad44 tmp;
    E_t *e;

    r4 = data_021f8ac4[data_021f8ab0.idx];

    tmp.a = (*(struct {
                char pad[4];
                unsigned short f4;
                unsigned short f6;
            } *) data_021f7270)
                .f4;
    *(volatile unsigned short *) 0x05000400 = tmp.a;
    tmp.b = (*(struct {
                char pad[4];
                unsigned short f4;
                unsigned short f6;
            } *) data_021f7270)
                .f6;
    *(volatile unsigned short *) 0x05000000 = tmp.b;

    e = &data_021f75b8[data_021f75b0.idx];
    *(volatile unsigned short *) 0x04001030 = e->unk_08;
    *(volatile unsigned int *) 0x04001038 = e->unk_00;
    *(volatile unsigned int *) 0x0400103c = e->unk_04;

    func_0209def4(&tmp);

    if (tmp.type >= 6 && tmp.type < 0x12) {
        volatile unsigned int *p = (volatile unsigned int *) 0x04001000;
        *p = *p & ~0x200;
        if (func_0206fea4() == 0) {
            func_02001afc(2);
        }
    } else {
        unsigned int reg = *(volatile unsigned int *) 0x04001000;
        reg |= 0x200;
        *(volatile unsigned int *) 0x04001000 = reg;
        if (func_0206fea4() == 0) {
            func_02001b0c(2);
        }
    }

    if (data_021fba88[0x11]) {
        *(volatile unsigned short *) 0x04001050 = 0x2040;
    } else {
        *(volatile unsigned short *) 0x04001050 = 0x2042;
    }

    {
        unsigned int sum = (unsigned short) (r4 + data_021f8ab0.w3e);
        if (sum > 0x100) {
            sum = 0x100;
        }
        *(volatile unsigned short *) 0x04001016 = sum;
    }

    *(volatile unsigned short *) 0x04001014 = data_021f8ab0.w3c;
}

void func_020babb4(void)
{
    int r4;
    int r5;
    UnkStruct_020babb4 tmp;
    E_t *e;

    r4 = data_021f8ac4[data_021f8ab0.idx];

    tmp.a = (*(struct {
                char pad[4];
                unsigned short f4;
            } *) data_021f7270)
                .f4;
    *(volatile unsigned short *) 0x05000400 = tmp.a;
    tmp.b = (*(struct {
                char pad[4];
                unsigned short f4;
            } *) data_021f7270)
                .f4;
    *(volatile unsigned short *) 0x05000000 = tmp.b;

    e = &data_021f75b8[data_021f75b0.idx];
    *(volatile unsigned short *) 0x04000030 = e->unk_08;
    *(volatile unsigned int *) 0x04000038 = e->unk_00;
    *(volatile unsigned int *) 0x0400003c = e->unk_04;

    func_0209def4(&tmp);

    if (tmp.type >= 6 && tmp.type < 0x12) {
        volatile unsigned int *p = (volatile unsigned int *) 0x04000000;
        *p = *p & ~0x200;
        func_02001b34(2);
    } else {
        unsigned int reg = *(volatile unsigned int *) 0x04000000;
        reg |= 0x200;
        *(volatile unsigned int *) 0x04000000 = reg;
        func_02001b44(2);
    }

    if (r4 > 0xa8) {
        volatile unsigned int *p = (volatile unsigned int *) 0x04000000;
        *p = *p & ~0xa00;
        func_02001b34(0xa);
        *(volatile unsigned short *) 0x04000050 = 0x2040;
    } else {
        unsigned int reg = *(volatile unsigned int *) 0x04000000;
        reg |= 0x800;
        *(volatile unsigned int *) 0x04000000 = reg;
        func_02001b44(8);
        if (r4 > 0x97) {
            volatile unsigned int *p = (volatile unsigned int *) 0x04000000;
            *p = *p & ~0x200;
            func_02001b34(2);
            *(volatile unsigned short *) 0x04000050 = 0x2048;
        } else {
            if (data_021fba88[0x11]) {
                *(volatile unsigned short *) 0x04000050 = 0x2040;
            } else {
                *(volatile unsigned short *) 0x04000050 = 0x2042;
            }
        }
    }

    r5 = 0xc0 - r4;
    if (r5 < 0) {
        r5 = 0;
    } else if (r5 > 0xc0) {
        r5 = 0xc0;
    }

    {
        unsigned int sum = (unsigned short) (r4 + data_021f8ab0.w3e);
        if (sum > 0x100) {
            sum = 0x100;
        }
        *(volatile unsigned short *) 0x04000016 = sum;
    }

    *(volatile unsigned short *) 0x04000014 = data_021f8ab0.w3c;

    func_02001bb4(1);
    func_02001da0(0x15);
    func_02001d1c(0x1f);
    func_02001cc4(0, r5, 0xff, 0xc0);
}

void func_020bab74(void)
{
    UnkStruct_020bab74 *s1 = (UnkStruct_020bab74 *) data_021f7270;
    UnkStruct_020bab74 *s2 = (UnkStruct_020bab74 *) data_021f70f0;
    volatile u16 tmp;
    volatile u32 *reg = (volatile u32 *) 0x04000000;

    tmp = s1->unk_04;
    *(volatile u16 *) 0x05000400 = tmp;
    *(volatile u16 *) 0x05000000 = s2->unk_02;
    *reg = (*reg) & 0xfffff5ff;
}

void func_020bab04(void)
{
    func_020bb090();
    if (func_0206fea4() == 0) {
        func_020bae60();
        func_020bb3a4(((int **) &data_021f75b0));
    }
    func_020bbb20((*(int **) &data_021f75b0));
    if (data_021c67a4 != 0) {
        int a = (func_0206fd34() * 0x123) >> 12;
        int b = (func_0203adb0() * 0x1e) >> 12;
        int sum = a + b;
        data_021f8ac4[(*(UnkStruct_020bab04 *) &data_021f8ab0).unk_1C ^ 1] = sum;
    }
    (*(UnkStruct_020bab04 *) &data_021f8ab0).unk_3E = func_020bb1b0(((int **) &data_021f75b0));
}

void func_020baad8(void)
{
    unsigned int local1, local2;
    if (func_0206fea4() == 0) {
        func_020bb240(((int *) &data_021f75b0));
    }
    func_020bbb6c(((int *) &data_021f75b0), &local1, &local2);
    func_020bba14();
}
