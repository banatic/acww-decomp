/* field_actor_room_states_2: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022272f0 @ 0x022272f0, 0x2 bytes, Thumb
 * func_ov004_02227268 @ 0x02227268, 0x88 bytes, Thumb
 * func_ov004_02227254 @ 0x02227254, 0x14 bytes, Thumb
 * func_ov004_02227210 @ 0x02227210, 0x42 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02227268 {
    unsigned short a;
    unsigned short b;
};

struct Pair {
    u8 a;
    u8 b;
};

struct Msg {
    u8 pad_00[0xc];
    struct Pair p;
    u8 pad_0E[0x1c - 0xe];
};

extern int func_02056f94(void *p);
extern int func_020112e4(void *self);
extern void func_020112f8(unsigned short *p, void *self);
extern int func_020112d0(void *self);
extern int func_020100e8(void *self, struct UnkStruct_02227268 *t, int a, int b, int c);
extern int func_02011368(void *self);
extern void func_02099808(int a, int b);
extern void func_02010f5c(void *arg);
extern unsigned int func_0200e92c(struct Msg *m);
extern void func_0200e90c(struct Msg *m, int kind, int arg, short v);
extern int func_0200e894(void *self, struct Msg *m);
extern int func_0200e91c(struct Msg *m);

int func_ov004_02227210(void *self, int a, int b, int arg, short v);

void func_ov004_022272f0(void *callbackObject, int event) {}

void func_ov004_02227268(char *self)
{
    struct UnkStruct_02227268 t;
    unsigned char *q;

    if (func_02056f94(self + 0x2d0) != 0) {
        q = (unsigned char *) (self + 0x7d4);
        func_ov004_02227210(self, q[0], q[1], 6, -1);
        return;
    }
    if (((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) >= 3) {
        if (func_020112e4(self) != 0) {
            func_020112f8(&t.b, self);
            t.a = t.b;
            if (func_020100e8(self, &t, 0, func_020112d0(self), 0) != 0) {
                func_02099808(func_02011368(self), 0);
            }
        }
    }
}

void func_ov004_02227254(void *arg)
{
    func_02010f5c(arg);
    func_ov004_02227268((char *) arg);
}

int func_ov004_02227210(void *self, int a, int b, int arg, short v)
{
    struct Msg m;
    int r;

    func_0200e92c(&m);
    func_0200e90c(&m, 0x7b, arg, v);
    {
        struct Pair *q = &m.p;
        q->a = (u8) a;
        q->b = (u8) b;
    }
    r = func_0200e894(self, &m);
    func_0200e91c(&m);
    return r;
}
