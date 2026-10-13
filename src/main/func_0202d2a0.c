/* func_0202d2a0 @ 0x0202d2a0, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0202d34c(int, const u8 *, int, int, int);
extern int func_020644cc(int);
extern int func_0209a488(u8);
extern int func_02061550(u8);
extern int func_0202d3b0(int, int, int);

int func_0202d2a0(u16 *out1, int *out2, int key, const u8 *p, int n, int a3, int a4)
{
    int result;
    int k;
    int c;
    int prev;
    int i;
    int t;
    int d;
    u16 v;

    result = 0;
    if (n > 0 && p != 0) {
        c = func_0202d34c(key, p, n, a3, a4);
        if (c > 0) {
            k = func_020644cc(c);
            prev = 0;
            for (i = 0; i < n; i++) {
                d = p[1] - prev;
                if (d > 0) {
                    if (key == func_0209a488((u8) d)) {
                        t = func_02061550(p[0]);
                        if (func_0202d3b0(t, a3, a4) == 0) {
                            if (k == 0) {
                                if (p[0] < 0x38) {
                                    v = (u16) (p[0] + 0x12b0);
                                } else {
                                    v = 0x12b0;
                                }
                                *out1 = v;
                                *out2 = t;
                                result = 1;
                                break;
                            }
                            k--;
                        }
                    }
                }
                prev = p[1];
                p += 2;
            }
        }
    }
    return result;
}
