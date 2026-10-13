/* func_ov004_0223cfec @ 0x0223cfec, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0223cfc4(char *self);
extern int func_0200431c(void);
extern void func_02004414(char *self);
void func_ov004_0223cfec(char *self)
{
    if (func_ov004_0223cfc4(self) == 0 && func_0200431c() != 0) {
        func_02004414(self);
        *(u8 *) (self + 0x10) = 1;
    }
}
