/* func_ov004_02233aa4 @ 0x02233aa4, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02045f08(void *, int);

void func_ov004_02233aa4(char *self)
{
    int t[2];
    if (*(u8 *) (self + 0x8f) != 0) {
        *(u8 *) (self + 0x8f) = 0;
        t[0] = *(int *) (self + 0x10);
        t[1] = *(int *) (self + 0x14);
        func_02045f08(t, *(u8 *) (self + 0x90));
    }
}
