/* func_ov004_0220d318 @ 0x0220d318, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220e5c8(void *b);
extern int func_ov004_0220e758(void *b, int *x, int *y, int c, int d);
extern int func_020b65c4(void);
extern int func_02052f14(int x, int y, int c, int d);
extern void func_ov004_0220d280(void *p, int a, int b);

void func_ov004_0220d318(void *a, char *b)
{
    int r;
    int x, y;

    r = 0;
    if (*(int *) (b + 0x76c) == 1 || func_ov004_0220e5c8(b) != 0) {
        if (*(u8 *) (b + 0x78d) == 0) {
            r = 1;
        } else {
            r = 0;
        }
    } else if (func_ov004_0220e758(b, &x, &y, 0, 0) != 0) {
        r = func_02052f14(x, y, *(u8 *) (b + 0x288), func_020b65c4());
    }
    func_ov004_0220d280(a, r, 0);
}
