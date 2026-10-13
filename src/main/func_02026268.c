/* func_02026268 @ 0x02026268, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020535f0(u16 *w);

int func_02026268(u16 *p, int comp)
{
    unsigned int ok = 0;
    int r5;
    unsigned int i;
    int j;
    int r;
    u16 w;

    if (p[0] >= 0x450c && p[0] <= 0x45db) {
        ok = 1;
    }
    if (ok > 0) {
        w = 0xfff1;
        r5 = (p[0] >= 0x450c && p[0] <= 0x45db) ? (int) (p[0] - 0x450c) >> 2 : -1;
        for (i = 0; i < 0x34; i++) {
            w = (i < 0x34) ? 0x450c + i * 4 : 0x450c;
            r = func_020535f0(&w);
            if (comp == r) {
                for (j = 0; j < 3; j++) {
                    if (r5 == j + i) {
                        return j;
                    }
                }
                break;
            }
        }
    }
    return -1;
}
