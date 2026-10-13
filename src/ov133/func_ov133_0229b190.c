/* func_ov133_0229b190 @ 0x0229b190, 0x58 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov133_0229b320(u8 *self, u8 v);
extern void func_ov133_0229ad78(u8 *self, int x);

void func_ov133_0229b190(u8 *self)
{
    unsigned int a = self[0xa3];
    unsigned int b = self[0xa2];
    int lo, hi;

    if (b < a) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }
    func_ov133_0229b320(self, lo);
    for (; hi < 0xc; lo++, hi++) {
        u8 *s = self + hi;
        u8 *d = self + lo;
        d[0xa4] = s[0xa4];
    }
    for (; lo < 0xc; lo++) {
        u8 *d = self + lo;
        d[0xa4] = 0xa;
    }
    func_ov133_0229ad78(self, 8);
}
