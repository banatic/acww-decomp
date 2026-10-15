/* func_ov004_022117b0 @ 0x022117b0, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d2a8(void *p);
extern int func_ov004_0223cb10(void);
extern int func_ov004_0223ca9c(int a, void *self);
extern int *func_ov004_0223cb24(int x);
extern int func_ov004_0223cb18(int x);
extern int func_0203e0a8(void *self, int a);
extern void func_ov004_0220d280(void *p, int a, int b);

void func_ov004_022117b0(char *self)
{
    int x;
    int *p;

    if (func_ov004_0220d2a8(self + 0x740) != 0) {
        x = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
        p = func_ov004_0223cb24(x);
        *(int *) (self + 0x844) = p[0];
        *(int *) (self + 0x848) = p[1];
        *(int *) (self + 0x84c) = p[2];
        *(u16 *) (self + 0x850) = (u16) func_ov004_0223cb18(x);
        func_0203e0a8(self, 0);
    }
    func_ov004_0220d280(self + 0x740, 0, 0);
}
