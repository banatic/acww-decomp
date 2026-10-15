/* func_ov004_0223507c @ 0x0223507c, 0x2f8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define WORD(o, k) (*(int *) ((o) + (k)))
extern u8 data_ov004_022593a0, data_ov004_02255c34;
extern char data_ov004_022593dc[], data_ov004_022593c4[];
extern int func_0205c8c4(int, int);
extern void func_0205c8a8(void);
extern int func_0209d180(void *, unsigned int, int, int, int, int (*)(int, int), void (*)(void), void *);
extern int func_ov004_02234eac(char *);
extern int func_ov004_02234c64(char *);
extern void *func_020b6590(void);
extern int func_020b7dc8(void *, char *, char *, int, int, int, short, int, u8);
extern void func_02004658(int);
int func_ov004_0223507c(char *self)
{
    func_0209d180(self + 0x7f8, 0x38, 0x800, 0x80, 0xc00, func_0205c8c4, func_0205c8a8, 0);
    data_ov004_022593a0 = WORD(self, 8);
    if (data_ov004_022593a0 == 0) {
        WORD(self, 0xa0) = 0xc000;
        WORD(self, 0xa4) = 0x700;
        WORD(self, 0xa8) = 0x5600;
        WORD(self, 0xac) = 0x1000;
        WORD(self, 0xb0) = 0x800;
        WORD(self, 0x104) = 0x15200;
        WORD(self, 0x108) = 0x700;
        WORD(self, 0x10c) = 0x6200;
        WORD(self, 0x110) = 0x1000;
        WORD(self, 0x114) = 0xd00;
        WORD(self, 0x168) = 0x9c00;
        WORD(self, 0x16c) = 0x700;
        WORD(self, 0x170) = 0x14b00;
        WORD(self, 0x174) = 0xa00;
        WORD(self, 0x178) = 0xa00;
        WORD(self, 0x1cc) = 0x15900;
        WORD(self, 0x1d0) = 0x700;
        WORD(self, 0x1d4) = 0x13900;
        WORD(self, 0x1d8) = 0x1000;
        WORD(self, 0x1dc) = 0x800;
        WORD(self, 0x230) = 0x14c00;
        WORD(self, 0x234) = 0x700;
        WORD(self, 0x238) = 0x14a00;
        WORD(self, 0x23c) = 0x700;
        WORD(self, 0x240) = 0x700;
        data_ov004_02255c34 = 5;
        func_ov004_02234eac(self);
        func_020b7dc8(func_020b6590(), self + 0x2a8, data_ov004_022593dc, 0x11c00, 0x5c00, 0x3800, 0, 0x13, 0);
        func_020b7dc8(func_020b6590(), self + 0x550, data_ov004_022593c4, 0x11c00, 0x5c00, 0x3800, 0, 0x13, 1);
    } else {
        WORD(self, 0xa0) = 0x8b00;
        WORD(self, 0xa4) = -0xd00;
        WORD(self, 0xa8) = 0x13e00;
        WORD(self, 0xac) = 0x800;
        WORD(self, 0xb0) = 0x1200;
        WORD(self, 0x104) = 0x9e00;
        WORD(self, 0x108) = -0xd00;
        WORD(self, 0x10c) = 0x14700;
        WORD(self, 0x110) = 0x1100;
        WORD(self, 0x114) = 0x1500;
        WORD(self, 0x168) = 0x12f00;
        WORD(self, 0x16c) = -0xd00;
        WORD(self, 0x170) = 0x13d00;
        WORD(self, 0x174) = 0xa00;
        WORD(self, 0x178) = 0xd00;
        WORD(self, 0x1cc) = 0x16e00;
        WORD(self, 0x1d0) = -0xd00;
        WORD(self, 0x1d4) = 0x13100;
        WORD(self, 0x1d8) = 0x1200;
        WORD(self, 0x1dc) = 0x1400;
        data_ov004_02255c34 = 4;
        WORD(self, 0x294) = 0x9e00;
        WORD(self, 0x298) = -0xd00;
        WORD(self, 0x29c) = 0x14700;
        WORD(self, 0x2a0) = 0xc00;
        WORD(self, 0x2a4) = 0x2000;
        func_ov004_02234c64(self);
        func_020b7dc8(func_020b6590(), self + 0x2a8, data_ov004_022593dc, 0x26000, 0x4dc3, 0x3800, 0, 0x13, 0);
    }
    func_02004658(0x4da);
    return 1;
}
