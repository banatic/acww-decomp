/* func_ov003_0222fe18 @ 0x0222fe18, 0x114 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02042200(void);
extern void func_02054fcc(void *p);
extern void func_02004280(void *p);
extern void func_0209d090(void *p);
extern void func_0209d200(void *a, void *b);

void func_ov003_0222fe18(char *a0, char *self, int mode)
{
    int *p;
    int *q;

    p = (int *) (self + 0x204);
    q = (int *) (self + 0x1d4);
    if (*(s8 *) (self + 0x24d) == 0x33) {
        func_02042200();
    }
    if (*(s8 *) (self + 0x24d) >= 0) {
        func_02054fcc(self + 0x50);
    }
    *(u8 *) (self + 0x250) = 0;
    *(int *) (self + 0x21c) = 0;
    func_02004280(self + 0x174);
    p[0] = 1;
    p[1] = 1;
    p[2] = 1;
    q[0] = 1;
    q[1] = 1;
    q[2] = 1;
    *(u8 *) (self + 0x248) = 0;
    *(u8 *) (self + 0x249) = 0;
    *(u8 *) (self + 0x258) = 0;
    *(s8 *) (self + 0x24d) = -1;
    *(short *) (self + 0x23a) = 0;
    *(short *) (self + 0x242) = 0;
    *(u8 *) (self + 0x251) = 0x13;
    func_0209d090(self + 0x130);
    *(int *) (self + 0x18) = 0;
    *(int *) (self + 0x1c) = 0;
    *(u8 *) (self + 0x254) = 0;
    *(u8 *) (self + 0x24a) = 0;
    *(short *) (self + 0x236) = 0;
    if (mode == 1) {
        func_0209d200(a0 + 0x50, self + 0x230);
    } else if (mode == 2) {
        func_0209d200(a0 + 0x68, self + 0x230);
    } else {
        func_0209d200(a0 + 0x80, self + 0x230);
    }
    *(int *) (self + 0x170) = 0;
}
