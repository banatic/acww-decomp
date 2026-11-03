/* field_actor_room_states2_11: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b0b8 @ 0x0222b0b8, 0x44 bytes, Thumb
 * func_ov004_0222b0a8 @ 0x0222b0a8, 0x10 bytes, Thumb
 * func_ov004_0222b08c @ 0x0222b08c, 0x1c bytes, Thumb
 * func_ov004_0222aff0 @ 0x0222aff0, 0x9c bytes, Thumb
 * func_ov004_0222afd0 @ 0x0222afd0, 0x20 bytes, Thumb
 * func_ov004_0222afbc @ 0x0222afbc, 0x14 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222b0b8 {
    unsigned char b;
    unsigned char pad_01;
    short e;
};

extern void func_ov004_0222b1b4(const unsigned char *a, int *c, int *d, unsigned short *e, unsigned char *b);
extern int func_ov004_0222b214(int self, int c, int d, short e, int b, int f, short g);
extern void func_020110a0(void *object, short *values);
extern void func_0200fbc4(void *, int, int, int);
extern char *data_020ccf94;
extern int func_02073908(char *g, int a);
extern int func_02008258(void *self, int a);
extern int func_02051e28(void);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_ov004_0222af6c(int self, int b, int c, int d, int e, int f, short g);
extern void func_02010f5c(int);
extern void func_02010d64(int);

void func_ov004_0222b0b8(char *self, short arg)
{
    struct UnkStruct_0222b0b8 t;
    int c, d;

    func_ov004_0222b1b4((const unsigned char *) (self + 0x8f0), &c, &d, (unsigned short *) &t.e, &t.b);
    func_ov004_0222b214((int) self, c, d, t.e, t.b, 6, arg);
    return;
}

void func_ov004_0222b0a8(char *self, int stateId)
{
    // DECLS
    // ENDDECLS
    func_020110a0(self, (short *) (self + 0x7dc));
}

void func_ov004_0222b08c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0200fbc4(self, *(int *) (self + 0x5c), *(int *) (self + 0x64), *(short *) (self + 0x7dc));
}

void func_ov004_0222aff0(char *self)
{
    char *q;

    q = self + 0x7d4;
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        return;
    }
    switch (func_02051e28()) {
        case 0:
            return;
        case 1:
            break;
        case 2:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_0200d4e8(self, 3, 1, -1);
            return;
    }
    if (*(short *) (q + 8) == *(short *) (self + 0x8e)) {
        func_ov004_0222af6c((int) self, *(unsigned char *) (q + 0xa), *(int *) q, *(int *) (q + 4),
                            *(unsigned char *) (q + 0xb), 6, -1);
    }
}

void func_ov004_0222afd0(int arg)
{
    func_ov004_0222b08c((char *) arg);
    func_02010f5c(arg);
    func_02010d64(arg);
    func_ov004_0222aff0((char *) arg);
}

void func_ov004_0222afbc(char *self, u8 a, int b, int c, u8 d)
{
    *(u8 *) self = a;
    *(int *) (self + 4) = b;
    *(int *) (self + 8) = c;
    *(u8 *) (self + 0xc) = d;
}
