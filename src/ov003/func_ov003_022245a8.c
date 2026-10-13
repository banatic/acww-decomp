/* func_ov003_022245a8 @ 0x022245a8, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xa];
    u16 unk_0A;
} UnkStruct_022245a8;

extern int func_02045c60(void *a0, int *pair, int k);
extern UnkStruct_022245a8 *func_02045bac(int r);

int func_ov003_022245a8(void *a0, int *pv)
{
    volatile u16 t;
    int pair[2];
    unsigned int d, c, b, a;
    u16 lo, hi;
    int ok = 0;
    int r;

    pair[0] = pv[0];
    pair[1] = pv[1];
    r = func_02045c60(a0, pair, 0);
    if (r >= 0) {
        t = 0xfff1;
        t = func_02045bac(r)->unk_0A;
        d = 1;
        c = 1;
        b = 1;
        a = 0;
        lo = t;
        hi = t;
        if (hi >= 0x2b && lo <= 0x2e) {
            a = 1;
        }
        if (a == 0) {
            if (!(lo >= 0xff && lo <= 0x102)) {
                b = 0;
            }
        }
        if (b == 0) {
            if (!(lo >= 0x62 && lo <= 0x65)) {
                c = 0;
            }
        }
        if (c == 0) {
            if (!(lo >= 0xd0 && lo <= 0xd3)) {
                d = 0;
            }
        }
        if (d != 0) {
            ok = 1;
        }
    }
    return ok;
}
