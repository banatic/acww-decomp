/* room_shell_members: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02232314 @ 0x02232314, 0x18 bytes, Thumb
 * func_ov004_022322fc @ 0x022322fc, 0x18 bytes, Thumb
 * func_ov004_022322ec @ 0x022322ec, 0x10 bytes, Thumb
 * func_ov004_0223228c @ 0x0223228c, 0x60 bytes, Thumb
 * func_ov004_02232270 @ 0x02232270, 0x1c bytes, Thumb
 * func_ov004_0223226c @ 0x0223226c, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 unk_00;
} UnkStruct_0223228c;

extern int func_02032180(void *arg0);
extern int func_020b65c4(void);
extern void *func_020b7ee8(void *);
extern int func_020b7ed8(int);
extern void *func_020b6590(void);
extern void *func_020b7d3c(void *, void *, int *, int, int, int, int);
extern int func_020b7d6c(int, void *);

int func_ov004_02232314(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020b65c4();
    if (v1 == 0xa) {
        return func_02032180(self);
    }
    return v1;
}

void *func_ov004_022322fc(char *self)
{
    // DECLS
    // ENDDECLS
    func_020b7ee8(self);
    *(u8 *) (self + 0x20) = 0x0;
    return self;
}

int func_ov004_022322ec(int arg)
{
    func_020b7ed8(arg);
    return arg;
}

void func_ov004_0223228c(char *self)
{
    int a[3];
    if (func_020b65c4() == 0x22) {
        ((UnkStruct_0223228c *) (self + 0x20))->unk_00 = 1;
    }
    if (((UnkStruct_0223228c *) (self + 0x20))->unk_00 != 0) {
        a[0] = 0x108f6;
        a[1] = 0;
        a[2] = 0x1351e;
        func_020b7d3c(func_020b6590(), self, a, 0xf33, 0x6000, 0x16, 0xff);
    }
}

int func_ov004_02232270(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x20) != 0x0) {
        return func_020b7d6c((int) func_020b6590(), self);
    }
    return *(u8 *) (self + 0x20);
}

void func_ov004_0223226c(void *object) {}
