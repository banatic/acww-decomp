/* field_actor_room_states: 31 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022271dc @ 0x022271dc, 0x2 bytes, Thumb
 * func_ov004_022271a4 @ 0x022271a4, 0x38 bytes, Thumb
 * func_ov004_02227190 @ 0x02227190, 0x14 bytes, Thumb
 * func_ov004_0222714c @ 0x0222714c, 0x42 bytes, Thumb
 * func_ov004_02227118 @ 0x02227118, 0x34 bytes, Thumb
 * func_ov004_02227114 @ 0x02227114, 0x2 bytes, Thumb
 * func_ov004_022270d0 @ 0x022270d0, 0x44 bytes, Thumb
 * func_ov004_02227038 @ 0x02227038, 0x98 bytes, Thumb
 * func_ov004_02226ff0 @ 0x02226ff0, 0x48 bytes, Thumb
 * func_ov004_02226fdc @ 0x02226fdc, 0x14 bytes, Thumb
 * func_ov004_02226fa4 @ 0x02226fa4, 0x36 bytes, Thumb
 * func_ov004_02226f90 @ 0x02226f90, 0x12 bytes, Thumb
 * func_ov004_02226f4c @ 0x02226f4c, 0x44 bytes, Thumb
 * func_ov004_02226f40 @ 0x02226f40, 0xc bytes, Thumb
 * func_ov004_02226ef8 @ 0x02226ef8, 0x48 bytes, Thumb
 * func_ov004_02226ed0 @ 0x02226ed0, 0x28 bytes, Thumb
 * func_ov004_02226eb0 @ 0x02226eb0, 0x20 bytes, Thumb
 * func_ov004_02226e78 @ 0x02226e78, 0x36 bytes, Thumb
 * func_ov004_02226e5c @ 0x02226e5c, 0x1c bytes, Thumb
 * func_ov004_02226e50 @ 0x02226e50, 0xc bytes, Thumb
 * func_ov004_02226e34 @ 0x02226e34, 0x1a bytes, Thumb
 * func_ov004_02226dfc @ 0x02226dfc, 0x36 bytes, Thumb
 * func_ov004_02226db4 @ 0x02226db4, 0x48 bytes, Thumb
 * func_ov004_02226da8 @ 0x02226da8, 0xc bytes, Thumb
 * func_ov004_02226d68 @ 0x02226d68, 0x40 bytes, Thumb
 * func_ov004_02226d4c @ 0x02226d4c, 0x1a bytes, Thumb
 * func_ov004_02226d14 @ 0x02226d14, 0x36 bytes, Thumb
 * func_ov004_02226d00 @ 0x02226d00, 0x14 bytes, Thumb
 * func_ov004_02226cfc @ 0x02226cfc, 0x2 bytes, Thumb
 * func_ov004_02226c94 @ 0x02226c94, 0x68 bytes, Thumb
 * func_ov004_02226c80 @ 0x02226c80, 0x14 bytes, Thumb
 */

#include "types.h"

struct Pair {
    u8 a;
    u8 b;
};

struct Msg {
    u8 pad_00[0xc];
    struct Pair p;
    u8 pad_0E[0x1c - 0xe];
};

struct UnkStruct_02227038 {
    unsigned short a, b;
};

typedef struct {
    int a, b, c;
} UnkStruct_02226f90;

struct UnkStruct_02226f4c {
    int a;
    int b;
    int c;
};

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
} GameState;

struct UnkStruct_02226d68 {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x51F];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

