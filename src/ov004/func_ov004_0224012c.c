/* func_ov004_0224012c @ 0x0224012c, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_ov004_0223edd8(void);
extern int func_020644cc(int);

void func_ov004_0224012c(char *self)
{
    char *o;
    int v;
    if (*(signed char *) (self + 0x196) == 0x23) {
        o = func_ov004_0223edd8();
        if (func_020644cc(0x64) > 0x32) {
            v = (short) (0x14 * (func_020644cc(9) + 4));
            *(int *) (self + 0x174) = v;
            *(int *) (o + 0x174) = v;
            *(short *) (self + 0x172) = 4;
            *(short *) (o + 0x172) = 4;
        } else {
            v = (short) (0x14 * (func_020644cc(3) + 2));
            if (*(u8 *) (self + 0x22) == 0) {
                v = (short) (3 * v);
            }
            *(int *) (self + 0x174) = v;
            *(int *) (o + 0x174) = v;
            *(int *) (self + 0x15c) = 0;
            *(short *) (self + 0x172) = 0x19;
            *(short *) (o + 0x172) = 0x19;
        }
    } else if (*(short *) (self + 0x172) == 0x19) {
        *(int *) (self + 0x15c) = 0;
    }
}
