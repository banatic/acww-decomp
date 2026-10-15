/* func_020051b4 @ 0x020051b4, 0x184 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0209129c(int a);
extern void func_020962b8(int a);
extern int func_02073d90(void *p);
extern int func_02073908(void *p, int a);
extern void func_020771cc(void *p, int a, int b, int c);
extern void func_020b9e2c(char *p);
extern void func_0205682c(char *p);
extern int func_02055454(char *p);
extern void func_0205502c(char *p);
extern void func_0205ebb4(char *p);
extern void func_0205defc(char *p);
extern void func_0205e4b0(char *p);
extern void func_0205d4e8(char *p);
extern void func_0205d084(char *p);
extern void func_020961e0(char *p);
extern int func_0200f290(char *p, int a);
extern void func_02035638(int a);
extern void func_0200f268(char *p, int a);
extern int func_020044a0(char *p);
extern void func_020b8db4(void);

extern void *data_020ccf94;

int func_020051b4(char *self)
{
    void *g;

    if (*(u32 *) (self + 0x7f0) == 0x6d && *(int *) (self + 0x7d4) != -1) {
        func_0209129c(*(int *) (self + 0x7d4));
    }

    func_020962b8(*(int *) (self + 0x800));

    g = data_020ccf94;
    if (func_02073d90(g)) {
        if (func_02073908(g, *(int *) (self + 0x800))) {
            func_020771cc(*(char **) (self + 0x800) + 8, 0, 0, 0);
        }
    }

    func_020b9e2c(self + 0x778);
    func_0205682c(self + 0x710);
    func_0205682c(self + 0x73c);
    func_02055454(self + 0x500);
    func_02055454(self + 0x38c);
    func_02055454(self + 0x464);
    func_0205502c(self + 0x234);
    func_02055454(self + 0x234);
    func_0205ebb4(self + 0x5a0);
    func_0205defc(self + 0x59c);

    *(u32 *) (self + 0xc8c) = 2;

    func_0205e4b0(self + 0x428);
    func_0205d4e8(self + 0x774);
    func_0205d084(self + 0x389);

    func_020961e0(*(char **) (self + 0x800));

    if (func_0200f290(self, 0x1a)) {
        func_02035638(0x3f);
        func_0200f268(self, 0x1a);
    }

    if (func_0200f290(self, 0xa)) {
        if (func_0200f290(self, 0x19)) {
            func_020044a0(self + 0x83c);
        } else {
            func_020044a0(self + 0x880);
        }
        func_0200f268(self, 0xa);
    }

    if (func_0200f290(self, 0x1b)) {
        func_0200f268(self, 0x1b);
        func_020b8db4();
    }

    return 1;
}
