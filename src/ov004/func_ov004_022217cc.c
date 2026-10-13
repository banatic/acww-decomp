/* func_ov004_022217cc @ 0x022217cc, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0202e364(void *);
extern void func_0201c280(void *, void *);
extern void func_ov004_02220cdc(void *, void *);

int func_ov004_022217cc(u8 *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x918);
    func_ov004_02220cdc(self + 0x918, self);
    return 1;
}
