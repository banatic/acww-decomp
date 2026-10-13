/* func_ov003_02228618 @ 0x02228618, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern char data_ov003_0225f4dc[];
extern char data_ov003_0225f35c[];
extern char data_ov003_0225f0b4[];

extern int func_02073d90(void *h);
extern void func_ov003_0222924c(void *p);
extern void func_ov003_02229ca8(void *rec, u8 i);
extern void func_ov003_0222c130(void *a, void *b);

void func_ov003_02228618(void *p)
{

    int i;
    char *a;
    char *b;

    if (func_02073d90(data_020ccf94)) {
        func_ov003_0222924c(p);
    }
    a = data_ov003_0225f4dc;
    b = data_ov003_0225f35c;
    for (i = 0; i < 4; i++) {
        func_ov003_02229ca8(a, (u8) i);
        a += 0xa4;
        func_ov003_0222c130(data_ov003_0225f0b4, b);
        b += 0x60;
    }
}
