/* museum_aquarium_5: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223546c @ 0x0223546c, 0x74 bytes, Thumb
 * func_ov004_02235374 @ 0x02235374, 0xf8 bytes, Thumb
 * func_ov004_0223507c @ 0x0223507c, 0x2f8 bytes, Thumb
 */

#include "types.h"

#define WORD(o, k) (*(int *) ((o) + (k)))

extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern char *data_ov004_022594d4[];
extern void *func_0209d238(void *, void *);
extern void func_0209d0a4(void *);
extern unsigned char *data_ov004_022593ac;
extern unsigned char *data_ov004_022593b4;
extern unsigned char *data_ov004_022593b8;
extern void func_020e9898(void *);
extern void func_0205502c(void *);
extern int func_02055454(void *);
extern void func_0209d090(void *);
extern void func_0209d200(void *, void *);
extern void func_02004280(void *);
extern u8 data_ov004_022593a0;
extern u8 data_ov004_02255c34;
extern char data_ov004_022593dc[];
extern char data_ov004_022593c4[];
extern int func_0205c8c4(int, int);
extern void func_0205c8a8(void);
extern int func_0209d180(void *, unsigned int, int, int, int, int (*)(int, int), void (*)(void), void *);
extern int func_ov004_02234eac(char *);
extern int func_ov004_02234c64(char *);
extern void *func_020b6590(void);
extern int func_020b7dc8(void *, char *, char *, int, int, int, short, int, u8);
extern void func_02004658(int);

int func_ov004_0223546c(char *self, int i)
{
    char **e;
    if (i < (int) data_ov004_022593a4 || i >= (int) data_ov004_02255c30) {
        return 0;
    }
    e = &data_ov004_022594d4[i];
    if (*e == 0) {
        return 0;
    }
    *(int *) (*e + 0x15c) = i;
    *(int *) (*e + 0x160) = 1;
    func_0209d238(self + 0x7f8, *e + 0x166);
    func_0209d0a4(*e + 0x168);
    return 1;
}

void func_ov004_02235374(unsigned char *self, int index)
{
    if (index >= (*(unsigned char *) &data_ov004_022593a4) && index < (*(unsigned char *) &data_ov004_02255c30)) {
        unsigned char **slot = &((unsigned char * *) data_ov004_022594d4)[index];
        int i;
        for (i = 0; i < 4; ++i) {
            if (*(void **) (*slot + 0x54 + i * 4)) {
                func_020e9898(*(void **) (*slot + 0x54 + i * 4));
                *(void **) (*slot + 0x54 + i * 4) = 0;
            }
        }
        *(int *) (*slot + 0x160) = 0;
        func_0205502c(*slot + 0x64);
        func_02055454(*slot + 0x64);
        func_0209d090(*slot + 0x168);
        func_0209d200(self + 0x7f8, *slot + 0x166);
        switch (*(int *) (*slot + 0x15c)) {
            case 11:
                if (data_ov004_022593ac) {
                    func_02004280(data_ov004_022593ac + 0x1fc);
                    data_ov004_022593ac = 0;
                }
                break;
            case 36:
                if (data_ov004_022593b4) {
                    data_ov004_022593b4 = 0;
                }
                break;
            case 35:
                if (data_ov004_022593b8) {
                    data_ov004_022593b8 = 0;
                }
                break;
        }
        *(int *) (*slot + 0x15c) = -1;
    }
}

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
