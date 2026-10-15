/* func_ov004_0223a458 @ 0x0223a458, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a5e4(char *argument0);
extern void *data_ov004_02255ea4;

void *func_ov004_0223a458(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4(self);
    *(void **) (self) = &data_ov004_02255ea4;
    *(u8 *) (self + 0x1ee) = 0x2;
    *(u8 *) (self + 0x1fe) = 0x2;
    *(u16 *) (self + 0x200) = 0x3;
    *(u8 *) (self + 0x1fc) = 0x0;
    *(void **) (self + 0x21c) = 0x0;
    *(u16 *) (self + 0x220) = 0x0;
    *(u8 *) (self + 0x1ca) = 0x0;
    *(int *) (self + 0x224) = 0x28;
    *(u8 *) (self + 0x22e) = 0x0;
    *(int *) (self + 0x1cc) = 0x3000;
    *(int *) (self + 0x228) = 0x1000;
    *(u8 *) (self + 0x1ef) = 0x0;
    *(u8 *) (self + 0x254) = 0x0;
    return self;
}
