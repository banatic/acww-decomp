/* room_object_02252ba8_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02215020 @ 0x02215020, 0x98 bytes, Thumb
 * func_ov004_02214fc8 @ 0x02214fc8, 0x58 bytes, Thumb
 */

#include "types.h"

extern void func_0204f818(int *a, int *b, void *p);
extern int func_020b65c4(void);
extern int func_02052e70(int a, int b, int c);
extern void func_ov004_0221524c(void *self, int a);
extern int func_ov004_02210744(void *self);
extern void func_ov004_0220d280(void *p, int a, int b);
extern void *func_ov004_0223b22c(void);
extern void *func_ov004_0223adf4(void *p);
extern void func_02055060(void *p, void *o, int a, int b, int c, int d);
extern void func_02054cac(void *p, void *o, int a, int b, int c, int d, int e);
extern void func_02051f4c(int a, int b, int c);
extern void func_02054cdc(void *argument0);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_0220fd8c(char *argument0);
extern int func_ov004_02215298(char *argument0, int *argument1);

int func_ov004_02215020(char *self)
{
    int a;
    int b;
    void *x;

    func_0204f818(&a, &b, self + 0x5c);
    *(u8 *) (self + 0x77c) = 0xff;
    func_02052e70(a, b, func_020b65c4());
    func_ov004_0221524c(self, 0);
    func_ov004_02210744(self);
    func_ov004_0220d280(self + 0x740, 0, 0);
    if (func_ov004_0223b22c() != 0) {
        x = func_ov004_0223adf4(func_ov004_0223b22c());
        if (*(u8 *) (self + 0x77e) != 0) {
            func_02055060(self + 0x538, x, 0, 0, 0, 0);
        } else {
            func_02054cac(self + 0x538, x, 0x20, 0, 0, 0, 0);
        }
    }
    return 1;
}

void func_ov004_02214fc8(char *self)
{
    // DECLS
    int v3;
    int v5;
    // ENDDECLS
    func_ov004_02215298((char *) (self), (int *) (self + 0x5c));
    func_02054cdc(self + 0x538);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        func_ov004_0220d280((void *) ((unsigned char *) (self + 0x740)), 0, 0);
        v5 = func_020b65c4();
        func_02051f4c((int) (v5), (int) (self + 0x5c), (int) (func_ov004_0220fd8c(self)));
    }
}
