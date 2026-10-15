/* func_ov004_0223cf80 @ 0x0223cf80, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223d028(void);
extern int func_ov004_0223cfc4(void *);
extern void *func_ov004_0223cfc8(void *object);
extern void func_02004404(void *, void *);

void func_ov004_0223cf80(char *self)
{
    void *p;
    if (*(u8 *) (self + 0x1c) == 0) {
        p = func_ov004_0223d028();
        if (p != 0) {
            if (func_ov004_0223cfc4(p) != 0) {
                func_02004404(self, func_ov004_0223cfc8(p));
                *(u8 *) (self + 0x1c) = 1;
            }
        }
    }
}
