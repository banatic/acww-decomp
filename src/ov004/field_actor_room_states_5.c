/* field_actor_room_states_5: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02227f90 @ 0x02227f90, 0x54 bytes, Thumb
 * func_ov004_02227f8c @ 0x02227f8c, 0x2 bytes, Thumb
 * func_ov004_02227f24 @ 0x02227f24, 0x68 bytes, Thumb
 * func_ov004_02227f08 @ 0x02227f08, 0x1a bytes, Thumb
 * func_ov004_02227f00 @ 0x02227f00, 0x6 bytes, Thumb
 */

#include "types.h"

struct Rec {
    int id;
    u16 count;
};

extern int func_0200f328(void *, int);
extern void func_020109a0(void *, int, int, unsigned short d);
extern void func_02056fcc(void *, int, int, int, int);
extern unsigned char func_02057cf4(void);
extern int func_02057d0c(int, void *);
extern int func_02056f94(void *p);
extern int func_02008258(void *self, int a);
extern int func_0200c3b0(void *self, int a, int b, int c);
extern void func_02057bb8(unsigned short *buf);
extern void func_02057cb8(void *self);
extern void func_02010f5c(void *self);
extern void func_02010d64(void *self);

void func_ov004_02227f90(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x2e, 0x3, 0x0);
    func_02057d0c(((void) (func_02056fcc(self + 0x2d0, ((u32) (*(int *) (self + 0x2d4) << 4) >> 16), 0x3, 0x1000,
                                         (u16) (((u32) (*(int *) (self + 0x2d4) << 4) >> 16) - 0x1))),
                   func_02057cf4()),
                  self);
    func_0200f328(self, 0x52);
    return;
}

void func_ov004_02227f8c(void *callbackObject, int event) {}

void func_ov004_02227f24(char *self)
{
    unsigned short buf[2];

    if (func_02056f94(self + 0x2d0) != 0) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        func_0200c3b0(self, 3, 5, -1);
        func_02057bb8(buf);
        if (buf[0] == 0x1379) {
            *(char *) (self + 0x8eb) = 4;
        }
        func_02057cb8(self);
    }
}

void func_ov004_02227f08(void *self)
{
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_02227f24((char *) self);
}

void func_ov004_02227f00(struct Rec *r, int id, u16 count)
{
    r->id = id;
    r->count = count;
}
