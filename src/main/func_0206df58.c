/* func_0206df58 @ 0x0206df58, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0206db5c(char *param0, unsigned char param1, unsigned char param2, int param3);

void func_0206df58(void *a, unsigned int b, unsigned int c, int d)
{
    int i;
    int j;
    unsigned int s;
    int t;
    int delta;

    j = 0;
    i = j;
    while (i < 4) {
        delta = *(int *) ((char *) a + (i + 1) * 4 + 0x308) - *(int *) ((char *) a + i * 4 + 0x308);
        if (delta == 0) {
            break;
        }
        if (b >= j && b < (t = j + delta)) {
            if (t > b + c) {
                s = c;
            } else {
                s = delta - (b - j);
            }
            func_0206db5c((char *) a + 0xe8 + i * 0x74, (u8) (b - j), (u8) s, d);
            b = (u8) t;
            c -= s;
            if (c == 0) {
                break;
            }
        }
        j += delta;
        i++;
    }
}
