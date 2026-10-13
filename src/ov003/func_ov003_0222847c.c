/* func_ov003_0222847c @ 0x0222847c, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_0225f4dc[];
int func_ov003_022298c4(void *p, u8 i);
void func_020044a0(void *p);

void func_ov003_0222847c(void)
{
    char *p = data_ov003_0225f4dc;
    int i;
    for (i = 0; i < 4; i++) {
        func_ov003_022298c4(p, (u8) i);
        func_020044a0(p);
        p += 0xa4;
    }
}
