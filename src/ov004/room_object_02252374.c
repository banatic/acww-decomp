/* room_object_02252374: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213e24 @ 0x02213e24, 0x50 bytes, Thumb
 * func_ov004_02213e10 @ 0x02213e10, 0x14 bytes, Thumb
 * func_ov004_02213d84 @ 0x02213d84, 0x8c bytes, Thumb
 * func_ov004_02213d70 @ 0x02213d70, 0x14 bytes, Thumb
 */

#include "types.h"

extern unsigned int func_0203cfc8(unsigned int *object);
extern int func_020b9d3c(void *argument0, void *argument1, int argument2, void *argument3, int argument4, int argument5);
extern void func_ov004_0220d280(unsigned char *argument0, unsigned char argument1, int argument2);
extern void *data_ov004_022531c8;
extern void *func_ov004_0220e220(void *p);
extern void *func_ov004_0220d9bc(void *p);
extern int func_02057a40(void *p, void *d);
extern int func_020579b8(void *p, const char *name);
extern int data_ov004_022531d4;

int func_ov004_02213e24(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_ov004_0220d280((unsigned char *) (self + 0x740), (unsigned char) (0x1), (int) (0x0));
    v2 = *(int *) (self + 0x594);
    func_020b9d3c((void *) (self + 0x848), (void *) (v2), (int) (&data_ov004_022531c8),
                  (void *) (func_0203cfc8(*(unsigned int **) (self + 0x844))), (int) (0x0), (int) (0x0));
    return 0x1;
}

void func_ov004_02213e10(char *self)
{
    func_ov004_0220d280((unsigned char *) self + 0x740, 1, 0);
}

int func_ov004_02213d84(char *self)
{
    int a;
    int x;
    int y;

    func_ov004_0220d280((unsigned char *) (self + 0x740), 0, 0);
    x = func_02057a40(func_ov004_0220d9bc(func_ov004_0220e220(self + 0x6cc)), &data_ov004_022531d4);
    y = func_020579b8(func_ov004_0220d9bc(func_ov004_0220e220(self + 0x6cc)), (const char *) (&data_ov004_022531d4));
    a = *(int *) (self + 0x594);
    if (func_020b9d3c(self + 0x848, (void *) a, (int) (((int *) &data_ov004_022531c8)), func_ov004_0220d9bc(func_ov004_0220e220(self + 0x6cc)), x, y) !=
        0) {
        *(u8 *) (self + 0x870) = 0;
    }
    return 1;
}

void func_ov004_02213d70(char *self)
{
    func_ov004_0220d280((unsigned char *) self + 0x740, 0, 0);
}
