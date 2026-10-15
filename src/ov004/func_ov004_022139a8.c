/* func_ov004_022139a8 @ 0x022139a8, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022139a8 {
    int x, y, z;
};

extern int func_02072614(void);
extern int func_0207277c(int a, int b);
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_020044d0(void *p, struct UnkStruct_022139a8 *t);

int func_ov004_022139a8(char *self)
{
    struct UnkStruct_022139a8 t;

    if (*(u8 *) (self + 0x888) != 0) {
        t = *(struct UnkStruct_022139a8 *) (self + 0x7b8);
        if (func_0207277c(func_02072614(), *(int *) (self + 0x844))) {
            func_020044c0(self + 0x848, 0x50, 0x7f, 0);
        }
        func_020044d0(self + 0x848, &t);
    }
    return 1;
}
