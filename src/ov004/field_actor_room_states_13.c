/* field_actor_room_states_13: 22 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02228e58 @ 0x02228e58, 0x28 bytes, Thumb
 * func_ov004_02228e38 @ 0x02228e38, 0x20 bytes, Thumb
 * func_ov004_02228dfc @ 0x02228dfc, 0x3c bytes, Thumb
 * func_ov004_02228dc4 @ 0x02228dc4, 0x38 bytes, Thumb
 * func_ov004_02228db0 @ 0x02228db0, 0x14 bytes, Thumb
 * func_ov004_02228da0 @ 0x02228da0, 0x10 bytes, Thumb
 * func_ov004_02228d14 @ 0x02228d14, 0x8c bytes, Thumb
 * func_ov004_02228c84 @ 0x02228c84, 0x90 bytes, Thumb
 * func_ov004_02228c18 @ 0x02228c18, 0x6c bytes, Thumb
 * func_ov004_02228be0 @ 0x02228be0, 0x36 bytes, Thumb
 * func_ov004_02228bac @ 0x02228bac, 0x34 bytes, Thumb
 * func_ov004_02228ba0 @ 0x02228ba0, 0xc bytes, Thumb
 * func_ov004_02228b90 @ 0x02228b90, 0x10 bytes, Thumb
 * func_ov004_02228b68 @ 0x02228b68, 0x28 bytes, Thumb
 * func_ov004_02228b4c @ 0x02228b4c, 0x1a bytes, Thumb
 * func_ov004_02228b14 @ 0x02228b14, 0x36 bytes, Thumb
 * func_ov004_02228ae0 @ 0x02228ae0, 0x34 bytes, Thumb
 * func_ov004_02228ad4 @ 0x02228ad4, 0xc bytes, Thumb
 * func_ov004_02228ac4 @ 0x02228ac4, 0x10 bytes, Thumb
 * func_ov004_02228a9c @ 0x02228a9c, 0x28 bytes, Thumb
 * func_ov004_02228a80 @ 0x02228a80, 0x1a bytes, Thumb
 * func_ov004_02228a7c @ 0x02228a7c, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[12];
    unsigned short value;
    unsigned char pad_0E[14];
} UnkStruct_02228dfc;

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
} GameState;

typedef struct {
    unsigned char unk_00;
} UnkStruct_02228a7c;

extern int func_02056f94(void *p);
extern void func_ov004_02228e80(int);
extern int func_0200f554(int);
extern unsigned int func_0200e92c(void *p);
extern int func_0200e894(void *p, void *q);
extern int func_0200e91c(void *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_020355e0(void);
extern int func_020e8b0c(int a, int b, int c);
extern char *func_0200420c(void);
extern void func_02056e60(void *p, int a);
extern void func_02054860(void *p);
extern void func_02010f5c(void *self);
extern int func_0200dc8c(void *self);
extern int func_0200dc48(void *self);
extern int func_02064558(short v);
extern int func_ov004_0223c40c(void *p, short a);
extern int func_ov004_0223c3b8(void *p, short a);
extern int func_ov004_0223c364(void *p, short a);
extern int func_ov004_02228a3c(void *self, int a, int b, int c);
extern unsigned char data_020e54a8;
extern char *data_020ccf94;
extern void func_ov004_0223a6d8(void *p);
extern int func_02010ca4(void *self);
extern int func_02073908(char *a, int b);
extern int func_02008258(void *self, int a);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200f328(void *, int);
extern void func_020109a0(void *, int, int, unsigned short d);
extern void func_020110a0(void *object, short *values);
extern int func_ov004_02228850(GameState *p, int a, int b);
extern void func_02010d64(void *self);

int func_ov004_02228dfc(void *param0, unsigned short param1, void *param2, void *param3);

void func_ov004_02228e58(void *self)
{
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        func_ov004_02228dfc(self, 0, (void *) 6, (void *) (~0));
    }
}

void func_ov004_02228e38(int arg)
{
    func_ov004_02228e80(arg);
    func_0200f554(arg);
    func_02010d64((void *) arg);
    func_ov004_02228e58((void *) arg);
}

int func_ov004_02228dfc(void *param0, unsigned short param1, void *param2, void *param3)
{
    UnkStruct_02228dfc stackVar;
    int result;

    func_0200e92c(&stackVar);
    func_0200e90c(&stackVar, 0x28, (int) param2, (int) param3);
    stackVar.value = param1;
    result = func_0200e894(param0, &stackVar);
    func_0200e91c(&stackVar);
    return result;
}

void func_ov004_02228dc4(unsigned char *self, unsigned char *p, int previous)
{
    unsigned short *q;
    unsigned char *w;
    q = (unsigned short *) (p + 0xc);
    if (*(int *) (self + 0x704) != 0x24) {
        func_020109fc(self, 0x24, *q, 0);
    }
    w = self + 0x7d4;
    *(int *) w = *(int *) (self + 0xb0);
    *(unsigned char *) (w + 4) = 0;
}

void func_ov004_02228db0(int a, int b)
{
    func_ov004_02228dfc((void *) a, 0, (void *) 6, (void *) b);
    return;
}

void func_ov004_02228da0(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0xb0) = *(int *) (self + 0x7d4);
}

void func_ov004_02228d14(char *self)
{
    char *e;
    char *r;
    unsigned char *q;

    if (func_020e8b0c(func_020355e0(), 0x63, 0xab) != 0) {
        e = func_0200420c();
        if (e != 0) {
            if (*(signed char *) (e + 3) != 1) {
                r = self + 0x234;
                q = (unsigned char *) (self + 0x7d4);
                if (q[4] == 0) {
                    q[4] = 1;
                    if (((unsigned int) (*(int *) (r + 0xa4) << 4) >> 16) != 0) {
                        func_02056e60(r + 0xb8, 0xa);
                    }
                }
                *(int *) (r + 0xa4) = 0;
                *(int *) (r + 0xac) = *(int *) (e + 0xc);
                func_02054860(r);
                *(int *) (r + 0xac) = 0x1000;
                *(int *) (self + 0xb0) = 0;
                return;
            }
        }
    }
    func_02010f5c(self);
}

void func_ov004_02228c84(char *self)
{
    if (func_0200dc8c(self) > 0) {
        switch (func_02064558((short) (*(short *) (self + 0x8e) - func_0200dc48(self)))) {
            case 0:
                if (func_ov004_0223c40c(self + 0x5c, *(short *) (self + 0x8e)) != 0) {
                    func_ov004_02228a3c(self, 0, 6, -1);
                }
                break;
            case 3:
                if (func_ov004_0223c3b8(self + 0x5c, *(short *) (self + 0x8e)) != 0) {
                    func_ov004_02228a3c(self, 1, 6, -1);
                }
                break;
            case 1:
                if (func_ov004_0223c364(self + 0x5c, *(short *) (self + 0x8e)) != 0) {
                    func_ov004_02228a3c(self, 2, 6, -1);
                }
                break;
        }
    }
}

void func_ov004_02228c18(char *self)
{
    unsigned int t;

    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t != 0) {
        func_ov004_0223a6d8(self + 0x5c);
    }
    func_ov004_02228d14((char *) self);
    func_02010ca4(self);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_ov004_02228c84((char *) self);
    } else {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    }
}

int func_ov004_02228be0(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x29, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02228bac(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x7d4) = (*(short *) (self + 0x8e) - 0x4000);
    func_020109a0(self, 0x26, 0x0, 0x0);
    func_0200f328(self, 0x4c9);
    return;
}

void func_ov004_02228ba0(int a, int b)
{
    func_ov004_02228be0((void *) a, 6, b);
}

void func_ov004_02228b90(char *self, int stateId)
{
    // DECLS
    // ENDDECLS
    func_020110a0(self, (short *) (self + 0x7d4));
}

void func_ov004_02228b68(GameState *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        func_ov004_02228850(p, 6, -1);
    }
}

void func_ov004_02228b4c(void *self)
{
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_02228b68((GameState *) self);
}

int func_ov004_02228b14(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x2a, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02228ae0(unsigned char *self, void *message, int previous)
{
    *(short *) (self + 0x7d4) = (short) (*(short *) (self + 0x8e) + 0x4000);
    func_020109a0(self, 0x25, 0, 0);
    func_0200f328(self, 0x4c9);
}

void func_ov004_02228ad4(int a, int b)
{
    func_ov004_02228b14((void *) a, 6, b);
}

void func_ov004_02228ac4(char *self, int stateId)
{
    // DECLS
    // ENDDECLS
    func_020110a0(self, (short *) (self + 0x7d4));
}

void func_ov004_02228a9c(GameState *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        func_ov004_02228850(p, 6, -1);
    }
}

void func_ov004_02228a80(void *self)
{
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_02228a9c((GameState *) self);
}

void func_ov004_02228a7c(UnkStruct_02228a7c *p, unsigned char v)
{
    p->unk_00 = v;
}
