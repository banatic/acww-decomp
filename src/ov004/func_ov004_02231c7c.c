/* func_ov004_02231c7c @ 0x02231c7c, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_021c80bc;
extern void func_ov004_0221ad0c(int *, int, int, int);

void func_ov004_02231c7c(void *receiver)
{
    int v[3];
    char *o, *e;
    unsigned i;
    int a, b, c;
    char *q = data_021c80bc;
    char *r;
    if (*(char **) (q + 4) > (char *) 0 && *(char **) (q + 8) > (char *) 0 && *(char **) q != 0) {
        r = *(char **) q;
    } else {
        r = 0;
    }
    o = *(char **) (r + 0x20);
    if (o == 0) {
        return;
    }
    e = *(char **) (o + 0x28);
    if (e == 0) {
        return;
    }
    if (*(unsigned *) (o + 0x2c) == 0) {
        return;
    }
    for (i = 0; i < *(unsigned *) (o + 0x2c); i++) {
        c = (*(s16 *) (e + 4) << 12) >> 4;
        b = (*(s16 *) (e + 2) << 12) >> 4;
        a = (*(s16 *) (e + 0) << 12) >> 4;
        v[0] = a;
        v[1] = b;
        v[2] = c;
        func_ov004_0221ad0c(v, (*(s16 *) (e + 6) << 12) >> 4, (*(u8 *) (e + 8) << 30) >> 16, *(u8 *) (e + 9));
        e += 0xa;
    }
}
