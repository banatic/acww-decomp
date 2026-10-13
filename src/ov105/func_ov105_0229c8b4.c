/* func_ov105_0229c8b4 @ 0x0229c8b4, 0xf8 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern void func_ov105_0229c330(u8 *, int);
extern int func_ov105_0229d75c(u8 *, unsigned char);
extern int func_ov105_0229c340(u8 *, int);
extern void func_ov002_0220a314(void *);

void func_ov105_0229c8b4(u8 *self, void *p, int arg2)
{
    int r4;
    int r6;

    r4 = (int) self[0x2ba] - 0x24;
    r6 = 0;
    while (r4 >= 5) {
        r6++;
        r4 -= 5;
    }

    if (func_ov002_022088ac(p) != 0) {
        if (r4 > 0) {
            self[0x2ba]--;
            r4--;
            goto common;
        } else {
            self[0x2ba] = r6 * 2 + 0x1b;
            func_ov105_0229c330(self, 0x10);
            return;
        }
    } else {
        if (func_ov002_0220889c(p) != 0) {
            if (r4 < 4) {
                self[0x2ba]++;
                r4++;
                goto common;
            } else {
                self[0x2ba] = r6 * 2 + 0x1a;
                return;
            }
        } else {
            goto common;
        }
    }

common:
    if (func_ov105_0229d75c(self, self[0x2ba]) != 0) {
        if (func_ov105_0229c340(self, 0x30) == 0) {
            if (func_ov002_022088cc(p) != 0) {
                if (r6 > 0) {
                    self[0x2ba] -= 5;
                } else {
                    if (r4 < 2) {
                        r4 += 0x3e;
                        self[0x2ba] = (u8) r4;
                    } else {
                        self[0x2ba] = 0x3f;
                    }
                }
            } else {
                if (func_ov002_022088bc(p) != 0) {
                    if (r6 < 4) {
                        self[0x2ba] += 5;
                    } else {
                        if (arg2 == 0) {
                            self[0x2ba] = 0x3d;
                            func_ov002_0220a314(self + 0x24a4);
                        }
                    }
                }
            }
        }
    }
    return;
}
