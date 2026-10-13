/* func_ov004_02241f88 @ 0x02241f88, 0xf0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_ov004_0223edd8(void);
extern int func_020e8bb0(int *p, int a, int b, int c, int d);
extern int func_ov004_02244c20(void *self);
extern int func_020644cc(int);

void func_ov004_02241f88(char *self)
{
    char *o;
    u8 c = *(u8 *) (self + 0x196);
    int tmp;
    int v;
    if (c == 0x23) {
        o = func_ov004_0223edd8();
    }
    switch (*(short *) (self + 0x172)) {
        case 4:
            tmp = *(int *) (self + 0x15c);
            if (func_020e8bb0(&tmp, 0x1000, 0x66, 0x1000, 0x29) == 0) {
                *(short *) (self + 0x172) = 5;
            }
            *(int *) (self + 0x15c) = tmp;
            break;
        case 5:
            if (func_ov004_02244c20(self) != 0) {
                *(short *) (self + 0x172) = 0x19;
                *(int *) (self + 0x15c) = 0;
                if (c == 0x23) {
                    v = (short) (0x14 * (func_020644cc(3) + 2));
                    if (*(u8 *) (self + 0x22) == 0) {
                        v = (short) (3 * v);
                    }
                    *(int *) (self + 0x174) = v;
                    *(short *) (o + 0x98) = (short) v;
                } else {
                    *(int *) (self + 0x174) = *(short *) (self + 0x98);
                }
            }
            break;
        default:
            if (func_ov004_02244c20(self) != 0) {
                *(short *) (self + 0x172) = 4;
                if (c == 0x23) {
                    v = (short) (0x14 * (func_020644cc(9) + 2));
                    *(int *) (self + 0x174) = v;
                    *(short *) (o + 0x98) = (short) v;
                } else if (*(short *) (self + 0x98) > 0) {
                    *(int *) (self + 0x174) = *(short *) (self + 0x98);
                }
            }
            break;
    }
}
