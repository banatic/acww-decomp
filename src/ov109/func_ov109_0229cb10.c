/* func_ov109_0229cb10 @ 0x0229cb10, 0x8c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov109_0229cab0(u8 *self, int i);
extern int func_ov109_0229ca4c(u8 *self, int i);
extern u16 func_ov109_0229ca7c(u8 *self, int i);
extern int func_ov109_0229cc98(u8 *self, int i);
extern void func_ov094_0229a888(u8 *p, int v);

void func_ov109_0229cb10(u8 *self)
{
    volatile u16 h;
    unsigned int hit;
    unsigned int ok;
    u16 v0, v1;
    unsigned char i;

    h = 0xfff1;
    for (i = 0; i <= 0xe; i++) {
        hit = 0;
        if (func_ov109_0229cab0(self, i) == 0) {
            if (func_ov109_0229ca4c(self, i) != 0) {
                hit = 1;
            } else {
                h = func_ov109_0229ca7c(self, i);
                ok = 0;
                v0 = h;
                v1 = h;
                if (v1 >= 0x1323 && v0 <= 0x1368) {
                    ok = 1;
                }
                if (ok == 0) {
                    hit = 1;
                }
            }
        }
        if (hit != 0) {
            func_ov094_0229a888(self + 0xcc, func_ov109_0229cc98(self, i));
        }
    }
}
