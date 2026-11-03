/* snowball_spot: 11 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02236110 @ 0x02236110, 0x18 bytes, Thumb
 * func_ov003_022360d8 @ 0x022360d8, 0x36 bytes, Thumb
 * func_ov003_022360b8 @ 0x022360b8, 0x1e bytes, Thumb
 * func_ov003_0223605c @ 0x0223605c, 0x5a bytes, Thumb
 * func_ov003_02236028 @ 0x02236028, 0x34 bytes, Thumb
 * func_ov003_02235fec @ 0x02235fec, 0x3a bytes, Thumb
 * func_ov003_02235fb8 @ 0x02235fb8, 0x34 bytes, Thumb
 * func_ov003_02235f34 @ 0x02235f34, 0x84 bytes, Thumb
 * func_ov003_02235f30 @ 0x02235f30, 0x2 bytes, Thumb
 * func_ov003_02235f2c @ 0x02235f2c, 0x2 bytes, Thumb
 * func_ov003_02235f10 @ 0x02235f10, 0x1c bytes, Thumb
 */

#include "types.h"

extern int func_020644cc(int n);
extern void __cxa_vec_cleanup(void *a, int b, int c, void (*d)(void *));

int func_ov003_022360b8(unsigned short *p, int i, int j);

void func_ov003_02236110(unsigned short *p)
{
    unsigned int i;
    for (i = 0; i < 0x10; i++) {
        p[i] = 0;
    }
    p[0x10] = 0x100;
}

void func_ov003_022360d8(unsigned short *p, int i, int j)
{
    unsigned char s;
    unsigned char k;
    s = i & 0xf;
    k = j & 0xf;
    if (func_ov003_022360b8(p, i, j)) {
        return;
    }
    p[k] |= 1 << s;
    p[0x10]--;
}

int func_ov003_022360b8(unsigned short *p, int i, int j)
{
    unsigned char s;
    unsigned char k;
    s = i & 0xf;
    k = j & 0xf;
    if ((p[k] >> s) & 1) {
        return 1;
    }
    return 0;
}

int func_ov003_0223605c(unsigned short *p, int *ox, int *oz)
{
    int k;
    unsigned int z, x;
    int n;
    if (p[0x10] != 0) {
        n = func_020644cc(p[0x10]);
        k = 0;
        for (z = 0; z < 0x10; z++) {
            for (x = 0; x < 0x10; x++) {
                if (func_ov003_022360b8(p, x, z) == 0) {
                    if (n == k) {
                        *ox = x;
                        *oz = z;
                        return 1;
                    }
                    k++;
                }
            }
        }
    }
    return 0;
}

void func_ov003_02236028(char *base)
{
    unsigned int a, b;
    for (a = 0; a < 4; a++) {
        for (b = 0; b < 4; b++) {
            func_ov003_02236110((unsigned short *) (base + a * 0x88 + b * 0x22));
        }
    }
}

int func_ov003_02235fec(char *base)
{
    int n;
    unsigned int a, b;
    n = 0;
    for (a = 0; a < 4; a++) {
        for (b = 0; b < 4; b++) {
            if (*(unsigned short *) (base + a * 0x88 + b * 0x22 + 0x20) != 0) {
                n++;
            }
        }
    }
    return n;
}

void func_ov003_02235fb8(char *base, int x, int z)
{
    char *e;
    e = base + (((z - 0x10) >> 4) & 3) * 0x88;
    e = e + (((x - 0x10) >> 4) & 3) * 0x22;
    func_ov003_022360d8((unsigned short *) e, x & 0xf, z & 0xf);
}

int func_ov003_02235f34(char *self, int *px, int *py)
{
    unsigned int i;
    unsigned int j;
    int sel;
    int count;
    int n;
    int x;
    int y;
    char *e;

    if ((count = func_ov003_02235fec((char *) self)) != 0) {
        sel = (unsigned int) func_020644cc(count);
        n = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                e = self + i * 0x88 + j * 0x22;
                if (*(u16 *) (e + 0x20) != 0) {
                    if (sel == n) {
                        if (func_ov003_0223605c((unsigned short *) e, &x, &y) != 0) {
                            *px = ((j + 1) << 4) + x;
                            *py = ((i + 1) << 4) + y;
                            return 1;
                        }
                        return 0;
                    }
                    n++;
                }
            }
        }
    }
    return 0;
}

void func_ov003_02235f30(void *element) {}

void func_ov003_02235f2c(void *element) {}

void *func_ov003_02235f10(void *self)
{
    __cxa_vec_cleanup(self, 0x10, 0x22, func_ov003_02235f2c);
    return self;
}
