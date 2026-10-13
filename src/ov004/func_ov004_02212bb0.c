/* func_ov004_02212bb0 @ 0x02212bb0, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220e5c8(void *self);
extern void func_ov004_0223cf40(void *p, int a, void *q);
extern int func_ov004_0220ffbc(void *self);
extern int func_02056f28(void *p, int a);
extern void func_ov004_0223cf18(void *p, int a);
extern int func_ov004_0220d2a8(void *p);
extern void func_0205265c(void *self, int a, int b, int c);

void func_ov004_02212bb0(char *self)
{
    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0223cf40(self + 0x798, 0x42a, self + 0x7b8);
    }
    func_ov004_0220ffbc(self);
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
    if (func_ov004_0220d2a8(self + 0x740) != 0) {
        func_0205265c(self, 3, 0xff, 1);
    }
}
