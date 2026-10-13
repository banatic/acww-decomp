/* func_ov003_0222b960 @ 0x0222b960, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_0222be78(void *p, int a, int b);
extern void func_ov003_022277fc(void *self, int a);

void func_ov003_0222b960(void *self)
{
    func_ov003_0222be78((char *) self + 0x120, 0x19a, *(short *) ((char *) self + 0x138));
    func_ov003_022277fc(self, 0x20);
    *(u16 *) ((char *) self + 0x140) -= 1;
    if (*(u16 *) ((char *) self + 0x140) == 0) {
        *(int *) ((char *) self + 0x13c) = 0;
        *(u8 *) ((char *) self + 0x200) = 3;
    }
}
