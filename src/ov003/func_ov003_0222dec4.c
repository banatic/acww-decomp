/* func_ov003_0222dec4 @ 0x0222dec4, 0x144 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_022617bc[];
extern char data_ov003_02260994[];

extern void *func_020ba4e4(void);
extern int func_ov003_0222d248(int a, void *ctx);
extern int func_020a7278(void);
extern void func_ov003_0222fe18(void *a0, void *e, int n);

void func_ov003_0222dec4(void *a0, int mode, int slot, int x, int z)
{
    int n;
    int x0, z0, x1, z1;
    void *ctx;
    int rr;
    int *pp;
    int bit;
    int mask;
    int zero;
    char *e;
    u8 i;
    int f;
    int g;
    int v;

    if (mode == 1) {
        e = data_ov003_022617bc;
        n = 8;
    } else {
        e = data_ov003_02260994;
        n = 2;
    }
    x0 = x - 0x10000;
    z0 = z - 0x1c000;
    x1 = x + 0x10000;
    z1 = z + 0xc000;
    ctx = func_020ba4e4();
    i = 0;
    bit = 1 << slot;
    mask = ~(bit & 0xf);
    zero = 0;
    for (; i < n; i++) {
        if (*(u8 *) (e + 0x248) != 0 && *(s8 *) (e + 0x24d) >= 0) {
            pp = (int *) (e + 0x204);
            f = *(u8 *) (e + 0x258);
            rr = func_ov003_0222d248(*(s8 *) (e + 0x24d), ctx);
            if (func_020a7278() == 0 && rr == 4) {
                rr = 3;
            }
            g = *(u8 *) (e + 0x249);
            if (g == 0 && rr == 4) {
                func_ov003_0222fe18(a0, e, mode);
            } else {
                v = pp[0];
                if (x0 < v && x1 > v && z0 < pp[2] && z1 > pp[2]) {
                    if (g == 0) {
                        *(u8 *) (e + 0x249) = 1;
                        f |= bit;
                        *(u8 *) (e + 0x258) = (u8) f;
                    }
                } else if (((f >> slot) & 1) != 0) {
                    f &= mask;
                    *(u8 *) (e + 0x258) = (u8) f;
                } else if (g != 0 && f == 0 && mode == 1) {
                    *(u8 *) (e + 0x249) = (u8) zero;
                }
            }
        }
        e += 0x25c;
    }
}
