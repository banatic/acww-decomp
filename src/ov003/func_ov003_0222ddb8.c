/* func_ov003_0222ddb8 @ 0x0222ddb8, 0x10c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int data_021c67a4;
extern int data_021c67d0[];
extern char data_ov003_022617bc[];
extern char data_ov003_02260994[];

extern void *func_020ba4e4(void);
extern int func_ov003_0222d248(int a, void *ctx);
extern void func_ov003_0222fe18(void *a, void *e, int n);

void func_ov003_0222ddb8(void *a0, int a1)
{
    int g;
    char *e;
    int n;
    int x0, z0, x1, z1;
    void *ctx;
    int zero1, zero2;
    volatile Vec3 c;
    u8 i;
    int *p;
    int r;
    int v;

    g = data_021c67a4;
    if (a1 == 1) {
        e = data_ov003_022617bc;
        n = 8;
    } else {
        e = data_ov003_02260994;
        n = 2;
    }
    if (g == 0) {
        return;
    }
    c.x = data_021c67d0[0];
    c.y = data_021c67d0[1];
    c.z = data_021c67d0[2];
    x0 = data_021c67d0[0] - 0x10000;
    z0 = data_021c67d0[2] - 0x1c000;
    x1 = data_021c67d0[0] + 0x10000;
    z1 = data_021c67d0[2] + 0xc000;
    ctx = func_020ba4e4();
    zero1 = 0;
    zero2 = 0;
    for (i = 0; i < n; i++) {
        if (*(u8 *) (e + 0x248) != 0 && *(s8 *) (e + 0x24d) >= 0) {
            p = (int *) (e + 0x204);
            r = func_ov003_0222d248(*(s8 *) (e + 0x24d), ctx);
            if (*(u8 *) (e + 0x249) == 0 && r == 4) {
                func_ov003_0222fe18(a0, e, a1);
            } else {
                if (r == 5) {
                    *(u8 *) (e + 0x246) = (u8) zero1;
                } else {
                    *(u8 *) (e + 0x246) = 1;
                }
                v = p[0];
                if (x0 < v && x1 > v && z0 < p[2] && z1 > p[2]) {
                    *(u8 *) (e + 0x249) = 1;
                } else {
                    *(u8 *) (e + 0x249) = (u8) zero2;
                }
            }
        }
        e += 0x25c;
    }
}
