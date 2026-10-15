/* func_ov003_0222d388 @ 0x0222d388, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020644cc(int k);
extern int func_020ba4e4(void);
extern int func_ov003_0222d40c(int c);
extern int func_ov003_0222d248(signed char c, int h);
extern u8 *data_020dded8[];

int func_ov003_0222d388(int a, int b, u8 *out)
{
    int h;
    u8 lvl;
    u8 *p;
    u8 *e;
    u8 i;
    u8 n;
    u8 c;

    lvl = func_020644cc(0x64);
    e = data_020dded8[a];
    if (e == 0) {
        return 0;
    }
    b = b * 8;
    n = *(e + b + 4);
    h = func_020ba4e4();
    for (i = 0; i < n; i++) {
        p = *(u8 **) ((int) e + b);
        c = *(p + i * 2);
        if (*(p + i * 2 + 1) <= lvl) {
            continue;
        }
        if (c != 0x30 && func_ov003_0222d40c(c) != 0 && func_ov003_0222d248((signed char) c, h) != 4) {
            *out = c;
            return 1;
        }
        return 0;
    }
    return 0;
}
