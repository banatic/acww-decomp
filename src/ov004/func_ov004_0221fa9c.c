/* func_ov004_0221fa9c @ 0x0221fa9c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int gt2GetIncomingBufferSize(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);

int func_ov004_0221fa9c(u8 *self)
{
    int n;
    int v;

    n = gt2GetIncomingBufferSize(self + 0x8a8);
    v = 0;
    if (n != 0) {
        v = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, v, 1);
    return 1;
}
