/* func_ov004_0221ff40 @ 0x0221ff40, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0202e364(void *);
extern void func_0201c280(void *, void *);
extern void func_ov004_0221f800(void *, void *);

int func_ov004_0221ff40(u8 *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x8a8);
    func_ov004_0221f800(self + 0x8a8, self);
    return 1;
}
