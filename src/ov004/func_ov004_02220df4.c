/* func_ov004_02220df4 @ 0x02220df4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int gt2GetIncomingBufferSize(void *p);
extern int func_0201c314(void *self, int h);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov004_02220df4(char *self)
{
    int h;
    int n;
    h = gt2GetIncomingBufferSize(self + 0x918);
    n = 0;
    if (h != 0) {
        n = func_0201c314(self, h);
    }
    *(int *) (self + 0xacc) = 0;
    if (*(u8 *) (self + 0xac8) != 0) {
        func_020147fc(self + 0x618, 0, n, 0);
    }
    return 1;
}
