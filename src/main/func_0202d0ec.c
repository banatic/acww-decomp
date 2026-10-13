/* func_0202d0ec @ 0x0202d0ec, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020617d8(int);
extern int func_020644cc(int);
extern int func_0202d1cc(u16 *, int *, int *, int, void *, int, int, u8, u8);

int func_0202d0ec(u16 *a, int lo, int hi, u8 d, u8 e5, u8 f)
{
    void *tbl;
    int o1;
    int o2;
    u8 mask;
    int cnt;
    int i;
    int k;

    tbl = func_020617d8(f - 1);
    if (tbl != 0) {
        mask = 0;
        cnt = hi - lo + 1;
        o1 = 0;
        o2 = 0;
        while (lo <= hi) {
            mask |= 1 << lo;
            lo++;
        }
        while (cnt > 0) {
            k = func_020644cc(cnt);
            for (i = 0; i < 5; i++) {
                if ((mask >> i) & 1) {
                    if (k == 0) {
                        if (func_0202d1cc(a, &o1, &o2, i, tbl, 0, 0, d, e5) != 0) {
                            return 1;
                        }
                        mask &= ~(1 << i);
                        break;
                    }
                    k--;
                }
            }
            cnt--;
        }
    }
    return 0;
}
