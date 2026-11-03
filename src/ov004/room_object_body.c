/* room_object_body: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220f484 @ 0x0220f484, 0xa8 bytes, Thumb
 * func_ov004_0220f450 @ 0x0220f450, 0x34 bytes, Thumb
 */

#include "types.h"

extern int func_0205790c(int x, void *d);
extern void func_ov004_0220d398(void *p, signed char a, signed char b);
extern void func_02055dc8(void *p, void *fn, void *self);
extern void func_ov004_02211450(char *arg0);
extern void func_ov004_0220cff0(void *p, int a, int b);
extern void *func_ov004_0220e068(void *p);
extern void *func_ov004_0220e050(void *p);
extern int NNS_G3dBindMdlTex(void *a, void *b);
extern int NNS_G3dBindMdlPltt(void *a, void *b);
extern int data_ov004_02250018;
extern int data_ov004_02250020;
extern void func_02055d80(void *object, int value);
extern int func_ov004_0223cd78(int *argument0, int argument1);
extern void *func_ov004_0223ce84(void);
extern void *data_ov004_02247640;

void func_ov004_0220f450(char *self);

void func_ov004_0220f484(char *self)
{
    int x;
    int a;
    int b;

    x = *(int *) (self + 0x594);
    a = func_0205790c(x, &data_ov004_02250018);
    b = func_0205790c(x, &data_ov004_02250020);
    func_ov004_0220d398(self + 0x742, (signed char) a, (signed char) b);
    func_02055dc8(self + 0x538, (void *) func_ov004_02211450, self);
    func_ov004_0220cff0(self + 0x764, *(int *) (self + 0x594), 1);
    NNS_G3dBindMdlTex(func_ov004_0220e068(self + 0x6cc), func_ov004_0220e050(self + 0x6cc));
    NNS_G3dBindMdlPltt(func_ov004_0220e068(self + 0x6cc), func_ov004_0220e050(self + 0x6cc));
    func_ov004_0220f450((char *) self);
}

void func_ov004_0220f450(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_ov004_0223cd78((int *) (func_ov004_0223ce84()), (int) (self));
    if (v2 != -0x1) {
        func_02055d80(self + 0x538, *(u8 *) ((char *) &data_ov004_02247640 + v2));
    }
}
