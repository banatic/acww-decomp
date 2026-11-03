/* music_player: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022160b0 @ 0x022160b0, 0x60 bytes, Thumb
 * func_ov004_0221605c @ 0x0221605c, 0x54 bytes, Thumb
 * func_ov004_02215ff0 @ 0x02215ff0, 0x6c bytes, Thumb
 * func_ov004_02215f8c @ 0x02215f8c, 0x64 bytes, Thumb
 */

#include "types.h"

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_02210744(void *);
extern void func_ov004_02216598(void *, int, int);
extern int func_0203e0a8(void *, int);
extern int func_02095ec4(void);
extern int func_ov004_0220d058(void *, int, int, int);
extern int func_ov004_0220d2a8(void *);
extern int func_ov004_0220ffbc(void *);
extern int func_ov004_0221078c(void *self);
extern void func_ov004_0223c2b4(int a, int (*fn)(void *), int c);
extern int func_ov004_02211308(void *self);
extern void func_ov004_022165dc(void *self, int a);
extern int func_ov004_022107d4(char *argument0);
extern void func_ov004_0223cf2c(char *argument0, int argument1);

int func_ov004_022160b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02210744(self);
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    if (*(u8 *) (self + 0x77e) == 0x0) {
        func_ov004_02216598(self, *(u8 *) (self + 0x845), 0x1);
    }
    if (*(int *) (self + 0x780) == 0x29) {
        func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    }
    return 0x1;
}

void func_ov004_0221605c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x780) == 0x29) {
        func_ov004_0220ffbc(self);
    }
    func_ov004_0220d058(self + 0x848, 0x0, 0x1, 0x0);
    if (func_ov004_0220d2a8(self + 0x740) != 0x0) {
        func_ov004_0220d280(self + 0x740, 0x0, 0x0);
        func_0203e0a8(self, 0x0);
        func_02095ec4();
        return;
    }
}

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

int func_ov004_02215f8c(char *self)
{
    // DECLS
    int v5;
    // ENDDECLS
    func_ov004_0220ffbc((void *) self);
    func_ov004_022107d4(self);
    func_ov004_0220d058((void *) (self + 0x848), 0x1, 0x1, 0x0);
    func_ov004_0223cf2c((char *) (self + 0x798), (int) (self + 0x7b8));
    v5 = func_ov004_0220d2a8((void *) (self + 0x740));
    if (v5 != 0x0) {
        func_ov004_0220d280((void *) ((unsigned char *) (self + 0x740)), (unsigned char) ((unsigned char) (0x1)), (int) (0x0));
        func_0203e0a8((void *) ((int) (self)), (int) (0x0));
        return func_02095ec4();
    }
    return v5;
}
