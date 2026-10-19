/* func_ov133_0229b0f0 @ 0x0229b0f0, 0xa0 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200467c(int cmd);
extern void func_ov133_0229b190(u8 *self);
extern void func_ov133_0229b320(u8 *self, u8 v);
extern void func_ov133_0229ad78(u8 *self, int v);

int func_ov133_0229b0f0(u8 *self, u8 v)
{
    int i;

    if (self[0x9f] == 0xc && self[0xa2] == self[0xa3]) {
        func_0200467c(0x34);
        return 0;
    }
    if (self[0xa2] == self[0xa3] && self[0xaf] != 0xa) {
        func_0200467c(0x34);
        return 0;
    }
    if (self[0xa2] != self[0xa3]) {
        func_ov133_0229b190(self);
    }
    i = 0xb;
    while (i > self[0x9f]) {
        u8 *s = self + (i - 1);
        u8 *d = self + i;

        d[0xa4] = s[0xa4];
        i--;
    }
    {
        u8 *d = self + self[0x9f];
        d[0xa4] = v;
    }
    func_ov133_0229b320(self, self[0x9f] + 1);
    func_ov133_0229ad78(self, 8);
    return 1;
}
