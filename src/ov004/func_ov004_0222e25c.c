/* func_ov004_0222e25c @ 0x0222e25c, 0x1f0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned short func_ov004_022236c4(void);
extern int func_ov004_022236a8(void);
extern void func_ov004_0222db14(void *, int, void *, void *, int, int, int, int);
void func_ov004_0222e25c(u8 *self)
{
    unsigned int frame = func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf2) {
        func_ov004_0222db14(self, 0, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf4) {
        func_ov004_0222db14(self, 1, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf6) {
        if (frame <= 6) {
            self[0xef9] = 1;
            self[0xef0] = 1;
        } else {
            self[0xef9] = 0;
            self[0xef0] = 0;
        }
        if (frame >= 18) {
            self[0xef1] = 1;
            self[0xef2] = 1;
        } else {
            self[0xef1] = 0;
            self[0xef2] = 0;
        }
        func_ov004_0222db14(self, 2, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 2, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 2, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 2, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf3) {
        func_ov004_0222db14(self, 0, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf5) {
        func_ov004_0222db14(self, 1, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    }
}
