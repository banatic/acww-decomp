/* func_ov122_022a0e90 @ 0x022a0e90, 0xe6 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov122_0229f5a0(void *self);
extern void *func_ov122_0229f5f8(void *self);
extern int func_ov122_0229f5c8(void *self);
extern void func_ov122_0229f590(void *self, int v);
extern int func_ov095_0229bc00(void *obj, void *a, int b, u8 *sav, int p4, int p5, int p6, int p7, int p8, int p9);
extern int func_ov095_0229bcec(void *obj, void *a, int b, u8 *sav, int p4, int p5, int p6, int p7);

int func_ov122_022a0e90(void *self, int b, int c)
{
    u8 sav;
    u8 old;
    void *r7v;
    int x;
    u8 *p;

    sav = (u8) func_ov122_0229f5a0(self);
    old = sav;
    r7v = func_ov122_0229f5f8(self);
    x = func_ov122_0229f5c8(self);

    if (*((u8 *) self + 0xaa) == 2) {
        if (func_ov095_0229bc00((void *) ((char *) self + 0xc0), r7v, b, &sav, 0x40, 0x28, 4, 0xa0, 0, c) != 0) {
            func_ov122_0229f590(self, sav);
        } else {
            return 0;
        }
    } else {
        if (b == 0xa) {
            return 0;
        }
        if (func_ov095_0229bcec((void *) ((char *) self + 0xc0), r7v, b, &sav, x, 0xa0, 0, 1) != 0) {
            switch (*((u8 *) self + 0xaa)) {
                case 0:
                    if (old != sav) {
                        p = *(u8 **) ((char *) self + 0xbc);
                        *(p + 0xf8) = (u8) (*(p + 0xf8) + sav - old);
                    }
                    break;
                case 1:
                    p = *(u8 **) ((char *) self + 0xbc);
                    sav = (u8) (sav - *(p + 0xf8));
                    break;
                default:
                    break;
            }
            func_ov122_0229f590(self, sav);
        } else {
            return 0;
        }
    }
    return 1;
}
