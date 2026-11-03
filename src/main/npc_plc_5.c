/* npc_plc_5: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c3ee8 @ 0x020c3ee8, 0x118 bytes, Thumb
 * func_020c3e98 @ 0x020c3e98, 0x50 bytes, Thumb
 * func_020c3e6c @ 0x020c3e6c, 0x2c bytes, Thumb
 * func_020c3e54 @ 0x020c3e54, 0x18 bytes, Thumb
 * func_020c3e48 @ 0x020c3e48, 0xc bytes, Thumb
 * func_020c3e3c @ 0x020c3e3c, 0xc bytes, Thumb
 */

#include "types.h"

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_020e877c;
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
extern void *func_020c3c7c(void *);
extern int func_0202edc8(void *p);
extern void func_0201c400(void *a, void *b);
extern void func_0201c280(void *a, void *b);
extern void func_020c3c20(void *obj, int val);
extern int func_0202ec58(void *);
extern void func_020c3dac(void *param1, int param2);
extern int func_0202ec14(void *);
extern unsigned int data_020d3164[];

void *func_020c3ee8(void)
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
        *(void **) p = &data_020e877c;
        func_020c3c7c(p + 0x658);
    }
    return p;
}

int func_020c3e98(void *self)
{
    unsigned short local = 0xfff1;

    if (func_0202edc8(self) == 0) {
        return 0;
    }
    local = 0xd000;
    func_0201c400(self, &local);
    func_0201c280(self, (char *) self + 0x658);
    func_020c3c20((char *) self + 0x658, (int) self);
    return 1;
}

int func_020c3e6c(void *param0)
{
    int result;
    void *r4 = param0;
    int r0;

    if (func_0202ec58(param0) == 0) {
        return 0;
    }

    func_020c3dac(r4, 0);
    r0 = *(short *) ((char *) r4 + 0x8e);
    *(short *) ((char *) r4 + 0x710) = r0;
    return 1;
}

int func_020c3e54(void *argument0)
{
    if (func_0202ec14((void *) argument0) != 0) {
        return 1;
    } else {
        return 0;
    }
}

unsigned int func_020c3e48(void)
{
    return data_020d3164[1];
}

unsigned int func_020c3e3c(void)
{
    return (*(unsigned int *) data_020d3164);
}
