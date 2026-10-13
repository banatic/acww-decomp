/* func_ov123_0229b228 @ 0x0229b228, 0xe0 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 *func_ov123_02299d9c(void *self);
extern void func_0200255c(void *d, void *s, int a, int b);

void func_ov123_0229b228(char *self)
{
    u32 a;
    u32 word;
    int sh;
    int j;
    int t;
    int i;
    int m;
    u32 b;
    u32 val;
    u32 *q;
    u32 *src;
    u32 *base;
    u32 *p;
    u32 *dst;
    // ENDDECLS

    src = func_ov123_02299d9c(self);
    dst = (u32 *) (self + 0xe30);
    for (i = 0; i < 0x20; i++) {
        base = dst;
        for (j = 0; j < 4; j++) {
            sh = 0;
            p = base;
            for (m = 0; m < 4; m++) {
                word = *src;
                a = (u8) ((word >> sh) & 0xf);
                b = (u8) ((word >> (sh + 4)) & 0xf);
                sh = sh + 8;
                val = (b << 0x1c) | (b << 0x18) | (b << 0x14) | (b << 0x10) | (a << 0xc) | (a << 8) | (a << 4) | a;
                q = p;
                for (t = 0; t < 4; t++) {
                    *q = val;
                    q = q + 0x10;
                }
                p = p + 1;
            }
            src = src + 1;
            base = base + 4;
        }
        dst = dst + 0x40;
    }
    func_0200255c(self + 0xe30, self + 0x3030, 0x10, 0x10);
}
