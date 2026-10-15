/* func_ov004_02228078 @ 0x02228078, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056f28(void *, int);
extern int func_020b65c4(void);
extern int func_0200f328(void *, int);
extern void func_02010f5c(void *);
void func_ov004_02228078(u8 *self)
{
    if (func_02056f28(self + 0x2d0, 8) != 0 && func_020b65c4() == 9) {
        func_0200f328(self, 0x63);
    }
    func_02010f5c(self);
}
