/* func_ov004_0222e860 @ 0x0222e860, 0x3d0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int m[12];
} Matrix;
#define WORD(o, k) (*(int *) ((o) + (k)))
#define BYTE(o, k) (*(u8 *) ((o) + (k)))
#define MAT(o, k) (*(Matrix *) ((o) + (k)))
extern Matrix data_021fbe48;
extern int data_ov004_0225836c[3], data_ov004_0225839c[3];
extern int data_ov004_02258318[3], data_ov004_02258330[3], data_ov004_02258348[3];
extern Matrix *func_ov004_022236dc(void);
extern Matrix *func_ov004_022236f0(void);
extern void func_020e96c8(Matrix *, int, int, int);
extern void func_0205510c(char *, int);
#define TRANSLATE(v) func_020e96c8(&data_021fbe48, (v)[0], (v)[1], (v)[2])
#define FIXED_POSITION()                                                                                                      \
    {                                                                                                                         \
        WORD(self, 0xf10) = 0x16a00;                                                                                          \
        WORD(self, 0xf14) = 0x1900;                                                                                           \
        WORD(self, 0xf18) = 0x15000;                                                                                          \
    }
#define COPY_POSITION()                                                                                                       \
    {                                                                                                                         \
        WORD(self, 0xf10) = data_021fbe48.m[9];                                                                               \
        WORD(self, 0xf14) = data_021fbe48.m[10];                                                                              \
        WORD(self, 0xf18) = data_021fbe48.m[11];                                                                              \
    }
void func_ov004_0222e860(char *self)
{
    u8 i;
    data_021fbe48 = *func_ov004_022236dc();
    MAT(self, 0x150) = data_021fbe48;
    data_021fbe48 = *func_ov004_022236f0();
    MAT(self, 0x2f4) = data_021fbe48;
    if (WORD(self, 0xefc) == 8 || WORD(self, 0xefc) == 9) {
        TRANSLATE(data_ov004_0225836c);
        MAT(self, 0x3ac) = data_021fbe48;
    } else if (WORD(self, 0xefc) == 5) {
        if ((u16) (WORD(self, 0x3ec) >> 12) >= 16) {
            TRANSLATE(data_ov004_0225836c);
            FIXED_POSITION();
        } else {
            data_021fbe48 = *func_ov004_022236dc();
            COPY_POSITION();
        }
    } else if (WORD(self, 0xefc) == 6) {
        if ((u16) (WORD(self, 0x3ec) >> 12) >= (u16) (WORD(self, 0x3e8) >> 12) - 45) {
            TRANSLATE(data_ov004_0225836c);
            FIXED_POSITION();
        } else {
            data_021fbe48 = *func_ov004_022236dc();
            COPY_POSITION();
        }
    } else {
        data_021fbe48 = *func_ov004_022236dc();
        COPY_POSITION();
    }
    MAT(self, 0x3ac) = data_021fbe48;
    if (WORD(self, 0xefc) == 8 || WORD(self, 0xefc) == 9) {
        TRANSLATE(data_ov004_0225836c);
        MAT(self, 0x464) = data_021fbe48;
    } else if (WORD(self, 0xefc) == 5) {
        if ((u16) (WORD(self, 0x4a4) >> 12) >= 16) {
            TRANSLATE(data_ov004_0225836c);
        } else {
            data_021fbe48 = *func_ov004_022236dc();
        }
    } else if (WORD(self, 0xefc) == 6) {
        if ((u16) (WORD(self, 0x4a4) >> 12) >= (u16) (WORD(self, 0x4a0) >> 12) - 45) {
            TRANSLATE(data_ov004_0225836c);
        } else {
            data_021fbe48 = *func_ov004_022236dc();
        }
    } else {
        data_021fbe48 = *func_ov004_022236dc();
    }
    MAT(self, 0x464) = data_021fbe48;
    {
        u16 phase = (u16) (WORD(self, 0x55c) >> 12);
        if (phase >= 15 && phase <= 72) {
            data_021fbe48 = *func_ov004_022236f0();
        } else {
            TRANSLATE(data_ov004_0225839c);
        }
    }
    MAT(self, 0x51c) = data_021fbe48;
    TRANSLATE(data_ov004_02258318);
    MAT(self, 0x5d4) = data_021fbe48;
    MAT(self, 0x68c) = data_021fbe48;
    TRANSLATE(data_ov004_02258330);
    MAT(self, 0x744) = data_021fbe48;
    MAT(self, 0x7fc) = data_021fbe48;
    TRANSLATE(data_ov004_02258348);
    MAT(self, 0x8b4) = data_021fbe48;
    if (BYTE(self, 0xef9)) {
        func_0205510c(self + 0xec, 0);
    }
    for (i = 0; i < 9; i++) {
        if (BYTE(self + i, 0xef0)) {
            func_0205510c(self + 0x290 + i * 0xb8, 0);
        }
    }
}
