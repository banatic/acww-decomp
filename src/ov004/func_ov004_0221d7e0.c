/* func_ov004_0221d7e0 @ 0x0221d7e0, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_ov004_0221d4e8(void);
extern int func_020e8b4c(int a, int b);
extern int func_020644cc(int);
extern int func_ov004_0221dd24(void *self, int a);

void func_ov004_0221d7e0(char *self)
{
    short a;
    short b;
    char *o;
    int d1;
    int d2;
    a = *(short *) (self + 0xa50);
    b = (short) (a + 0x8000);
    o = func_ov004_0221d4e8();
    if (o == 0) {
        return;
    }
    d1 = func_020e8b4c(a, *(short *) (self + 0x8e));
    d2 = func_020e8b4c(b, *(short *) (o + 0x8e));
    if (d1 > 0x500) {
        return;
    }
    if (d2 > 0x500) {
        return;
    }
    if (func_020644cc(2) != 0) {
        if (func_ov004_0221dd24(self, 3) != 0) {
            *(u16 *) (self + 0xa4e) = 0x12c;
        }
    } else {
        if (func_ov004_0221dd24(self, 2) != 0) {
            *(u16 *) (self + 0xa4e) = 0x12c;
        }
    }
}
