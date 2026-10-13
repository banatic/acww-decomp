/* func_ov003_02229dc0 @ 0x02229dc0, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004290(void *p, int k);
extern u8 func_ov003_0222793c(int a, int b);
extern int func_ov003_02228018(void *p);

void func_ov003_02229dc0(u8 *s, char *p)
{
    if (s[1] != 0) {
        s[1] -= 1;
        func_02004290(p + 0x40, 0x82f);
    } else {
        s[2] = func_ov003_0222793c(0x14, 0x50);
        s[3] = 1;
    }
    if (func_ov003_02228018(0)) {
        s[2] = func_ov003_0222793c(0x14, 0x28);
        s[3] = 1;
        s[1] = 0;
        s[0] += 1;
        if (s[0] >= 0xc8) {
            s[0] = 0xc8;
        }
    } else if (s[0] != 0) {
        s[0] -= 1;
    }
}
