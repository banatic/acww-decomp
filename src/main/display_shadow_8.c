/* display_shadow_8: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020024cc @ 0x020024cc, 0x24 bytes, Thumb
 * func_0200240c @ 0x0200240c, 0xc0 bytes, Thumb
 * func_02002408 @ 0x02002408, 0x2 bytes, Thumb
 * func_02002354 @ 0x02002354, 0xb4 bytes, Thumb
 * func_02001ecc @ 0x02001ecc, 0x488 bytes, Thumb
 */

#include "types.h"

#define REG_DISPCNT (*(volatile unsigned int *) 0x04000000)
#define REG_DISPCNT_SUB (*(volatile unsigned int *) 0x04001000)
#define REG_WINOUT (*(volatile unsigned short *) 0x0400004a)
#define REG_WINOUT_SUB (*(volatile unsigned short *) 0x0400104a)

struct BigObj {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned char unk_11;
    unsigned short unk_12;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
};

struct Small2 {
    unsigned char pad_00[0x12];
    unsigned char unk_12;
    unsigned char pad_13;
    unsigned char unk_14;
};

typedef struct {
    u16 unk_00, h1, h2, h3;
    u8 unk_08[0x10];
    u32 unk_18, unk_1C, unk_20, unk_24;
    u8 unk_28[0x10];
    u32 unk_38, unk_3C, unk_40, unk_44;
    u8 unk_48[0x18];
    u32 unk_60, unk_64, unk_68, unk_6C;
} UnkStruct_02001ecc;

typedef struct {
    u8 unk_00[8];
    u16 unk_08, unk_0A, unk_0C, unk_0E;
} UnkStruct_02001ecc_2;

typedef struct {
    u32 unk_00, unk_04, unk_08, unk_0C;
    u8 unk_10, unk_11;
    u16 unk_12;
    u8 unk_14[10];
    u8 unk_1E, unk_1F;
} UnkStruct_02001ecc_3;

typedef struct {
    u8 b[0x16];
} UnkStruct_02001ecc_4;

extern void GX_LoadBGPltt(const void *, int, int);
extern void GXS_LoadBGPltt(const void *, int, int);
extern unsigned short data_0213fdf0[];
extern void func_02001ec4(unsigned short *p0);
extern void func_02001ea8(unsigned int *arg0);
extern void func_02001e94(unsigned char *r0);
extern void func_02001c08(unsigned char param);
extern void func_02001c30(unsigned char param);
extern struct Small2 data_0213fe94;
extern unsigned short data_0213fdf4[2];
extern unsigned short data_0213fdf8[2];
extern unsigned int data_0213fdfc[8];
extern unsigned int data_0213fe1c[8];
extern unsigned short data_0213fe3c[2];
extern unsigned short data_0213fe40[2];
extern unsigned int data_0213fe44[8];
extern unsigned int data_0213fe64[8];
extern unsigned char data_0213fe92[5];
extern unsigned char data_0213fe97[5];
extern unsigned char data_0213fe9c[5];
extern unsigned char data_0213fea1[5];
extern void GX_SetGraphicsMode(int, int, int);
extern void GXS_SetGraphicsMode(int);
extern unsigned char data_0213fe74[];
extern UnkStruct_02001ecc_2 data_0213fe34;
extern void G2x_SetBGyAffine_(u32 reg, void *p, u32 a, u32 b, u32 c, u32 d);
extern void G3X_SetHOffset(u32 v);
extern void G2x_SetBlendBrightnessExt_(u32 reg, int a, int b, int c, int d, int e);
extern void G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern void G2x_SetBlendBrightness_(u32 reg, int a, int b);

void func_020024cc(void)
{
    GX_LoadBGPltt(data_0213fdf0, 0, 2);
    GXS_LoadBGPltt(data_0213fdf0, 0, 2);
}

