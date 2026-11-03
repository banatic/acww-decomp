/* field_actor_room_states_12: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02228a2c @ 0x02228a2c, 0x10 bytes, Thumb
 * func_ov004_022289b8 @ 0x022289b8, 0x74 bytes, Thumb
 * func_ov004_022289b4 @ 0x022289b4, 0x2 bytes, Thumb
 * func_ov004_02228978 @ 0x02228978, 0x3c bytes, Thumb
 * func_ov004_022288c8 @ 0x022288c8, 0xb0 bytes, Thumb
 * func_ov004_02228888 @ 0x02228888, 0x40 bytes, Thumb
 * func_ov004_02228850 @ 0x02228850, 0x36 bytes, Thumb
 * func_ov004_02228840 @ 0x02228840, 0xe bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022289b8 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02228888 {
    u8 pad_00[0x5c];
    u8 sub[4];
};

extern void func_0200fa1c(struct UnkStruct_022289b8 *out, void *self, struct UnkStruct_022289b8 *in, unsigned short *p,
                          int *q);
extern int func_02073908(int a, int b);
extern void func_02051ea4(struct UnkStruct_022289b8 *out);
extern short data_ov004_0224776c[];
extern int data_ov004_02247780;
extern int data_020ccf94;
extern void func_02010d88(void *self, int *t, int a, int b);
extern void func_02089fc8(void *p);
extern int func_02051e9c(void);
extern int func_02008258(void *self, int a);
extern int func_ov004_02228dfc(void *self, int a, int b, int c);
extern int func_ov004_02228b14(void *self, int a, int b);
extern int func_ov004_02228be0(void *self, int a, int b);
extern u8 data_020e54a8;
extern void func_ov004_0223a6d8(void *p);
extern void func_02010f5c(struct UnkStruct_02228888 *self);
extern void func_02010d64(struct UnkStruct_02228888 *self);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_ov004_02228850(void *a0, int a1, int a2);

void *func_ov004_02228a2c(char *self, char *a1, int a2)
{
    // DECLS
    // ENDDECLS
    *(int *) (self) = *(int *) (a1);
    *(int *) (self + 0x4) = *(int *) (a1 + 0x4);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x8);
    *(u8 *) (self + 0xc) = a2;
    return self;
}

void func_ov004_022289b8(unsigned char *self, unsigned char *p, int previous)
{
    short sh;
    struct UnkStruct_022289b8 out, v;
    int b;

    b = *(unsigned char *) (p + 0xc);
    sh = (short) (*(short *) (self + 0x8e) - data_ov004_0224776c[b]);
    func_0200fa1c(&out, self, (struct UnkStruct_022289b8 *) (self + 0x5c), (unsigned short *) &sh, &data_ov004_02247780);
    v.a = out.a;
    v.b = out.b;
    v.c = out.c;
    func_ov004_02228a2c((char *) (self + 0x7d4), (char *) (&v), b);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_02051ea4(&out);
    }
}

void func_ov004_022289b4(void *callbackObject, int event) {}

void func_ov004_02228978(void *self)
{
    int t[4];
    int *p;

    p = (int *) ((char *) self + 0x7d4);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_02010d88(self, t, 0x1000, 0x1000);
    func_02089fc8((char *) self + 0x1c4);
}

void func_ov004_022288c8(char *self)
{
    unsigned char *q;

    switch (func_02051e9c()) {
        case 0:
            return;
        case 1:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            break;
        case 2:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_ov004_02228dfc(self, 3, 6, -1);
            return;
    }
    q = (unsigned char *) (self + 0x7d4);
    if (*(unsigned char *) (self + 0x200) != 0) {
        func_ov004_02228dfc(self, 3, 6, -1);
        return;
    }
    switch (q[0xc]) {
        case 0:
            func_ov004_02228850(self, 6, -1);
            break;
        case 1:
            func_ov004_02228b14(self, 6, -1);
            break;
        case 2:
            func_ov004_02228be0(self, 6, -1);
            break;
    }
}

void func_ov004_02228888(struct UnkStruct_02228888 *self)
{
    int on;

    on = !(data_020e54a8 != 1);
    if (on != 0) {
        func_ov004_0223a6d8(&self->sub);
    }
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_022288c8((char *) self);
    func_ov004_02228978((void *) self);
}

int func_ov004_02228850(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x2c, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void *func_ov004_02228840(char *self, char *a1)
{
    // DECLS
    // ENDDECLS
    *(int *) (self) = *(int *) (a1);
    *(int *) (self + 0x4) = *(int *) (a1 + 0x4);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x8);
    return self;
}
