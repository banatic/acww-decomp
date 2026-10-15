/* func_ov004_022389f4 @ 0x022389f4, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055dc8(void *, void *, void *);
extern int func_ov004_02239460(int, int);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);

void func_ov004_022389f4(char *self)
{
    int *p = (int *) (self + 0x15c);
    int r;
    *(u8 *) (self + 0x1e8) = (u8) *p;
    *(u8 *) (self + 0x1c7) = 0;
    if ((unsigned) (*p - 0x35) <= 1) {
        func_02055dc8(self + 0x64, (void *) &func_ov004_0223653c, self);
    }
    if (func_ov004_02239460(0, 2) > 0) {
        r = 1;
    } else {
        r = -1;
    }
    *(s16 *) (self + 0x1c0) = (s16) (r << 0xe);
    func_ov004_022354e0(self);
}
