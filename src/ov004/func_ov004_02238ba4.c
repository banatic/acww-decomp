/* func_ov004_02238ba4 @ 0x02238ba4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_022358c0(char *argument0, int argument1);
extern int func_ov004_02236418(void *argument0);
extern void func_ov004_02238a58(unsigned char *argument0, int argument1, int argument2);
extern void func_ov004_02239700(char *argument0);

void func_ov004_02238ba4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02238a58((unsigned char *) (self), (int) (-0x2), (int) (0x24));
    if (*(u8 *) (self + 0x1ee) != 0x2 && *(u8 *) (self + 0x1ee) != 0x6) {
        func_ov004_02239700(self);
    }
    func_ov004_022358c0(self, 0x333);
    *(void **) (self + 0x158) = (char *) *(int *) (self + 0x158) + 0x1;
    func_ov004_02236418(self);
}
