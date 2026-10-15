/* func_ov122_0229fe28 @ 0x0229fe28, 0x7c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned char func_ov095_0229bb34(char *a, char *b, int c, int d, u8 e, u8 *f);
extern int func_0206e224(char *a);

u8 func_ov122_0229fe28(int a, int b, u8 *out)
{
    u8 arg5;
    u8 *p;
    u8 local;
    u8 bval;
    int v;
    int threshold;

    arg5 = (u8) (b - 0x30);
    p = &local;
    func_ov095_0229bb34((char *) a + 0xc0, (char *) a + 0x41e0, 0x28, 0xa0, arg5, p);

    bval = *(u8 *) (*(char **) ((char *) a + 0xbc) + 0xf8);
    v = func_0206e224((char *) a + 0x3ce8) + bval;
    threshold = (bval + v) >> 1;

    if (local < threshold) {
        *out = 0;
        if ((int) local > (int) bval) {
            local = bval;
        }
    } else {
        *out = 1;
        if (local < v) {
            local = 0;
        } else {
            local = (u8) (local - v);
        }
    }

    return local;
}
