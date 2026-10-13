/* func_ov004_02212ab8 @ 0x02212ab8, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_0225130c.h"

#include "types.h"

extern "C" {
int func_ov004_0220e5c8(void *self);
void func_ov004_0223cf40(void *p, int a, void *q);
void func_ov004_0220d280(void *p, int a, int b);
int func_02056f28(void *p, int a);
void func_ov004_0223cf18(void *p, int a);
int func_ov004_0220ffbc(void *self);
}

extern "C" void func_ov004_02212ab8(Obj_ov004_0225130c *selfp)
{
    char *self = (char *) selfp;

    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0223cf40(self + 0x798, 0x42a, self + 0x7b8);
    }
    func_ov004_0220d280(self + 0x740, 0, 0);
    if (func_ov004_0220e5c8(self) == 0) {
        if (func_02056f28(self + 0x5d4, 0) != 0) {
            func_ov004_0223cf18(self + 0x798, 1);
        } else if (func_02056f28(self + 0x5d4, 0x14) != 0) {
            if ((*(u8 *) (self + 0x845) & 1) != 0) {
                func_ov004_0223cf18(self + 0x798, 2);
            } else {
                func_ov004_0223cf18(self + 0x798, 1);
            }
            *(u8 *) (self + 0x845) = (u8) (*(u8 *) (self + 0x845) + 1);
        }
    }
    if (func_ov004_0220ffbc(self) != 0) {
        selfp->vfunc_70(4, 0xff);
    }
}
