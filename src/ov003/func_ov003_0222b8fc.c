/* func_ov003_0222b8fc @ 0x0222b8fc, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_0222be78(void *p, int a, int b);
extern void func_ov003_022277fc(void *self, int a);

void func_ov003_0222b8fc(void *self)
{
    int d = 0x19a - (*(int *) ((char *) self + 0x13c) << 3);
    func_ov003_0222be78((char *) self + 0x120, d, *(short *) ((char *) self + 0x138));
    if (*(int *) ((char *) self + 0x13c) >= 0xa) {
        func_ov003_022277fc(self, 3);
    } else {
        func_ov003_022277fc(self, 0x10);
    }
    if (d <= 0) {
        *(int *) ((char *) self + 0x13c) = 0;
        *(u8 *) ((char *) self + 0x200) = 4;
    }
}
