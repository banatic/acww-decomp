/* func_ov003_02229e2c @ 0x02229e2c, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02095794(int k);
extern int func_020ea990(void *p, void *q);
extern int func_ov003_02228018(void *p);
extern u8 func_ov003_0222793c(int a, int b);

void func_ov003_02229e2c(u8 *s, char *b)
{
    void *p;
    if (s[2] != 0) {
        s[2] -= 1;
    }
    p = func_02095794(0);
    if (p != 0 && func_020ea990(p, b + 0x120) >= 0x8000) {
        s[3] = 0;
    } else if (func_ov003_02228018(0)) {
        s[0] += 1;
        if (s[0] >= 0xc8) {
            s[0] = 0xc8;
        }
    } else {
        if (s[0] != 0) {
            s[0] -= 1;
        }
        if (s[0] <= 0x96 && s[2] == 0) {
            s[1] = func_ov003_0222793c(0x3c, 0x8c);
            s[3] = 2;
        }
    }
}
