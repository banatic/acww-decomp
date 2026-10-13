/* func_ov004_02215ff0 @ 0x02215ff0, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0221078c(void *self);
extern void func_ov004_0223c2b4(int a, void (*fn)(void), int c);
extern void func_ov004_02211308(void);
extern void func_ov004_0220d280(void *p, int a, int b);
extern void func_ov004_022165dc(void *self, int a);
extern void func_ov004_022101e4(void *self, int a, int b, int c, int d);

int func_ov004_02215ff0(char *self)
{
    func_ov004_0221078c(self);
    func_ov004_0223c2b4(0, func_ov004_02211308, 0);
    func_ov004_0220d280(self + 0x740, 1, 0);
    *(u8 *) (self + 0x845) = *(u8 *) (self + 0x77c);
    func_ov004_022165dc(self, *(u8 *) (self + 0x77c));
    if (*(int *) (self + 0x780) == 0x29) {
        func_ov004_022101e4(self, 1, 0, 0x1000, 0);
    }
    return 1;
}
