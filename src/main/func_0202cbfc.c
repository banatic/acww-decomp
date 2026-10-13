/* func_0202cbfc @ 0x0202cbfc, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204fafc(u8);
extern void *func_0204fc3c(int, int);
extern int func_020644cc(int);
extern int func_0202ccc0(u16 *, int *, int *, int, void *, u8, u8);

int func_0202cbfc(u16 *a, int lo, int hi, int d4, u8 p5, u8 p6, u8 p7)
{
    void *tbl;
    int o1;
    int o2;
    u8 mask;
    int cnt;
    int i;
    int k;

    tbl = func_0204fc3c(d4, func_0204fafc(p5));
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
                        if (func_0202ccc0(a, &o1, &o2, i, tbl, p6, p7) != 0) {
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