extern int func_02056f94(void *p);
extern void func_02010f5c(void *arg);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern int func_020984fc(void *object);
extern unsigned int func_02099824(const unsigned char *a);
extern unsigned int func_020997f8(void *a);
extern void func_ov004_02225f70(void *self, unsigned int b, unsigned int c);
extern int func_02056f28(void *p, int a);
extern int func_02090c2c(int a, void *b, int c, int d);
extern void func_020112f8(unsigned short *p, void *self);
extern int func_020100e8(void *self, struct UnkStruct_02227038 *t, int a, int b, int c);
extern int func_02011368(void *self);
extern void func_02099808(int h, int a);
extern void func_020997e0(int h, int a);
extern int data_020e25d4;
extern int func_0200dc8c(void *self);
extern int func_0200dc48(void *self);
extern int func_02064558(short v);
extern int func_ov004_02228850(void *self, int a, int b);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_0200fa8c(struct UnkStruct_02226f4c *v, void *self);
extern unsigned int func_ov004_022318f8(void);
extern void func_ov004_02230d30(void);
extern void func_0200fbc4(void *self, int a, int b, int c);
extern int func_0200f554(void *self);
extern void func_020109fc(void *, int, int, int);
extern void func_ov004_02230c98(void);
extern void func_02010d64(void *self);
extern void func_02056fcc(void *, int, int, int, int);
extern void func_ov004_02230ce4(void);
extern int func_02008258(struct UnkStruct_02226d68 *, int);
extern int func_0200d4e8(struct UnkStruct_02226d68 *, int, int, int);
extern int func_ov004_02228dfc(void *self, int a, int b, int c);

int func_ov004_0222714c(void *self, int a, int b, int arg, short v);
int func_ov004_02226e78(void *a0, int a1, int a2);

void func_ov004_022271dc(void *callbackObject, int event) {}

void func_ov004_022271a4(unsigned char *self)
{
    unsigned char *w;
    if (func_02056f94(self + 0x2d0) != 0) {
        w = self + 0x7d4;
        func_ov004_0222714c(self, w[0], w[1], 6, -1);
    }
}

void func_ov004_02227190(void *arg)
{
    func_02010f5c(arg);
    func_ov004_022271a4((unsigned char *) arg);
}

int func_ov004_0222714c(void *self, int a, int b, int arg, short v)
{
    struct Msg m;
    int r;

    func_0200e92c((void *) (&m));
    func_0200e90c((void *) (&m), 0x7c, arg, (short) v);
    {
        struct Pair *q = &m.p;
        q->a = (u8) a;
        q->b = (u8) b;
    }
    r = func_0200e894(self, (void *) (&m));
    func_0200e91c((void *) (&m));
    return r;
}

void func_ov004_02227118(void *self, void *msg, int previous)
{
    unsigned char *d;
    unsigned char b;

    func_020109a0(self, 0x6f, 3, 0);
    b = ((unsigned char *) ((int) msg + 0xc))[1];
    d = (unsigned char *) ((char *) self + 0x7d4);
    d[0] = *((unsigned char *) msg + 0xc);
    d[1] = b;
    d[2] = 0;
}

void func_ov004_02227114(void *callbackObject, int event) {}

void func_ov004_022270d0(void *self)
{
    unsigned char *a;
    unsigned int b;

    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
        a = (unsigned char *) func_020984fc(*(void **) ((char *) self + 0x800));
        b = func_02099824(a);
        func_ov004_02225f70(self, b, func_020997f8(a));
    }
}

void func_ov004_02227038(char *self)
{
    struct UnkStruct_02227038 t;
    unsigned char *q;
    int h;

    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 0xa) != 0) {
        func_02090c2c(0x60, self + 0x6e0, 0, (int) &data_020e25d4);
    }
    if (((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) >= 0xb) {
        q = (unsigned char *) (self + 0x7d4);
        if (q[2] == 0) {
            func_020112f8(&t.b, self);
            t.a = t.b;
            if (func_020100e8(self, &t, q[0], q[1], 0) != 0) {
                h = func_02011368(self);
                func_02099808(h, q[0]);
                func_020997e0(h, q[1]);
                q[2] = 1;
            }
        }
    }
}

void func_ov004_02226ff0(char *self)
{
    if (func_02056f94(self + 0x2d0) != 0) {
        if (func_0200dc8c(self) > 0) {
            if (func_02064558((short) (func_0200dc48(self) - *(short *) (self + 0x8e))) == 0) {
                func_ov004_02228850(self, 6, -1);
            }
        }
    }
}

