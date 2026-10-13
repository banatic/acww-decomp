/* func_ov003_02227e94 @ 0x02227e94, 0x150 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern u8 data_020cb784[];
extern int func_0204fb3c(int *e, int *f, int flag);
extern int func_ov003_02227ab0(char *self, int *a, int *b, int *c, int *d, int f, int mode, char *rec);
extern int func_ov003_02227a48(char *self, char *rec, int e);
extern void func_0204f794(Vec3 *v, int a, int b);

int func_ov003_02227e94(char *self, char *rec, int mode)
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    Vec3 v;
    int r;
    int g;
    r = 0;
    a = -1;
    b = -1;
    c = -1;
    d = -1;
    switch (mode) {
        case 0:
            g = 0;
            break;
        default:
            g = 1;
            break;
    }
    if (func_0204fb3c(&e, &f, g)) {
        if (func_ov003_02227ab0(self, &a, &b, &c, &d, f, mode, rec)) {
            if (func_ov003_02227a48(self, rec, e)) {
                int *p;
                int *q;
                func_0204f794(&v, a, b);
                v.y = 0xffffeccd;
                {
                    int t = e;
                    *(u8 *) (rec + 0x7e) = t;
                    *(u8 *) (rec + 0x7f) = (unsigned) (t - 0x34) <= 2;
                }
                *(u8 *) (rec + 0x1fe) = f;
                *(u8 *) (rec + 0x1ff) = data_020cb784[e * 6];
                *(short *) (rec + 0x138) = 0xffff8000;
                *(int *) (rec + 0x12c) = v.x;
                *(int *) (rec + 0x130) = v.y;
                *(int *) (rec + 0x134) = v.z;
                *(u8 *) (rec + 0x1fc) = mode;
                r = 1;
                *(int *) (rec + 0x80) = r;
                *(u8 *) (rec + 0x200) = 0;
                p = (int *) (rec + 0x218);
                p[0] = v.x;
                p[1] = v.y;
                p[2] = v.z;
                {
                    int dd = d;
                    q = (int *) (rec + 0x208);
                    q[0] = c;
                    q[1] = dd;
                }
                *(int *) (rec + 0x244) = -1;
            }
        } else if (mode == 0) {
            *(u8 *) (rec + 0x1fc) = 3;
        } else if (mode == 1) {
            *(u8 *) (rec + 0x1fc) = 4;
        }
    } else if (mode == 0) {
        *(u8 *) (rec + 0x1fc) = 5;
    } else if (mode == 1) {
        *(u8 *) (rec + 0x1fc) = 6;
    }
    return r;
}
