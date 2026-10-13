/* func_ov004_02213860 @ 0x02213860, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020e895c(void *p, int a, int b);
extern int FX_MulFunc(int a, s16 b);

int func_ov004_02213860(char *self)
{
    func_020e895c(self + 0x84c, 0, 0x5a00);
    if (*(int *) (self + 0x84c) == 0) {
        *(s16 *) (self + 0x848) = 0;
    } else {
        *(s16 *) (self + 0x848) = (s16) (*(s16 *) (self + 0x848) + 0x960);
    }
    func_020e895c(self + 0x850, FX_MulFunc(*(int *) (self + 0x84c), *(s16 *) (self + 0x848)), 0x5a00);
    return 1;
}
