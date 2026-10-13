/* func_ov003_02220294 @ 0x02220294, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O2,s
 */

#include "types.h"

extern void func_0204f818(int *x, int *z, int p);
extern u16 *func_0204f5e0(void *m, int bx, int bz, int ox, int oz, int f);
extern int func_ov003_02220174(unsigned int h);
extern void *data_021c80bc;

int func_ov003_02220294(int p)
{
    void *m = data_021c80bc;
    int x, z, j, i;

    if (m != 0) {
        func_0204f818(&x, &z, p);
        for (j = z; j >= z - 5; j--) {
            for (i = x - 3; i <= x + 3; i++) {
                // bx/bz are kept in locals rather than written inline.
                int bx = i >> 4;
                int bz = j >> 4;
                u16 *e = func_0204f5e0(m, bx, bz, i - bx * 16, j - bz * 16, 0);
                if (e != 0) {
                    int ok = 0;
                    unsigned int h = *e;
                    if (h >= 0x5000 && h <= 0x5021) {
                        ok = 1;
                    }
                    if (ok) {
                        int r = func_ov003_02220174(h);
                        if (r) {
                            return r;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
