/* func_020c3950 @ 0x020c3950, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_020e7ea4;

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_020c33a4(void *);

void *func_020c3950(void)
{
    u8 *p;

    p = (u8 *) func_020edf70(0x714);
    if (p) {
        func_0203f130(p);
        *(void **) p = &data_020d8c64;
        *(u16 *) (p + 0xea) = 0xfff1;
        func_0205467c(p + 0xec);
        func_0201b394(p + 0x2a0);
        func_0201a430(p + 0x2ac);
        func_020169a8(p + 0x334);
        func_0201b324(p + 0x350);
        func_0201af14(p + 0x3a8);
        func_0201b370(p + 0x3aa);
        func_0201adec(p + 0x3b0);
        func_0201a7ec(p + 0x418);
        func_0201a794(p + 0x420);
        func_02032c64(p + 0x49c);
        func_02089c88(p + 0x4cc);
        func_020f55cc(p + 0x514);
        func_02013c2c(p + 0x558);
        func_02019eb0(p + 0x564);
        func_0201489c(p + 0x618);
        *(void **) p = &data_020da088;
        func_02082f60(p + 0x640);
        *(void **) p = &data_020e7ea4;
        func_020c33a4(p + 0x658);
    }
    return p;
}
