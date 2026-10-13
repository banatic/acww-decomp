/* func_02001ecc @ 0x02001ecc, 0x488 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern UnkStruct_02001ecc_3 data_0213fe74;
extern UnkStruct_02001ecc data_0213fdf4;
extern u32 data_0213fdfc;
extern u32 data_0213fe1c;
extern UnkStruct_02001ecc_2 data_0213fe34;
extern u32 data_0213fe44;
extern u32 data_0213fe64;
extern UnkStruct_02001ecc_4 data_0213fe94;

extern void G2x_SetBGyAffine_(u32 reg, void *p, u32 a, u32 b, u32 c, u32 d);
extern void G3X_SetHOffset(u32 v);
extern void G2x_SetBlendBrightnessExt_(u32 reg, int a, int b, int c, int d, int e);
extern void G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern void G2x_SetBlendBrightness_(u32 reg, int a, int b);

static __inline void setpair(u32 ra, u32 rb, int a, int b, int c, int d)
{
    *(volatile u16 *) ra = (u16) (((a << 8) & 0xff00) | (b & 0xff));
    *(volatile u16 *) rb = (u16) (((c << 8) & 0xff00) | (d & 0xff));
}

void func_02001ecc(void)
{
    int m;

    if (data_0213fe74.unk_11 != 0) {
        if ((data_0213fe74.unk_11 & 1) != 0) {
            if ((*(volatile u32 *) 0x04000000 & 8) == 0) {
                *(volatile u32 *) 0x04000010 = (data_0213fdf4.unk_00 & 0x1ff) | (((u32) data_0213fdf4.h1 << 16) & 0x01ff0000);
            } else {
                G3X_SetHOffset(data_0213fdf4.unk_00);
            }
        }
        if ((data_0213fe74.unk_11 & 2) != 0) {
            *(volatile u32 *) 0x04000014 = (data_0213fdf4.h2 & 0x1ff) | (((u32) data_0213fdf4.h3 << 16) & 0x01ff0000);
        }
        if ((data_0213fe74.unk_11 & 4) != 0) {
            if ((data_0213fe74.unk_10 & 1) != 0) {
                G2x_SetBGyAffine_(0x04000020, &data_0213fdfc, data_0213fdf4.unk_18, data_0213fdf4.unk_1C, data_0213fdf4.unk_20,
                                  data_0213fdf4.unk_24);
            } else {
                *(volatile u32 *) 0x04000018 = (data_0213fdf4.unk_20 & 0x1ff) | ((data_0213fdf4.unk_24 << 16) & 0x01ff0000);
            }
        }
        if ((data_0213fe74.unk_11 & 8) != 0) {
            if ((data_0213fe74.unk_10 & 2) != 0) {
                G2x_SetBGyAffine_(0x04000030, &data_0213fe1c, data_0213fdf4.unk_38, data_0213fdf4.unk_3C, data_0213fdf4.unk_40,
                                  data_0213fdf4.unk_44);
            } else {
                *(volatile u32 *) 0x0400001c = (data_0213fdf4.unk_40 & 0x1ff) | ((data_0213fdf4.unk_44 << 16) & 0x01ff0000);
            }
        }
        if ((data_0213fe74.unk_11 & 0x10) != 0) {
            *(volatile u32 *) 0x04001010 = (data_0213fe34.unk_08 & 0x1ff) | (((u32) data_0213fe34.unk_0A << 16) & 0x01ff0000);
        }
        if ((data_0213fe74.unk_11 & 0x20) != 0) {
            *(volatile u32 *) 0x04001014 = (data_0213fe34.unk_0C & 0x1ff) | (((u32) data_0213fe34.unk_0E << 16) & 0x01ff0000);
        }
        if ((data_0213fe74.unk_11 & 0x40) != 0) {
            if ((data_0213fe74.unk_10 & 4) != 0) {
                G2x_SetBGyAffine_(0x04001020, &data_0213fe44, data_0213fdf4.unk_60, data_0213fdf4.unk_64, data_0213fdf4.unk_68,
                                  data_0213fdf4.unk_6C);
            } else {
                *(volatile u32 *) 0x04001018 = (data_0213fdf4.unk_68 & 0x1ff) | ((data_0213fdf4.unk_6C << 16) & 0x01ff0000);
            }
        }
        if ((data_0213fe74.unk_11 & 0x80) != 0) {
            if ((data_0213fe74.unk_10 & 8) != 0) {
                G2x_SetBGyAffine_(0x04001030, &data_0213fe64, data_0213fe74.unk_00, data_0213fe74.unk_04, data_0213fe74.unk_08,
                                  data_0213fe74.unk_0C);
            } else {
                *(volatile u32 *) 0x0400101c = (data_0213fe74.unk_08 & 0x1ff) | ((data_0213fe74.unk_0C << 16) & 0x01ff0000);
            }
        }
        data_0213fe74.unk_11 = 0;
    }
    if (data_0213fe74.unk_12 != 0) {
        if ((data_0213fe74.unk_12 & 1) != 0) {
            *(volatile u16 *) 0x04000048 = (u16) ((*(volatile u16 *) 0x04000048 & ~0x3f) | data_0213fe94.b[2] | 0x20);
        }
        if ((data_0213fe74.unk_12 & 2) != 0) {
            *(volatile u16 *) 0x04000048 =
                (u16) ((*(volatile u16 *) 0x04000048 & ~0x3f00) | (data_0213fe94.b[7] << 8) | 0x2000);
        }
        if ((data_0213fe74.unk_12 & 4) != 0) {
            *(volatile u16 *) 0x04001048 = (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f) | data_0213fe94.b[0xc] | 0x20);
        }
        if ((data_0213fe74.unk_12 & 0x100) != 0) {
            *(volatile u16 *) 0x04001048 = (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f) | data_0213fe94.b[0xc]);
        }
        if ((data_0213fe74.unk_12 & 8) != 0) {
            *(volatile u16 *) 0x04001048 =
                (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f00) | (data_0213fe94.b[0x11] << 8) | 0x2000);
        }
        if ((data_0213fe74.unk_12 & 0x200) != 0) {
            *(volatile u16 *) 0x04001048 = (u16) ((*(volatile u16 *) 0x04001048 & ~0x3f00) | (data_0213fe94.b[0x11] << 8));
        }
        if ((data_0213fe74.unk_12 & 0x10) != 0) {
            setpair(0x04000040, 0x04000044, data_0213fe74.unk_1E, data_0213fe94.b[0], data_0213fe74.unk_1F,
                    data_0213fe94.b[1]);
        }
        if ((data_0213fe74.unk_12 & 0x20) != 0) {
            setpair(0x04000042, 0x04000046, data_0213fe94.b[3], data_0213fe94.b[5], data_0213fe94.b[4], data_0213fe94.b[6]);
        }
        if ((data_0213fe74.unk_12 & 0x40) != 0) {
            setpair(0x04001040, 0x04001044, data_0213fe94.b[8], data_0213fe94.b[0xa], data_0213fe94.b[9],
                    data_0213fe94.b[0xb]);
        }
        if ((data_0213fe74.unk_12 & 0x80) != 0) {
            setpair(0x04001042, 0x04001046, data_0213fe94.b[0xd], data_0213fe94.b[0xf], data_0213fe94.b[0xe],
                    data_0213fe94.b[0x10]);
        }
        data_0213fe74.unk_12 = 0;
    }
    m = data_0213fe94.b[0x12];
    if ((m & 0x20) != 0) {
        G2x_SetBlendBrightnessExt_(0x04000050, 0x1f, 0x20, 0x10, 0x10, 0);
    } else if ((m & 0x10) != 0) {
        G2x_SetBlendAlpha_(0x04000050, data_0213fe94.b[0x13], (s8) data_0213fe94.b[0x14], data_0213fe94.b[0x15],
                           0x10 - data_0213fe94.b[0x15]);
    } else if ((m & 2) != 0) {
        G2x_SetBlendBrightnessExt_(0x04001050, 0x1f, 0x20, 0x10, 0x10, 0);
    } else if ((m & 8) != 0) {
        G2x_SetBlendAlpha_(0x04001050, data_0213fe94.b[0x13], (s8) data_0213fe94.b[0x14], data_0213fe94.b[0x15],
                           0x10 - data_0213fe94.b[0x15]);
    } else if (m != 0) {
        G2x_SetBlendBrightness_(0x04001050, data_0213fe94.b[0x13], (s8) data_0213fe94.b[0x14]);
    }
    data_0213fe94.b[0x12] = 0;
}
