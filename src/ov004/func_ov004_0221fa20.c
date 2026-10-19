/* func_ov004_0221fa20 @ 0x0221fa20, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);

int func_ov004_0221fa20(u8 *self)
{
    int n;
    int v;

    n = func_02016104(self + 0x8a8);
    v = 0;
    if (n != 0) {
        v = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, v, 0);
    return 1;
}
