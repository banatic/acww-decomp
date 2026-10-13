/* func_ov004_0221d784 @ 0x0221d784, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_02257a18;
extern int func_ov004_0221c844(void *p, int a);
extern int func_02019c90(void *p, int a, int b, int c);
extern u16 data_020c80f8;

int func_ov004_0221d784(char *self)
{
    char *g = data_ov004_02257a18;
    int r;
    if (g != 0 && *(unsigned int *) (g + 0x898) <= 1) {
        r = func_ov004_0221c844(g, 2);
    } else {
        r = 0;
    }
    if (r != 0) {
        if (func_02019c90(self + 0x564, 1, 3, data_020c80f8) != 0) {
            *(u8 *) (self + 0xa4c) = 0x1e;
            return 1;
        }
    }
    return 0;
}