void func_0200240c(void)
{
    (*(struct BigObj *) data_0213fe74).unk_14 = 0;
    (*(struct BigObj *) data_0213fe74).unk_15 = 0;
    (*(struct BigObj *) data_0213fe74).unk_18 = 0;
    (*(struct BigObj *) data_0213fe74).unk_19 = 0;
    (*(struct BigObj *) data_0213fe74).unk_1A = 0;
    (*(struct BigObj *) data_0213fe74).unk_1B = 0;
    (*(struct BigObj *) data_0213fe74).unk_1C = 0;
    (*(struct BigObj *) data_0213fe74).unk_1D = 0;
    (*(struct BigObj *) data_0213fe74).unk_16 = 0;
    (*(struct BigObj *) data_0213fe74).unk_17 = 1;

    func_02001ec4(data_0213fdf4);
    func_02001ec4(data_0213fdf8);
    func_02001ea8(data_0213fdfc);
    func_02001ea8(data_0213fe1c);
    func_02001ec4(data_0213fe3c);
    func_02001ec4(data_0213fe40);
    func_02001ea8(data_0213fe44);
    func_02001ea8(data_0213fe64);
    func_02001e94(data_0213fe92);
    func_02001e94(data_0213fe97);
    func_02001e94(data_0213fe9c);
    func_02001e94(data_0213fea1);

    (*(struct BigObj *) data_0213fe74).unk_10 = 0;
    (*(struct BigObj *) data_0213fe74).unk_11 = 0xff;
    (*(struct BigObj *) data_0213fe74).unk_12 = 0xff;

    data_0213fe94.unk_12 = 0;
    data_0213fe94.unk_14 = 0;

    func_02001c08(0);
    func_02001c30(1);
}

void func_02002408(void) {}

void func_02002354(void)
{
    unsigned int v;
    unsigned short w;

    GX_SetGraphicsMode(1, data_0213fe74[0x16], 1);
    GXS_SetGraphicsMode(data_0213fe74[0x17]);

    v = REG_DISPCNT;
    v = (v & ~0x1f00) | (data_0213fe74[0x14] << 8);
    REG_DISPCNT = v;

    v = REG_DISPCNT_SUB;
    v = (v & ~0x1f00) | (data_0213fe74[0x15] << 8);
    REG_DISPCNT_SUB = v;

    v = REG_DISPCNT;
    v = (v & ~0xe000) | (data_0213fe74[0x18] << 13);
    REG_DISPCNT = v;

    v = REG_DISPCNT_SUB;
    v = (v & ~0xe000) | (data_0213fe74[0x19] << 13);
    REG_DISPCNT_SUB = v;

    w = REG_WINOUT;
    w = (w & ~0x3f) | data_0213fe74[0x1a] | 0x20;
    REG_WINOUT = w;

    w = REG_WINOUT_SUB;
    w = (w & ~0x3f) | data_0213fe74[0x1b] | 0x20;
    REG_WINOUT_SUB = w;

    w = REG_WINOUT;
    w = (w & ~0x3f00) | (data_0213fe74[0x1c] << 8);
    REG_WINOUT = w;

    w = REG_WINOUT_SUB;
    w = (w & ~0x3f00) | (data_0213fe74[0x1d] << 8);
    REG_WINOUT_SUB = w;
}

static __inline void setpair(u32 ra, u32 rb, int a, int b, int c, int d)
{
    *(volatile u16 *) ra = (u16) (((a << 8) & 0xff00) | (b & 0xff));
    *(volatile u16 *) rb = (u16) (((c << 8) & 0xff00) | (d & 0xff));
}

