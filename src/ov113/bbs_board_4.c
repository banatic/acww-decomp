/* bbs_board_4: 4 functions, module ov113
 * mwccarm 1.2/base -O4,s
 * func_ov113_0229aaa8 @ 0x0229aaa8, 0x3c bytes, Thumb
 * func_ov113_0229aa8c @ 0x0229aa8c, 0x1a bytes, Thumb
 * func_ov113_0229aa34 @ 0x0229aa34, 0x58 bytes, Thumb
 * func_ov113_0229a958 @ 0x0229a958, 0xdc bytes, Thumb
 */

#include "types.h"

struct Context {
    u8 pad_00[0x9a];
    u8 index;
    u8 pad_9B[2];
    u8 count;
};

struct Elem {
    int a;
    int b;
};

extern void G2x_SetBlendBrightnessExt_(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4,
                                       unsigned int a5);
extern void func_ov002_02208090(unsigned int a0, unsigned int a1);
extern unsigned char *func_ov002_022080a0(unsigned int a0, unsigned char value);
extern void func_ov113_0229a474(unsigned int a0);
extern int func_020ee45c(void *p);
extern void func_ov092_0229929c(int x);
extern void func_ov113_0229a404(void *p);
extern struct Elem data_ov113_0229ac60[];
extern int func_020896b8(int, void *, int, int, int, int, int);
extern int func_ov113_02299da4(unsigned char *self, int a);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_02088df8(int a0, void *a1, int a2, void *a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10,
                          int a11);
extern int func_ov002_02207f54(unsigned char *self);
extern unsigned char data_ov113_0229ac80[];

int func_ov113_0229aaa8(unsigned int arg0)
{
    G2x_SetBlendBrightnessExt_(0x04000050, 0x1f, 0x20, 0x10, 0x10, 0);
    func_ov113_0229a474(arg0);
    func_ov002_02208090(arg0, 0);
    func_ov002_022080a0(arg0, 1);
    return 1;
}

int func_ov113_0229aa8c(void *p)
{
    func_ov092_0229929c(func_020ee45c(p));
    func_ov113_0229a404(p);
    return 1;
}

void func_ov113_0229aa34(struct Context *self, int arg1, int arg2)
{
    u8 i = 0;
    int flag = 0;
    while (i < self->count) {
        int a = (i == self->index) ? 11 : 10;
        func_020896b8(flag, &data_ov113_0229ac60[i + 8], arg1, arg2, a, 1, flag);
        i++;
    }
}

int func_ov113_0229a958(unsigned char *self)
{
    int r4;
    void *r6;
    int mode1;
    int mode2;

    if (func_ov113_02299da4(self, 8) == 0) {
        return 1;
    }
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self + 0x2b20);
    }

    r4 = 0x80;
    r6 = (void *) ((char *) *(char **) (self + 0x94) + 0x60);
    mode1 = 0xa;
    mode2 = 0xa;
    if (func_ov113_02299da4(self, 2) != 0) {
        mode1 = 0xb;
    } else if (func_ov113_02299da4(self, 4) != 0) {
        mode2 = 0xb;
    }

    func_02088df8(0, ((unsigned char *) data_ov113_0229ac60), 0x80, r6, mode1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(0, data_ov113_0229ac80, 0x80, r6, mode2, 1, 0x1000, 0x1000, 0, -1, 0, 0);

    r4 += self[0x9e];
    if (func_ov113_02299da4(self, 0x100) != 0) {
        r4 += func_ov002_02207f54(self);
    }

    func_ov113_0229aa34((struct Context *) self, r4, (int) r6);
    return 1;
}
