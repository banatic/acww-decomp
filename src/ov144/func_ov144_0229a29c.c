/* func_ov144_0229a29c @ 0x0229a29c, 0x8c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_02060b70(void);
extern int func_02060a34(u16 id);

void func_ov144_0229a29c(u8 *self)
{
    u16 *p;
    u16 v;
    int limit;
    int k;
    int n;
    u16 id;
    unsigned int ok;

    id = 0x1323;
    n = 0;
    *(short *) (self + 0xbc) = -1;
    p = func_02060b70();
    if (*p != 0xfff1) {
        p = func_02060b70();
        ok = 0;
        v = *p;
        if (v >= 0x1323 && v <= 0x1368) {
            ok = 1;
        }
        if (ok != 0) {
            limit = v - 0x1323;
        } else {
            limit = -1;
        }
        for (k = 0; k < 0x46; k++) {
            if (func_02060a34(id) != 0) {
                if (k == limit) {
                    *(u16 *) (self + 0xbc) = (u16) n;
                    k = 0x46;
                }
                n++;
            }
            id = (u16) (id + 1);
        }
    }
    *(u16 *) (self + 0xba) = *(short *) (self + 0xbc);
}