void func_02001ecc(void)
{
    int m;

    if ((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 != 0) {
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 1) != 0) {
            if ((*(volatile u32 *) 0x04000000 & 8) == 0) {
                *(volatile u32 *) 0x04000010 = ((*(UnkStruct_02001ecc *) data_0213fdf4).unk_00 & 0x1ff) | (((u32) (*(UnkStruct_02001ecc *) data_0213fdf4).h1 << 16) & 0x01ff0000);
            } else {
                G3X_SetHOffset((*(UnkStruct_02001ecc *) data_0213fdf4).unk_00);
            }
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 2) != 0) {
            *(volatile u32 *) 0x04000014 = ((*(UnkStruct_02001ecc *) data_0213fdf4).h2 & 0x1ff) | (((u32) (*(UnkStruct_02001ecc *) data_0213fdf4).h3 << 16) & 0x01ff0000);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 4) != 0) {
            if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_10 & 1) != 0) {
                G2x_SetBGyAffine_(0x04000020, ((u32 *) data_0213fdfc), (*(UnkStruct_02001ecc *) data_0213fdf4).unk_18, (*(UnkStruct_02001ecc *) data_0213fdf4).unk_1C, (*(UnkStruct_02001ecc *) data_0213fdf4).unk_20,
                                  (*(UnkStruct_02001ecc *) data_0213fdf4).unk_24);
            } else {
                *(volatile u32 *) 0x04000018 = ((*(UnkStruct_02001ecc *) data_0213fdf4).unk_20 & 0x1ff) | (((*(UnkStruct_02001ecc *) data_0213fdf4).unk_24 << 16) & 0x01ff0000);
            }
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 8) != 0) {
            if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_10 & 2) != 0) {
                G2x_SetBGyAffine_(0x04000030, ((u32 *) data_0213fe1c), (*(UnkStruct_02001ecc *) data_0213fdf4).unk_38, (*(UnkStruct_02001ecc *) data_0213fdf4).unk_3C, (*(UnkStruct_02001ecc *) data_0213fdf4).unk_40,
                                  (*(UnkStruct_02001ecc *) data_0213fdf4).unk_44);
            } else {
                *(volatile u32 *) 0x0400001c = ((*(UnkStruct_02001ecc *) data_0213fdf4).unk_40 & 0x1ff) | (((*(UnkStruct_02001ecc *) data_0213fdf4).unk_44 << 16) & 0x01ff0000);
            }
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 0x10) != 0) {
            *(volatile u32 *) 0x04001010 = (data_0213fe34.unk_08 & 0x1ff) | (((u32) data_0213fe34.unk_0A << 16) & 0x01ff0000);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 0x20) != 0) {
            *(volatile u32 *) 0x04001014 = (data_0213fe34.unk_0C & 0x1ff) | (((u32) data_0213fe34.unk_0E << 16) & 0x01ff0000);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 0x40) != 0) {
            if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_10 & 4) != 0) {
                G2x_SetBGyAffine_(0x04001020, ((u32 *) data_0213fe44), (*(UnkStruct_02001ecc *) data_0213fdf4).unk_60, (*(UnkStruct_02001ecc *) data_0213fdf4).unk_64, (*(UnkStruct_02001ecc *) data_0213fdf4).unk_68,
                                  (*(UnkStruct_02001ecc *) data_0213fdf4).unk_6C);
            } else {
                *(volatile u32 *) 0x04001018 = ((*(UnkStruct_02001ecc *) data_0213fdf4).unk_68 & 0x1ff) | (((*(UnkStruct_02001ecc *) data_0213fdf4).unk_6C << 16) & 0x01ff0000);
            }
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 & 0x80) != 0) {
            if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_10 & 8) != 0) {
                G2x_SetBGyAffine_(0x04001030, ((u32 *) data_0213fe64), (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_00, (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_04, (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_08,
                                  (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_0C);
            } else {
                *(volatile u32 *) 0x0400101c = ((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_08 & 0x1ff) | (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_0C << 16) & 0x01ff0000);
            }
        }
        (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_11 = 0;
    }
    if ((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 != 0) {
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 1) != 0) {
            *(volatile u16 *) 0x04000048 = (u16) ((*(volatile u16 *) 0x04000048 & ~0x3f) | (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[2] | 0x20);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 2) != 0) {
            *(volatile u16 *) 0x04000048 =
                (u16) ((*(volatile u16 *) 0x04000048 & ~0x3f00) | ((*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[7] << 8) | 0x2000);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 4) != 0) {
            *(volatile u16 *) 0x04001048 = (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f) | (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xc] | 0x20);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 0x100) != 0) {
            *(volatile u16 *) 0x04001048 = (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f) | (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xc]);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 8) != 0) {
            *(volatile u16 *) 0x04001048 =
                (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f00) | ((*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x11] << 8) | 0x2000);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 0x200) != 0) {
            *(volatile u16 *) 0x04001048 = (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f00) | ((*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x11] << 8));
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 0x10) != 0) {
            setpair(0x04000040, 0x04000044, (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_1E, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0], (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_1F,
                    (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[1]);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 0x20) != 0) {
            setpair(0x04000042, 0x04000046, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[3], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[5], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[4], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[6]);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 0x40) != 0) {
            setpair(0x04001040, 0x04001044, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[8], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xa], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[9],
                    (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xb]);
        }
        if (((*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 & 0x80) != 0) {
            setpair(0x04001042, 0x04001046, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xd], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xf], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0xe],
                    (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x10]);
        }
        (*(UnkStruct_02001ecc_3 *) data_0213fe74).unk_12 = 0;
    }
    m = (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x12];
    if ((m & 0x20) != 0) {
        G2x_SetBlendBrightnessExt_(0x04000050, 0x1f, 0x20, 0x10, 0x10, 0);
    } else if ((m & 0x10) != 0) {
        G2x_SetBlendAlpha_(0x04000050, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x13], (s8) (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x14], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x15],
                           0x10 - (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x15]);
    } else if ((m & 2) != 0) {
        G2x_SetBlendBrightnessExt_(0x04001050, 0x1f, 0x20, 0x10, 0x10, 0);
    } else if ((m & 8) != 0) {
        G2x_SetBlendAlpha_(0x04001050, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x13], (s8) (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x14], (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x15],
                           0x10 - (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x15]);
    } else if (m != 0) {
        G2x_SetBlendBrightness_(0x04001050, (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x13], (s8) (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x14]);
    }
    (*(UnkStruct_02001ecc_4 *) &data_0213fe94).b[0x12] = 0;
}