void func_ov004_02226fdc(void *arg)
{
    func_ov004_02227038((char *) arg);
    func_ov004_02226ff0((char *) arg);
}

int func_ov004_02226fa4(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x7d, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02226f90(int *d, UnkStruct_02226f90 v)
{
    d[0] = v.a;
    d[1] = v.b;
    d[2] = v.c;
}

void func_ov004_02226f4c(unsigned char *self, void *message, int previous)
{
    struct UnkStruct_02226f4c v;
    func_020109a0(self, 0x78, 3, 0);
    func_0200fa8c(&v, self);
    v.c = v.c + 0x2000;
    func_ov004_02226f90((int *) (self + 0x7d4), *(UnkStruct_02226f90 *) &v);
    func_ov004_022318f8();
    func_ov004_02230d30();
}

void func_ov004_02226f40(int a, int b)
{
    func_ov004_02226fa4((void *) a, 6, b);
}

void func_ov004_02226ef8(unsigned char *self)
{
    int *w;
    w = (int *) (self + 0x7d4);
    if (func_02073908((void *) ((*(int *) &data_020ccf94)), *(int *) (self + 0x800)) != 0) {
        func_0200fbc4(self, w[0], w[2], -0x8000);
    } else {
        func_0200f554(self);
    }
}

void func_ov004_02226ed0(GameState *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        func_ov004_02226e78((void *) p, 6, -1);
    }
}

void func_ov004_02226eb0(int arg)
{
    func_ov004_02226ef8((unsigned char *) arg);
    func_02010f5c((void *) arg);
    func_02010d64((void *) arg);
    func_ov004_02226ed0((GameState *) arg);
}

int func_ov004_02226e78(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x7e, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02226e5c(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109fc(self, 0x79, 0x3, 0x0);
    func_ov004_022318f8();
    func_ov004_02230c98();
}

void func_ov004_02226e50(int a, int b)
{
    func_ov004_02226e78((void *) a, 6, b);
}

void func_ov004_02226e34(void *self)
{
    func_02010f5c(self);
    func_02010d64(self);
    func_0200f554(self);
}

int func_ov004_02226dfc(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x7f, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02226db4(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x78, 0x3, 0x0);
    func_02056fcc(self + 0x2d0, ((u32) (*(int *) (self + 0x2d4) << 4) >> 16), 0x3, 0x1000,
                  (u16) (((u32) (*(int *) (self + 0x2d4) << 4) >> 16) - 0x1));
    func_ov004_022318f8();
    func_ov004_02230ce4();
}

void func_ov004_02226da8(int a, int b)
{
    func_ov004_02226dfc((void *) a, 6, b);
}

void func_ov004_02226d68(struct UnkStruct_02226d68 *obj)
{
    if (func_02056f94(&obj->unk_2D0) != 0) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        func_0200d4e8(obj, 3, 1, -1);
    }
}

void func_ov004_02226d4c(void *self)
{
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_02226d68((struct UnkStruct_02226d68 *) self);
}

int func_ov004_02226d14(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x8a, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02226d00(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x95, 0x3, 0x0);
}

void func_ov004_02226cfc(void *callbackObject, int event) {}

void func_ov004_02226c94(unsigned char *self)
{
    if (func_02056f94(self + 0x2d0) != 0) {
        switch (*(int *) (self + 0x704)) {
            case 0x95:
                func_020109a0(self, 0x96, 0, 0);
                break;
            case 0x96:
                func_020109a0(self, 0x97, 0, 0);
                break;
            case 0x97:
                break;
            case 0x98:
                func_ov004_02228dfc(self, 0, 6, -1);
                break;
        }
    }
}

void func_ov004_02226c80(void *arg)
{
    func_02010f5c(arg);
    func_ov004_02226c94((unsigned char *) arg);
}
