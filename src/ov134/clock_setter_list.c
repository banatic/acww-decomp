/* clock_setter_list: 37 functions, module ov134
 * mwccarm 1.2/base -O4,s
 * func_ov134_0229a804 @ 0x0229a804, 0x64 bytes, Thumb
 * func_ov134_0229a5c8 @ 0x0229a5c8, 0x23c bytes, Thumb
 * func_ov134_0229a4e4 @ 0x0229a4e4, 0xe2 bytes, Thumb
 * func_ov134_0229a44c @ 0x0229a44c, 0x98 bytes, Thumb
 * func_ov134_0229a3e4 @ 0x0229a3e4, 0x68 bytes, Thumb
 * func_ov134_0229a398 @ 0x0229a398, 0x4a bytes, Thumb
 * func_ov134_0229a24c @ 0x0229a24c, 0x14c bytes, Thumb
 * func_ov134_0229a1f0 @ 0x0229a1f0, 0x5a bytes, Thumb
 * func_ov134_0229a1d8 @ 0x0229a1d8, 0x16 bytes, Thumb
 * func_ov134_0229a1b4 @ 0x0229a1b4, 0x24 bytes, Thumb
 * func_ov134_02299fd0 @ 0x02299fd0, 0x1e4 bytes, Thumb
 * func_ov134_02299f74 @ 0x02299f74, 0x5c bytes, Thumb
 * func_ov134_02299ecc @ 0x02299ecc, 0xa8 bytes, Thumb
 * func_ov134_02299d10 @ 0x02299d10, 0x1bc bytes, Thumb
 * func_ov134_02299cb8 @ 0x02299cb8, 0x56 bytes, Thumb
 * func_ov134_02299c60 @ 0x02299c60, 0x56 bytes, Thumb
 * func_ov134_02299bcc @ 0x02299bcc, 0x94 bytes, Thumb
 * func_ov134_02299b98 @ 0x02299b98, 0x32 bytes, Thumb
 * func_ov134_02299b70 @ 0x02299b70, 0x28 bytes, Thumb
 * func_ov134_02299b3c @ 0x02299b3c, 0x32 bytes, Thumb
 * func_ov134_02299b18 @ 0x02299b18, 0x24 bytes, Thumb
 * func_ov134_02299af0 @ 0x02299af0, 0x28 bytes, Thumb
 * func_ov134_02299a90 @ 0x02299a90, 0x60 bytes, Thumb
 * func_ov134_02299a84 @ 0x02299a84, 0xc bytes, Thumb
 * func_ov134_02299a60 @ 0x02299a60, 0x22 bytes, Thumb
 * func_ov134_02299a3c @ 0x02299a3c, 0x22 bytes, Thumb
 * func_ov134_02299a14 @ 0x02299a14, 0x26 bytes, Thumb
 * func_ov134_02299a00 @ 0x02299a00, 0x14 bytes, Thumb
 * func_ov134_022999e0 @ 0x022999e0, 0x1e bytes, Thumb
 * func_ov134_022999ac @ 0x022999ac, 0x32 bytes, Thumb
 * func_ov134_02299980 @ 0x02299980, 0x2c bytes, Thumb
 * func_ov134_022997dc @ 0x022997dc, 0x1a4 bytes, Thumb
 * func_ov134_022997b0 @ 0x022997b0, 0x2a bytes, Thumb
 * func_ov134_02299774 @ 0x02299774, 0x3a bytes, Thumb
 * func_ov134_02299734 @ 0x02299734, 0x3e bytes, Thumb
 * func_ov134_02299710 @ 0x02299710, 0x22 bytes, Thumb
 * func_ov134_022996b4 @ 0x022996b4, 0x5c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a804 {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[0x10];
    unsigned char unk_B1;
};

typedef struct {
    char pad_00[4];
    int unk_04;
    u8 unk_08[0x10];
    char pad_18[0x74 - 0x18];
    void *unk_74;
    void *unk_78;
    int unk_7C;
    char pad_80[0x8c - 0x80];
    int unk_8C;
    char pad_90[0xa4 - 0x90];
    u8 a4;
    u8 a5;
    char pad_A6[1];
    u8 a7;
    u8 a8;
    u8 a9;
    u8 aa;
    u8 ab;
    u8 ac;
    char pad_AD[1];
    u8 ae;
    u8 af;
    u8 b0;
    char pad_B1[0xb5 - 0xb1];
    u8 b5;
    u8 b6;
    char pad_B7[0xbc - 0xb7];
    u8 bc;
    u8 bd;
    char pad_BE[0x1070 - 0xbe];
    char unk_1070[0x1870 - 0x1070];
    u16 unk_1870[0x20 * 0x20];
} UnkStruct_0229a5c8;

typedef struct UnkStruct_0229a4e4 UnkStruct_0229a4e4;

struct UnkStruct_0229a4e4 {
    u8 pad_00[0x60];
    u32 unk_60;
    u8 pad_64[0xa4 - 0x64];
    u8 unk_A4;
    u8 unk_A5;
    u8 pad_A6[0xa9 - 0xa6];
    u8 unk_A9;
    u8 pad_AA[0xaf - 0xaa];
    u8 unk_AF;
};

struct UnkStruct_0229a44c {
    int unk_00;
    char pad_04[161];
    unsigned char unk_A5;
    char pad_A6[5];
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char unk_AD;
};

typedef struct {
    int unk_00;
    char pad_04[0x7c];
    int unk_80;
    char pad_84[0x20];
    unsigned char unk_A4;
    char pad_A5[4];
    unsigned char unk_A9;
    char pad_AA[1];
    unsigned char unk_AB;
    char pad_AC[1];
    unsigned char unk_AD;
    char pad_AE[1];
    unsigned char unk_AF;
} UnkStruct_0229a3e4;

typedef struct {
    unsigned char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char pad_A5[4];
    unsigned char unk_A9;
    unsigned char pad_AA[5];
    unsigned char unk_AF;
} UnkStruct_0229a398;

typedef struct UnkStruct_0229a24c {
    char pad_00[0x70];
    void *unk_70;
    int unk_74;
    int unk_78;
    char pad_7C[0x28];
    u8 unk_A4;
    u8 unk_A5;
    char pad_A6[3];
    u8 unk_A9;
    char pad_AA[5];
    volatile u8 unk_AF;
} UnkStruct_0229a24c;

typedef struct {
    char pad_00[0x60];
    int unk_60;
} UnkStruct_0229a1f0;

typedef struct {
    int unk_00;
} UnkStruct_0229a1d8;

struct UnkStruct_0229a1b4 {
    int unk_00;
    unsigned char pad_04[0xa0];
    unsigned char unk_A4;
    unsigned char pad_A5[5];
    unsigned char unk_AA;
    unsigned char unk_AB;
};

typedef struct {
    int unk_00;
    char pad_04[4];
    u8 unk_08[0x10];
    char pad_18[0xa4 - 0x18];
    u8 unk_A4;
    u8 unk_A5;
    char pad_A6[0xab - 0xa6];
    u8 unk_AB;
    u8 unk_AC;
    char pad_AD[0x1870 - 0xad];
    u16 unk_1870[0x400];
    u16 unk_2070[0x400];
} UnkStruct_02299fd0;

struct UnkStruct_02299ecc {
    u8 pad_00[0x80];
    s32 unk_80;
    u8 pad_84[0x2a];
    u8 unk_AE;
    u8 unk_AF;
    u8 pad_B0[5];
    u8 unk_B5;
    u8 unk_B6;
};

typedef struct UnkStruct_02299d10 {
    u8 pad_00[0x88];
    u32 unk_88;
    u8 pad_8C[0xa0 - 0x8c];
    u8 unk_A0;
    u8 pad_A1[0xa5 - 0xa1];
    u8 unk_A5;
    u8 pad_A6[0xad - 0xa6];
    u8 unk_AD;
    u8 pad_AE[0xb2 - 0xae];
    u8 unk_B2;
    u8 pad_B3[0xb8 - 0xb3];
    u8 unk_B8;
    u8 pad_B9[0xbb - 0xb9];
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
    u8 pad_BE[0xc8 - 0xbe];
    u8 unk_C8;
    u8 pad_C9[0xd0 - 0xc9];
    u8 unk_D0;
} UnkStruct_02299d10;

typedef struct {
    char pad_00[0xd0];
    int unk_D0;
} UnkStruct_02299cb8;

struct UnkStruct_02299b3c {
    char data[0x4c];
};

struct UnkStruct_02299b3c_2 {
    char pad_00[0x18];
    struct UnkStruct_02299b3c sub;
    int unk_64;
    int unk_68;
    int unk_6C;
};

struct UnkStruct_02299a90 {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x5c];
    int unk_64;
    char pad_68[0x24];
    int unk_8C;
} UnkStruct_02299a14;

struct UnkStruct_02299a00 {
    char pad_00[0x60];
    int unk_60;
    int unk_64;
};

struct UnkStruct_022999ac {
    int unk_00;
    int unk_04;
    unsigned char pad_08[0x10];
    unsigned char sub;
    unsigned char pad_19[0x92];
    unsigned char unk_AB;
    unsigned char pad_AC[4];
    unsigned char unk_B0;
};

typedef struct _S UnkStruct_022997dc;

struct _S {
    int unk_00;        // 0x00
    int unk_04;        // 0x04
    char pad_08[0x10]; // 0x08..0x17
    int unk_18;        // 0x18
    char pad_1C[0x94]; // 0x1c..0xaf
    unsigned char b0;  // 0xb0
    char pad_B1[0x06]; // 0xb1..0xb6
    signed char b7;    // 0xb7
};

typedef struct UnkStruct_022997b0 {
    unsigned char pad_00[0xAD];
    unsigned char unk_AD;
    unsigned char pad_AE[2];
    unsigned char unk_B0;
} UnkStruct_022997b0;

struct UnkStruct_02299774 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[0xb0 - 8];
    unsigned char unk_B0;
};

typedef struct UnkStruct_02299734 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[0xac - 0x8];
    unsigned char unk_AC;
    unsigned char pad_AD[0xb0 - 0xad];
    unsigned char unk_B0;
} UnkStruct_02299734;

struct UnkStruct_02299710 {
    int unk_00;
    char pad_04[0xa7];
    unsigned char unk_AB;
    unsigned char unk_AC;
};

struct St {
    int unk_00;
    int unk_04;
};

extern void func_ov134_0229a868(struct UnkStruct_0229a804 *obj, unsigned char val);
extern void func_0200467c(int);
extern void func_0200277c(int);
extern u8 func_ov134_0229aaa8(UnkStruct_0229a5c8 *, int);
extern u8 func_ov134_0229aa78(UnkStruct_0229a5c8 *, int);
extern void MIi_CpuCopy16(void *, void *, int);
extern int func_ov134_0229aa6c(UnkStruct_0229a5c8 *, int);
extern u8 func_0209de24(int, int);
extern u8 func_ov134_0229b884(UnkStruct_0229a5c8 *, int);
extern void func_ov134_0229a918(UnkStruct_0229a5c8 *, int, int);
extern int func_ov134_0229aa3c(UnkStruct_0229a5c8 *, int);
extern void func_ov134_0229b5f4(UnkStruct_0229a5c8 *, int, int, int, int, int);
extern void func_ov134_022995b0(UnkStruct_0229a5c8 *, int);
extern void func_02001b6c(int);
extern void func_02001d74(int, int);
extern int func_02002d8c(int);
extern void func_02001d00(int);
extern void func_ov134_022995d4(UnkStruct_0229a5c8 *, int);
extern u8 data_ov134_0229bf64[];
extern u8 data_ov134_0229bf5c[];
extern char data_ov134_0229c294;
extern char data_ov134_0229c164;
extern char data_ov134_0229c2c4;
extern char data_ov134_0229c11c;
extern void func_02002708(int);
extern void func_02001b7c(int);
extern int func_ov134_0229aa4c(UnkStruct_0229a4e4 *, int);
extern void func_ov134_0229b6dc(void *);
extern void func_ov134_022995a0(void *, int);
extern u8 data_ov134_0229c03c[];
extern u8 data_ov134_0229c04c[];
extern void func_02004658(int);
extern int func_ov134_0229ac38(void *unused0);
extern void func_ov134_0229af60(UnkStruct_0229a24c *);
extern void func_ov002_0220a574(void *p);
extern void func_0200284c(int, int, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov134_0229b5ac(UnkStruct_02299fd0 *, u8, int, int, int, int, int);
extern void func_02002808(int, int, int, int, int);
extern void func_ov134_0229b808(void *s, int a, int b);
extern void func_ov134_0229a96c(void *s, int a, int b);
extern void func_0209e140(void *addr, int val);
extern void func_0209e29c(void *addr, int val);
extern int func_ov134_022995c0(void *s, int param);
extern int func_0209e3ac(void *a, void *b, int len);
extern void MI_CpuCopy8(void *a, void *b, int len);
extern void func_ov134_0229b890(void *s, int val);
extern int func_ov134_0229b848(UnkStruct_02299cb8 *a, int i, int *ptr);
extern int func_ov002_0220a58c(void *, int unused1, int unused2);
extern void func_ov002_0220a4bc(void *receiver);
extern void func_ov002_0220a4c8(void *receiver);
extern int func_020e895c(void *, int, int);
extern unsigned short data_021fbe40;
extern int func_ov002_0220a568(void *);
extern int func_0208e930(void *);
extern void func_ov002_0220a580(void *);
extern int _s32_div_f(int, int);
extern void func_0208ea70(void *, int, int);
extern int func_ov002_0220a4f8(void *);
extern int func_ov002_0220a4d4(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);

void func_ov134_0229a1d8(UnkStruct_0229a1d8 *self, int val);
void func_ov134_0229a1b4(struct UnkStruct_0229a1b4 *p);
void func_ov134_02299fd0(UnkStruct_02299fd0 *self);
void func_ov134_02299f74(unsigned char *obj);
void func_ov134_02299ecc(struct UnkStruct_02299ecc *self);
int func_ov134_02299d10(UnkStruct_02299d10 *s);
int func_ov134_02299bcc(u8 *self, int n);
int func_ov134_02299b98(void *r0, int r1, int r2);
void func_ov134_02299a3c(void *self);
int func_ov134_02299a14(UnkStruct_02299a14 *self);
void func_ov134_02299a00(struct UnkStruct_02299a00 *arg);
int func_ov134_02299774(struct UnkStruct_02299774 *obj);
int func_ov134_02299734(UnkStruct_02299734 *self);
int func_ov134_02299710(struct UnkStruct_02299710 *obj, int arg);

void func_ov134_0229a804(struct UnkStruct_0229a804 *obj)
{
    switch (obj->unk_A0) {
        case 0:
        case 1:
            if (obj->unk_B1 < 4u) {
                func_ov134_0229a868(obj, (unsigned char) (obj->unk_B1 + 1));
            } else {
                func_ov134_0229a868(obj, 6);
            }
            break;
        case 2:
        case 3:
            if (obj->unk_B1 < 2u) {
                func_ov134_0229a868(obj, (unsigned char) (obj->unk_B1 + 1));
            } else {
                func_ov134_0229a868(obj, 6);
            }
            break;
        default:
            break;
    }
}

void func_ov134_0229a5c8(UnkStruct_0229a5c8 *p, int mode)
{
    int n;
    int w;
    int i;
    int j;
    int k;
    u8 v;
    int t;
    u16 *row;

    func_0200467c(0x13);
    p->a5 = (u8) mode;
    p->a9 = 0;
    func_0200277c(p->a4);
    p->a7 = func_ov134_0229aaa8(p, mode);
    p->a8 = func_ov134_0229aa78(p, mode);
    MIi_CpuCopy16(p->unk_1070, p->unk_1870, 0x800);
    n = func_ov134_0229aa6c(p, mode);
    w = 8 - n;
    row = p->unk_1870;
    for (i = 0; i < 0x20; i++) {
        for (j = 0; j < w; j++) {
            row[j] = 0x10;
        }
        row[(w - 1) & 0x1f] = 0x3079;
        row = row + 0x20;
    }
    p->aa = (u8) ((p->a7 - w) << 3);
    p->ab = 0x28;
    p->ac = data_ov134_0229bf64[mode];
    if (mode == 2) {
        p->ac = func_0209de24(p->bd, p->bc);
    }
    p->unk_8C = (p->ac - 8) << 4;
    for (k = 0; k < 0x10; k++) {
        p->unk_08[k] = 0xff;
    }
    v = func_ov134_0229b884(p, p->a5);
    if (p->a5 == 1 || p->a5 == 2) {
        v = (u8) (v - 1);
    }
    t = (v << 4) - ((p->a8 << 3) - p->ab);
    if (t < 0) {
        t = 0;
    } else if (t > p->unk_8C) {
        t = p->unk_8C;
    }
    func_ov134_0229a1d8((UnkStruct_0229a1d8 *) p, t);
    func_ov134_02299a3c((void *) p);
    func_ov134_0229a918(p, mode, 0xa);
    func_ov134_0229a868((struct UnkStruct_0229a804 *) p, (unsigned char) ((u8) mode));
    p->unk_7C = func_ov134_0229aaa8(p, p->a5) << 3;
    p->ae = (u8) (func_ov134_0229aa3c(p, mode) << 3);
    p->b5 = (u8) (p->ae - 8);
    p->b6 = (u8) (p->ae + 8);
    func_ov134_0229b5f4(p, 8, 0x1aa, 8, data_ov134_0229bf5c[mode], n + 1);
    func_ov134_022995b0(p, 0x200);
    if (mode == 0) {
        p->unk_74 = &data_ov134_0229c294;
        p->unk_78 = &data_ov134_0229c164;
    } else {
        p->unk_74 = &data_ov134_0229c2c4;
        p->unk_78 = &data_ov134_0229c11c;
    }
    p->af = 3;
    func_02001b6c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~func_02002d8c(p->a4) & 0x1f);
    func_ov134_022995d4(p, 0);
    p->b0 = (u8) (v + 1);
    p->unk_04 = 0;
}

int func_ov134_0229a4e4(UnkStruct_0229a4e4 *self)
{
    switch (self->unk_A9) {
        case 0:
            self->unk_A9 = 1;
            func_02002708(self->unk_A4);
            func_02001b7c(1);
            self->unk_AF--;
            func_ov134_02299f74((unsigned char *) self);
            break;
        case 1:
            if (self->unk_AF != 0) {
                self->unk_AF--;
                func_ov134_02299f74((unsigned char *) self);
            } else {
                func_02001b6c(1);
                self->unk_A9 = 2;
                self->unk_AF = 0;
                func_ov134_022995b0((UnkStruct_0229a5c8 *) self, 4);
                self->unk_60 = (u32) (func_ov134_0229aa4c(self, self->unk_A5) << 3);
                func_ov134_02299a00((struct UnkStruct_02299a00 *) self);
            }
            break;
        case 2:
            if (self->unk_AF < 3) {
                self->unk_AF++;
                func_ov134_022995d4((UnkStruct_0229a5c8 *) self, self->unk_AF);
            } else {
                self->unk_A9 = 8;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            return 1;
    }
    return 0;
}

int func_ov134_0229a44c(struct UnkStruct_0229a44c *p, int n, int m)
{
    int shifted;
    int low;
    int diff;
    int pos;

    if (m <= 0x28 || m >= 0xa8) {
        return 0;
    }

    shifted = n >> 3;

    if ((int) func_ov134_0229aaa8((UnkStruct_0229a5c8 *) p, p->unk_A5) > shifted || func_ov134_0229aa4c((UnkStruct_0229a4e4 *) p, p->unk_A5) < shifted) {
        return 0;
    }

    low = p->unk_00 & 0xf;

    if (m >= 0xb2 - low) {
        return 2;
    }

    if (m <= ((0x10 - low) & 0xf) + 0x1e) {
        return 2;
    }

    diff = m - (p->unk_AB - p->unk_00);

    if (diff < 0) {
        return 2;
    }

    pos = diff >> 4;

    if (pos >= p->unk_AC) {
        return 2;
    }

    if (func_ov134_02299bcc((u8 *) p, pos) != 0) {
        return 2;
    }

    p->unk_AD = pos;
    return 1;
}

void func_ov134_0229a3e4(UnkStruct_0229a3e4 *p)
{
    func_0200467c(0x29);
    p->unk_A9 = 3;
    p->unk_AF = 3;
    func_02001b6c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~func_02002d8c(p->unk_A4) & 0x1f);
    func_ov134_0229b6dc(p);
    p->unk_80 = p->unk_AB + (p->unk_AD << 4) - p->unk_00;
    func_ov134_022995a0(p, 4);
}

void func_ov134_0229a398(UnkStruct_0229a398 *p)
{
    func_0200467c(0x2a);
    p->unk_A9 = 4;
    p->unk_AF = 3;
    func_02001b6c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~func_02002d8c(p->unk_A4) & 0x1f);
    func_ov134_022995a0((void *) p, 4);
}

// The countdown field faf is volatile; it is read three times.

int func_ov134_0229a24c(UnkStruct_0229a24c *o)
{
    switch (o->unk_A9) {
        case 3:
            o->unk_A9 = 5;
            if (o->unk_A5 == 0) {
                o->unk_70 = data_ov134_0229c04c;
            } else {
                o->unk_70 = data_ov134_0229c03c;
            }
            break;
        case 4:
            o->unk_A9 = 5;
            break;
        case 5:
            if (o->unk_AF != 0) {
                o->unk_AF = o->unk_AF - 1;
                func_ov134_022995d4((UnkStruct_0229a5c8 *) o, (int) o->unk_AF);
            } else {
                func_0200467c(0x14);
                o->unk_A9 = 6;
                o->unk_AF = 3;
                func_02001b7c(1);
                o->unk_AF = o->unk_AF - 1;
                func_ov134_02299ecc((struct UnkStruct_02299ecc *) o);
            }
            break;
        case 6:
            if (o->unk_AF != 0) {
                o->unk_AF = o->unk_AF - 1;
                func_ov134_02299ecc((struct UnkStruct_02299ecc *) o);
            } else {
                func_0200277c((int) o->unk_A4);
                func_02001b6c(1);
                func_ov134_0229a918((UnkStruct_0229a5c8 *) o, (int) o->unk_A5, 3);
                o->unk_74 = 0;
                o->unk_78 = 0;
                if (o->unk_70 != 0) {
                    if (func_ov134_02299d10((UnkStruct_02299d10 *) o)) {
                        o->unk_A9 = 7;
                        func_02004658(0x54);
                    } else {
                        o->unk_A9 = 8;
                    }
                    o->unk_70 = 0;
                    func_ov134_0229a804((struct UnkStruct_0229a804 *) o);
                } else {
                    o->unk_A9 = 8;
                }
            }
            break;
        case 7:
            if (func_ov134_0229ac38(o)) {
                func_ov134_0229af60(o);
                o->unk_A9 = 8;
            }
            break;
        case 8:
            return 1;
        case 0:
        case 1:
        case 2:
        default:
            break;
    }
    return 0;
}

int func_ov134_0229a1f0(UnkStruct_0229a1f0 *self, int x, int y)
{
    int ret;
    int v;

    ret = func_ov134_0229a44c((struct UnkStruct_0229a44c *) self, x, y);
    switch (ret) {
        case 1:
            return 0;
        case 2:
            return 4;
        default:
            break;
    }

    if (func_ov134_02299b98(self, x, y) != 0) {
        return 3;
    }

    if (y >= 32 && y <= 168) {
        v = self->unk_60;
        if (x > v + 24) {
            goto fail;
        }
        if (x < v) {
            goto fail;
        }
        func_ov002_0220a574((char *) self + 0x18);
        return 2;
    }

fail:
    return 1;
}

void func_ov134_0229a1d8(UnkStruct_0229a1d8 *self, int val)
{
    self->unk_00 = val;
    func_ov134_0229a1b4((struct UnkStruct_0229a1b4 *) self);
    func_ov134_02299fd0((UnkStruct_02299fd0 *) self);
}

void func_ov134_0229a1b4(struct UnkStruct_0229a1b4 *p)
{
    func_0200284c(p->unk_A4, -p->unk_AA, -(p->unk_AB - p->unk_00));
}

void func_ov134_02299fd0(UnkStruct_02299fd0 *self)
{
    int jt;
    int t;

    int i;
    int start;
    u16 *p;

    int n;
    int e;
    int j;
    u8 v;
    int c;
    int d;
    int col;
    int u;
    MIi_CpuCopy16(self->unk_1870, self->unk_2070, 0x800);
    d = self->unk_AB - self->unk_00;
    func_ov134_0229aa6c((UnkStruct_0229a5c8 *) self, (int) self->unk_A5);
    start = 8 - func_ov134_0229aa6c((UnkStruct_0229a5c8 *) self, (int) self->unk_A5);
    if (d > 0) {
        d += 0xf;
        col = (0x10 - (d >> 4)) * 2;
        p = (u16 *) (((char *) self->unk_2070) + (col << 6));
        for (; col < 0x20; col++) {
            for (j = start; j < 8; j++) {
                p[j] = 0x3074;
            }

            p += 0x20;
        }
    }
    n = (self->unk_00 - self->unk_AB) >> 4;
    for (i = 0; i < 0x10; i++) {
        t = i + n;
        c = t & 0xf;
        if ((t >= 0) && (t < self->unk_AC)) {
            if (func_ov134_02299bcc((u8 *) self, t) != 0) {
                func_0206fdd4(self->unk_2070, start, c * 2, 7, (c * 2) + 1, 6);
            }
            if (t != self->unk_08[c]) {
                self->unk_08[c] = (u8) t;
                v = self->unk_A5;
                if (v == 0) {
                    t += 0x7d0;
                }
                v = (u8) (v + 0xff);
                if (v <= 1) {
                    t++;
                }
                func_ov134_0229b5ac(self, self->unk_A4, (c << 4) + 0x80, 8, t, 0xf, 0xe);
            }
        }
    }

    u = self->unk_AC;
    e = self->unk_AB - self->unk_00;
    e = e + (u << 4);
    if (e < 0xc0) {
        d = ((0xcf - e) >> 4) * 2;
        jt = (u * 2) & 0x1f;
        for (i = 0; i < d; i++) {
            p = (u16 *) (((char *) self->unk_2070) + (jt << 6));
            for (j = start; j < 8; j++) {
                p[j] = 0x3074;
            }

            jt = (jt + 1) & 0x1f;
        }
    }
    col = (((self->unk_00 - self->unk_AB) + 0x20) & 0xff) >> 3;
    for (c = 0; c < 5; c++) {
        p = (u16 *) (((char *) self->unk_2070) + (col << 6));
        for (jt = 0; jt < 10; jt++) {
            p[jt] = 0x10;
        }

        p[0x1f] = 0x10;
        col = (col - 1) & 0x1f;
    }

    col = (((self->unk_00 - self->unk_AB) + 0xb0) & 0xff) >> 3;
    for (c = 0; c < 3; c++) {
        p = (u16 *) (((char *) self->unk_2070) + (col << 6));
        for (jt = 0; jt < 10; jt++) {
            p[jt] = 0x10;
        }

        p[0x1f] = 0x10;
        col = (col + 1) & 0x1f;
    }

    func_ov134_022995b0((UnkStruct_0229a5c8 *) self, 1);
}

void func_ov134_02299f74(unsigned char *obj)
{
    if (obj[0xaf]) {
        obj[0xb5] = (unsigned char) ((obj[0xb5] + 0x28) >> 1);
        obj[0xb6] = (unsigned char) ((obj[0xb6] + 0xa8) >> 1);
    } else {
        obj[0xb5] = 0x28;
        obj[0xb6] = 0xa8;
    }
    func_02002808(2, 0, obj[0xb5], 0xff, obj[0xb6]);
}

void func_ov134_02299ecc(struct UnkStruct_02299ecc *self)
{
    if (self->unk_AF) {
        self->unk_B5 = (self->unk_AE - 8 + self->unk_B5) >> 1;
        self->unk_B6 = (self->unk_AE + 8 + self->unk_B6) >> 1;
    } else {
        self->unk_B5 = self->unk_AE - 8;
        self->unk_B6 = self->unk_AE + 8;
    }
    func_02002808(2, 0, self->unk_B5, 0xff, self->unk_B6);
    if (self->unk_80 < self->unk_B5) {
        self->unk_80 = self->unk_B5;
    }
    if (self->unk_80 > self->unk_B6 - 8) {
        self->unk_80 = self->unk_B6 - 8;
    }
}

int func_ov134_02299d10(UnkStruct_02299d10 *s)
{
    u16 flag = 0;
    unsigned int t0;

    t0 = (unsigned int) func_ov134_0229b884((UnkStruct_0229a5c8 *) s, s->unk_A5);
    func_ov134_0229b808(s, s->unk_A5, s->unk_AD);

    flag |= (1 << s->unk_A5);

    {
        int tmp = (int) func_0209de24((int) s->unk_BD, (int) s->unk_BC);
        if (tmp < (int) s->unk_BB) {
            s->unk_BB = (u8) tmp;
            flag |= 4;
        }
    }

    if (s->unk_A5 <= 2) {
        func_ov134_0229a96c(s, 5, 3);
        flag |= 0x20;
    }

    {
        int n6 = 0;

        if (s->unk_A5 == 3 && s->unk_A0 == 1) {
            u8 b2 = s->unk_B2;
            if (t0 < b2) {
                if (s->unk_AD >= b2) {
                    func_0209e140(&s->unk_B8, 1);
                    n6 = -1;
                }
            } else {
                if (s->unk_AD < b2) {
                    func_0209e29c(&s->unk_B8, 1);
                    n6 = 1;
                }
            }
            if (n6 != 0) {
                flag |= 0x27;
            }
        }

        if (func_ov134_022995c0(s, 0x80) != 0) {
            if (func_0209e3ac(&s->unk_C8, &s->unk_B8, 0x3f) == 1) {
                MI_CpuCopy8(&s->unk_C8, &s->unk_B8, 8);
                flag = 0xffff;
            }
        }

        if (func_ov134_022995c0(s, 0x40) != 0) {
            if (func_0209e3ac(&s->unk_D0, &s->unk_B8, 0x3f) == -1) {
                MI_CpuCopy8(&s->unk_D0, &s->unk_B8, 8);
                flag = 0xffff;
            }
        }

        {
            u8 i;
            for (i = 0; i <= 5; i++) {
                if ((flag & (1 << i)) != 0) {
                    func_ov134_0229b890(s, i);
                }
            }
        }

        if ((u8) (s->unk_A5 + 0xfd) <= 1) {
            if (t0 == s->unk_AD) {
                return 0;
            } else {
                int v = (unsigned int) func_ov134_0229b884((UnkStruct_0229a5c8 *) s, 4);
                int w = (unsigned int) func_ov134_0229b884((UnkStruct_0229a5c8 *) s, 3);
                s->unk_88 = v + w * 0x3c;
                s->unk_88 += n6 * 0x5a0;
                return 1;
            }
        }
        return 0;
    }
}

int func_ov134_02299cb8(UnkStruct_02299cb8 *a, int threshold, unsigned int count)
{
    unsigned char i;
    int val;
    for (i = 0; i < count; i++) {
        val = (int) func_ov134_0229b884((UnkStruct_0229a5c8 *) a, i);
        if (val != func_ov134_0229b848(a, i, &a->unk_D0)) {
            return 0;
        }
    }
    if (threshold <= func_ov134_0229b848(a, count, &a->unk_D0)) {
        return 0;
    }
    return 1;
}

int func_ov134_02299c60(const char *param0, int param1, unsigned int param2)
{
    unsigned char i;
    int t;
    for (i = 0; i < param2; i++) {
        t = (int) func_ov134_0229b884((UnkStruct_0229a5c8 *) param0, i);
        if (t != func_ov134_0229b848((UnkStruct_02299cb8 *) param0, i, (int *) (param0 + 0xc8))) {
            return 0;
        }
    }
    if (param1 < func_ov134_0229b848((UnkStruct_02299cb8 *) param0, param2, (int *) (param0 + 0xc8))) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov134_02299bcc(u8 *self, int n)
{
    int hi;
    int lo;

    switch (self[0xa5]) {
        case 1:
        case 2:
            n++;
            break;
    }
    if (self[0xa0] == 1 && self[0xa5] == 3) {
        hi = self[0xb3];
        lo = self[0xb2];
        if ((unsigned int) lo < (unsigned int) hi) {
            if (n < lo || n > hi) {
                return 1;
            }
        } else {
            if (n < lo && n > hi) {
                return 1;
            }
        }
        return 0;
    }
    if (func_ov134_022995c0((void *) self, 0x80) != 0) {
        if (func_ov134_02299c60((const char *) self, n, (unsigned int) self[0xa5]) != 0) {
            return 1;
        }
    }
    if (func_ov134_022995c0((void *) self, 0x40) != 0) {
        return func_ov134_02299cb8((UnkStruct_02299cb8 *) self, n, (unsigned int) self[0xa5]);
    }
    return 0;
}

int func_ov134_02299b98(void *r0, int r1, int r2)
{
    int r5 = (int) r0;
    int r4 = r2;
    int result;
    void *p = (void *) (r5 + 0x18);
    if (func_ov002_0220a58c(p, r1, r2) != 0) {
        *(int *) (r5 + 0x68) = *(int *) (r5 + 0x64) - r4;
        func_ov002_0220a574((void *) (r5 + 0x18));
        *(int *) (r5 + 0x6c) = *(int *) (r5 + 0x64);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov134_02299b70(void *self)
{
    if (*(unsigned char *) ((char *) self + 0xb0) == 0) {
        func_ov002_0220a574((char *) self + 0x18);
        self = (void *) ((char *) self + 0x18);
        func_ov002_0220a4bc(self);
        return 1;
    }
    return 0;
}

void func_ov134_02299b3c(struct UnkStruct_02299b3c_2 *obj)
{
    int diff;
    func_ov134_02299a14((UnkStruct_02299a14 *) obj);
    func_ov134_02299a00((struct UnkStruct_02299a00 *) obj);
    diff = obj->unk_6C - obj->unk_64;
    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8((char *) obj + 0x18);
        obj->unk_6C = obj->unk_64;
    }
}

void func_ov134_02299b18(int *r0, int r1)
{
    r1 += r0[0x1a];
    r0[0x19] = r1;
    if (r0[0x19] < 0x20) {
        r0[0x19] = 0x20;
    }
    if (r0[0x19] > 0xa0) {
        r0[0x19] = 0xa0;
    }
    func_ov134_02299b3c((struct UnkStruct_02299b3c_2 *) r0);
}

void func_ov134_02299af0(void *param0, int param1)
{
    int r1 = param1 - 8;
    if (r1 < 0x20) {
        r1 = 0x20;
    }
    if (r1 > 0xa0) {
        r1 = 0xa0;
    }
    func_020e895c((char *) param0 + 0x64, r1, 8);
    func_ov134_02299b3c((struct UnkStruct_02299b3c_2 *) param0);
}

void func_ov134_02299a90(struct UnkStruct_02299a90 *self)
{
    int old = self->unk_64;
    unsigned short flags = data_021fbe40;

    if ((flags & 0x40) != 0) {
        self->unk_64 = old - 4;
        if (self->unk_64 < 0x20) {
            self->unk_64 = 0x20;
        }
    } else if ((flags & 0x80) != 0) {
        self->unk_64 = old + 4;
        if (self->unk_64 > 0xa0) {
            self->unk_64 = 0xa0;
        }
    }
    if (old != self->unk_64) {
        func_ov134_02299a14((UnkStruct_02299a14 *) self);
        func_ov134_02299a00((struct UnkStruct_02299a00 *) self);
        self = (struct UnkStruct_02299a90 *) ((char *) self + 0x18);
        func_ov002_0220a4c8(self);
    }
}

int func_ov134_02299a84(void *p)
{
    return func_ov002_0220a568((void *) ((char *) p + 0x18));
}

int func_ov134_02299a60(void *param)
{
    if (func_0208e930((char *) param + 0x18)) {
        func_ov002_0220a580((char *) param + 0x18);
        return 1;
    }
    return 0;
}

void func_ov134_02299a3c(void *self)
{
    int r0;
    int r1;

    r0 = *(int *) self;
    r0 = r0 << 7;
    r1 = *(int *) ((char *) self + 0x8c);
    r0 = _s32_div_f(r0, r1);
    r0 += 0x20;
    *(int *) ((char *) self + 0x64) = r0;
    func_ov134_02299a00((struct UnkStruct_02299a00 *) self);
}

int func_ov134_02299a14(UnkStruct_02299a14 *self)
{
    func_ov134_0229a1d8((UnkStruct_0229a1d8 *) self, (self->unk_8C * (self->unk_64 - 0x20)) / 0x80);
    self->unk_04 = 0;
    return 0;
}

void func_ov134_02299a00(struct UnkStruct_02299a00 *arg)
{
    func_0208ea70((char *) arg + 0x18, arg->unk_60 - 0x78, arg->unk_64 - 0x60);
}

int func_ov134_022999e0(void *self)
{
    if (*(unsigned char *) ((char *) self + 0xb0) == 0) {
        return func_ov002_0220a4f8((char *) self + 0x18);
    }
    return *(int *) ((char *) self + 0x60);
}

int func_ov134_022999ac(struct UnkStruct_022999ac *p)
{
    if (p->unk_B0 == 0) {
        return func_ov002_0220a4d4(&p->sub);
    } else {
        return p->unk_AB + ((p->unk_B0 - 1) << 4) - p->unk_00 + 8 - p->unk_04;
    }
}

void func_ov134_02299980(unsigned char *p, int x)
{
    if (p[0xB0] == 0) {
        return;
    }
    if (x < 0x28) {
        x = 0x28;
    } else if (x > 0xa8) {
        x = 0xa8;
    }
    p[0xB0] = func_ov134_02299710((struct UnkStruct_02299710 *) p, x) + 1;
}

int func_ov134_022997dc(UnkStruct_022997dc *self, void *other)
{
    if (self->b0 != 0) {
        goto L_else;
    }

    // L_b0_zero
    self->b7 = 0;
    if (func_ov002_022088ac(other) != 0) {
        goto L_b0_ok;
    }
    goto L_ret0;

L_b0_ok:
    self->b0 = 1;
    func_ov134_02299980((unsigned char *) self, func_ov002_0220a4d4(&self->unk_18));
    return 1;

L_else:
    if (func_ov002_0220889c(other) == 0) {
        goto L_else_zero;
    }
    self->b0 = 0;
    self->b7 = 0;
    return 1;

L_else_zero:
    if (self->b7 >= 6) {
        goto L_ge6;
    }
    goto L_less6;

L_ge6:
    if (((*(volatile unsigned short *) &data_021fbe40) & 0x40) == 0) {
        goto L_ge6_flag0;
    }
    if (func_ov134_02299774((struct UnkStruct_02299774 *) self) == 0) {
        goto L_label9908;
    }
    // L_ge6_pass
    if (self->unk_04 != 0) {
        func_ov134_0229a1d8((UnkStruct_0229a1d8 *) self, self->unk_00 + self->unk_04);
        self->unk_04 = 0;
        func_ov134_02299a3c((void *) self);
    }
    if (func_ov134_022995c0((void *) self, 0x100)) {
        func_ov134_022995a0((void *) self, 0x100);
        func_0200467c(0xb);
    } else {
        func_ov134_022995b0((UnkStruct_0229a5c8 *) self, 0x100);
    }
    return 3;

L_ge6_flag0:
    self->b7 = 0;
    goto L_label9908;

L_less6:
    if (self->b7 > -6) {
        goto L_label9908;
    }
    // L_less6_continue
    if (((*(volatile unsigned short *) &data_021fbe40) & 0x80) == 0) {
        goto L_less6_flag0;
    }
    if (func_ov134_02299734((UnkStruct_02299734 *) self) == 0) {
        goto L_label9908;
    }
    // L_less6_pass
    if (self->unk_04 != 0) {
        func_ov134_0229a1d8((UnkStruct_0229a1d8 *) self, self->unk_00 + self->unk_04);
        self->unk_04 = 0;
        func_ov134_02299a3c((void *) self);
    }
    if (func_ov134_022995c0((void *) self, 0x100)) {
        func_ov134_022995a0((void *) self, 0x100);
        func_0200467c(0xb);
    } else {
        func_ov134_022995b0((UnkStruct_0229a5c8 *) self, 0x100);
    }
    return 3;

L_less6_flag0:
    self->b7 = 0;
    goto L_label9908;

L_label9908:
    if (func_ov002_022088cc(other) == 0) {
        goto L_fn4_zero;
    }
    // L_fn4_nonzero
    if (self->b7 < 0) {
        self->b7 = 1;
    } else {
        self->b7 = self->b7 + 1;
    }
    if (func_ov134_02299774((struct UnkStruct_02299774 *) self) != 0) {
        return 2;
    }
    goto L_ret0;

L_fn4_zero:
    if (func_ov002_022088bc(other) == 0) {
        goto L_ret0;
    }
    // L_fn5_nonzero
    if (self->b7 > 0) {
        self->b7 = -1;
    } else {
        self->b7 = self->b7 - 1;
    }
    if (func_ov134_02299734((UnkStruct_02299734 *) self) != 0) {
        return 2;
    }

L_ret0:
    return 0;
}

int func_ov134_022997b0(UnkStruct_022997b0 *self)
{
    int n;

    n = self->unk_B0 - 1;
    if (func_ov134_02299bcc((u8 *) self, n)) {
        return 0;
    }
    self->unk_AD = n;
    return 1;
}

int func_ov134_02299774(struct UnkStruct_02299774 *obj)
{
    if (obj->unk_B0 > 1) {
        int ret;
        obj->unk_B0--;
        ret = func_ov134_022999ac((struct UnkStruct_022999ac *) obj);
        if (ret < 0x30) {
            obj->unk_04 -= 0x30 - ret;
        }
        return 1;
    }
    return 0;
}

int func_ov134_02299734(UnkStruct_02299734 *self)
{
    if ((int) self->unk_B0 < (int) self->unk_AC) {
        int res;
        self->unk_B0++;
        res = func_ov134_022999ac((struct UnkStruct_022999ac *) self);
        if (res > 0xa0) {
            self->unk_04 += res - 0xa0;
        }
        return 1;
    }
    return 0;
}

int func_ov134_02299710(struct UnkStruct_02299710 *obj, int arg)
{
    arg -= obj->unk_AB - obj->unk_00;
    if (arg < 0) {
        arg = 0;
    }
    arg >>= 4;
    if (arg >= obj->unk_AC) {
        arg = obj->unk_AC - 1;
    }
    return arg;
}

void func_ov134_022996b4(struct St *p)
{
    int a;
    int b;

    if (func_ov134_022995c0((void *) p, (int) 1) != 0) {
        return;
    }
    a = p->unk_00;
    b = p->unk_04;
    if (b > 0) {
        if (b < 8) {
            a += b;
            p->unk_04 = 0;
        } else {
            a += 8;
            b -= 8;
            p->unk_04 = b;
        }
    } else if (b < 0) {
        if (b > -8) {
            a += b;
            p->unk_04 = 0;
        } else {
            a -= 8;
            b += 8;
            p->unk_04 = b;
        }
    }
    if (a != p->unk_00) {
        func_ov134_0229a1d8((UnkStruct_0229a1d8 *) p, a);
        func_ov134_02299a3c((void *) p);
    }
}
