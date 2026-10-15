/* func_ov004_02225cd4 @ 0x02225cd4, 0x10c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02013c2c(void *argument0);
extern void func_0201489c(void *object);
extern int func_020169a8(int argument0);
extern void *func_02019eb0(void *argument0);
extern void *func_0201a430(void *argument0);
extern void func_0201a794(void *object);
extern void *func_0201a7ec(void *argument0);
extern void func_0201adec(char *argument0);
extern void func_0201af14(void *argument0);
extern int func_0201b324(int *argument0);
extern void func_0201b370(unsigned short *argument0);
extern void func_0201b394(int *argument0);
extern void *func_02032c64(void *argument0);
extern void *func_0203f130(void *argument0);
extern void *func_0205467c(void *argument0);
extern void *func_02082f60(void *argument0);
extern void *func_02089c88(void *argument0);
extern void *func_020edf70(int argument0);
extern void *func_020f55cc(void *argument0);
extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_ov004_02254a38;

void *func_ov004_02225cd4(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_020edf70(0x65c);
    if (self != 0) {
        func_0203f130(self);
        *(void **) (self) = &data_020d8c64;
        *(u16 *) (self + 0xea) = 0xfff1;
        func_0205467c(self + 0xec);
        func_0201b394((int *) (self + 0x2a0));
        func_0201a430(self + 0x2ac);
        func_020169a8((int) (self + 0x334));
        func_0201b324((int *) (self + 0x350));
        func_0201af14(self + 0x3a8);
        func_0201b370((unsigned short *) (self + 0x3aa));
        func_0201adec(self + 0x3b0);
        func_0201a7ec(self + 0x418);
        func_0201a794(self + 0x420);
        func_02032c64(self + 0x49c);
        func_02089c88(self + 0x4cc);
        func_020f55cc(self + 0x514);
        func_02013c2c(self + 0x558);
        func_02019eb0(self + 0x564);
        func_0201489c(self + 0x618);
        *(void **) (self) = &data_020da088;
        func_02082f60(self + 0x640);
        *(void **) (self) = &data_ov004_02254a38;
    }
    return self;
}
