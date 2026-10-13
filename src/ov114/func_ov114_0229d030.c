/* func_ov114_0229d030 @ 0x0229d030, 0x58 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020a7bf4(u8 *p, int n);

int func_ov114_0229d030(u8 *base)
{
    int i = 0;
    int j = i;
    while (i < 4) {
        int a = func_020a7bf4(base + 0x81a, j);
        int b = func_020a7bf4(base + 0x81a, j + 1);
        int c = func_020a7bf4(base + 0x81a, j + 2);
        j += 3;
        if (a == 0 && b == 0 && c == 0) {
            return (u8) i;
        }
        i++;
    }
    return 4;
}
