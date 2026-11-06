/* field_actor_room_states_3: 30 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022279d8 @ 0x022279d8, 0x26 bytes, Thumb
 * func_ov004_022279a0 @ 0x022279a0, 0x36 bytes, Thumb
 * func_ov004_02227958 @ 0x02227958, 0x48 bytes, Thumb
 * func_ov004_0222794c @ 0x0222794c, 0xc bytes, Thumb
 * func_ov004_022278fc @ 0x022278fc, 0x50 bytes, Thumb
 * func_ov004_02227888 @ 0x02227888, 0x74 bytes, Thumb
 * func_ov004_02227858 @ 0x02227858, 0x30 bytes, Thumb
 * func_ov004_02227818 @ 0x02227818, 0x40 bytes, Thumb
 * func_ov004_022277cc @ 0x022277cc, 0x4c bytes, Thumb
 * func_ov004_02227794 @ 0x02227794, 0x36 bytes, Thumb
 * func_ov004_02227764 @ 0x02227764, 0x30 bytes, Thumb
 * func_ov004_02227758 @ 0x02227758, 0xc bytes, Thumb
 * func_ov004_02227708 @ 0x02227708, 0x50 bytes, Thumb
 * func_ov004_02227694 @ 0x02227694, 0x74 bytes, Thumb
 * func_ov004_02227664 @ 0x02227664, 0x30 bytes, Thumb
 * func_ov004_02227624 @ 0x02227624, 0x40 bytes, Thumb
 * func_ov004_022275d8 @ 0x022275d8, 0x4c bytes, Thumb
 * func_ov004_022275a0 @ 0x022275a0, 0x36 bytes, Thumb
 * func_ov004_02227580 @ 0x02227580, 0x20 bytes, Thumb
 * func_ov004_02227574 @ 0x02227574, 0xc bytes, Thumb
 * func_ov004_02227524 @ 0x02227524, 0x50 bytes, Thumb
 * func_ov004_022274c4 @ 0x022274c4, 0x60 bytes, Thumb
 * func_ov004_022274a0 @ 0x022274a0, 0x24 bytes, Thumb
 * func_ov004_02227468 @ 0x02227468, 0x36 bytes, Thumb
 * func_ov004_02227448 @ 0x02227448, 0x20 bytes, Thumb
 * func_ov004_0222743c @ 0x0222743c, 0xc bytes, Thumb
 * func_ov004_022273ec @ 0x022273ec, 0x50 bytes, Thumb
 * func_ov004_0222738c @ 0x0222738c, 0x60 bytes, Thumb
 * func_ov004_02227368 @ 0x02227368, 0x24 bytes, Thumb
 * func_ov004_02227324 @ 0x02227324, 0x42 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02227888 {
    u8 pad_00[0x2d0];
    u8 sub[0x704 - 0x2d0];
    int state;
};

struct UnkStruct_02227818 {
    u8 pad_00[0x2d8];
    unsigned int lo : 12;
    unsigned int mid : 16;
    unsigned int hi : 4;
    u8 pad_2DC[0x804 - 0x2dc];
    int arg;
};

struct UnkStruct_022277cc {
    u8 pad_00[0x800];
    int room;
};

struct UnkStruct_02227694 {
    u8 pad_00[0x2d0];
    u8 sub[0x704 - 0x2d0];
    int state;
};

struct UnkStruct_02227624 {
    u8 pad_00[0x2d8];
    unsigned int lo : 12;
    unsigned int mid : 16;
    unsigned int hi : 4;
    u8 pad_2DC[0x804 - 0x2dc];
    int arg;
};

struct UnkStruct_022275d8 {
    u8 pad_00[0x800];
    int room;
};

struct UnkStruct_022274c4 {
    u8 pad_00[0x2d0];
    u8 sub[0x7f0 - 0x2d0];
    int src;
    u8 pad_7F4[0x7fc - 0x7f4];
    int handle;
    int room;
};

struct UnkStruct_0222738c {
    u8 pad_00[0x2d0];
    u8 sub[0x7f0 - 0x2d0];
    int src;
    u8 pad_7F4[0x7fc - 0x7f4];
    int handle;
    int room;
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

extern void func_ov004_02227d60(void *);
extern void func_ov004_02227cb0(void *);
extern void func_ov004_02227bf4(void *);
extern void func_02010d64(void *);
extern void func_ov004_02227a00(void *);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int func_02073908(int a, int b);
extern void func_020109fc(void *self, int a, int b, int c);
extern int data_020ccf94;
extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int n);
extern void func_0200f888(void *self);
extern void func_ov004_0222626c(void *argument0, unsigned int argument1, unsigned int argument2);
extern u8 data_021c75b8;
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_02010f6c(struct UnkStruct_022277cc *self);
extern void func_020109a0(void *, int, int, unsigned short d);
extern int func_02056f94(void *p);
extern void func_0200f3e8(struct UnkStruct_022274c4 *self);
extern int func_02008258(struct UnkStruct_022274c4 *self, int a);
extern int func_0200d4e8(struct UnkStruct_022274c4 *self, int a, int b, int c);
extern int func_0203e110(void);

void func_ov004_022279d8(void *p)
{
    func_ov004_02227d60(p);
    func_ov004_02227cb0(p);
    func_ov004_02227bf4(p);
    func_02010d64(p);
    func_ov004_02227a00(p);
}

int func_ov004_022279a0(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x41, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02227958(unsigned char *self, void *message, int previous)
{
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        if (*(int *) (self + 0x704) != 0x3e) {
            func_020109fc(self, 0x3e, 3, 0);
        }
    } else {
        func_020109fc(self, 0, 3, 3);
    }
}

void func_ov004_0222794c(int a, int b)
{
    func_ov004_022279a0((void *) a, 9, b);
    return;
}

void func_ov004_022278fc(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 1) || func_02056f28(self + 0x2d0, 6) || func_02056f28(self + 0x2d0, 0xb) ||
        func_02056f28(self + 0x2d0, 0x10)) {
        func_0200f888(self);
    }
}

void func_ov004_02227888(struct UnkStruct_02227888 *self, int flag)
{
    if (flag != 0 && self->state != 0x3e) {
        func_020109a0((void *) self, 0x3e, 3, 0);
    }
    func_02010f5c((void *) self);
    if (self->state == 0x3e) {
        if (func_02056f28(&self->sub, 1) || func_02056f28(&self->sub, 6) || func_02056f28(&self->sub, 0xb) ||
            func_02056f28(&self->sub, 0x10)) {
            func_0200f888((void *) self);
        }
    }
}

void func_ov004_02227858(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x704) == 0x3e && (u32) ((u32) (*(int *) (self + 0x2d8) << 4) >> 16) >= 0x6) {
        func_ov004_0222626c(self, 0x0, 0x6);
    }
}

void func_ov004_02227818(struct UnkStruct_02227818 *self)
{
    int idle;

    idle = !data_021c75b8;
    if (idle != 0) {
        return;
    }
    if (self->mid >= 5) {
        func_020b6098(func_020b5e10(), self->arg);
    }
}

void func_ov004_022277cc(struct UnkStruct_022277cc *self)
{
    if (func_02073908(data_020ccf94, self->room)) {
        func_ov004_022278fc((char *) self);
        func_ov004_02227858((char *) self);
        func_ov004_02227818((struct UnkStruct_02227818 *) self);
    } else {
        func_ov004_02227888((struct UnkStruct_02227888 *) self, func_02010f6c(self));
        func_ov004_02227858((char *) self);
    }
}

int func_ov004_02227794(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x42, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02227764(char *self, void *message, int previous)
{
    // DECLS
    int v3;
    // ENDDECLS
    v3 = func_02073908((int) ((void *) (*(int *) ((char *) ((void **) &data_020ccf94)))), (int) (*(int *) (self + 0x800)));
    if (v3 == 0x0) {
        func_020109fc((void *) ((int) (self)), (int) (0x0), (int) (0x3), (int) (0x3));
    }
    return;
}

void func_ov004_02227758(int a, int b)
{
    func_ov004_02227794((void *) a, 9, b);
    return;
}

void func_ov004_02227708(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 1) || func_02056f28(self + 0x2d0, 6) || func_02056f28(self + 0x2d0, 0xb) ||
        func_02056f28(self + 0x2d0, 0x10)) {
        func_0200f888(self);
    }
}

void func_ov004_02227694(struct UnkStruct_02227694 *self, int flag)
{
    if (flag != 0 && self->state != 0x3f) {
        func_020109a0((void *) self, 0x3f, 3, 0);
    }
    func_02010f5c((void *) self);
    if (self->state == 0x3e) {
        if (func_02056f28(&self->sub, 1) || func_02056f28(&self->sub, 6) || func_02056f28(&self->sub, 0xb) ||
            func_02056f28(&self->sub, 0x10)) {
            func_0200f888((void *) self);
        }
    }
}

void func_ov004_02227664(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x704) == 0x3f && (u32) ((u32) (*(int *) (self + 0x2d8) << 4) >> 16) >= 0x9) {
        func_ov004_0222626c(self, 0x0, 0x6);
    }
}

void func_ov004_02227624(struct UnkStruct_02227624 *self)
{
    int idle;

    idle = !data_021c75b8;
    if (idle != 0) {
        return;
    }
    if (self->mid >= 5) {
        func_020b6098(func_020b5e10(), self->arg);
    }
}

void func_ov004_022275d8(struct UnkStruct_022275d8 *self)
{
    if (func_02073908(data_020ccf94, self->room)) {
        func_ov004_02227708((char *) self);
        func_ov004_02227664((char *) self);
        func_ov004_02227624((struct UnkStruct_02227624 *) self);
    } else {
        func_ov004_02227694((struct UnkStruct_02227694 *) self, func_02010f6c((struct UnkStruct_022277cc *) self));
        func_ov004_02227664((char *) self);
    }
}

int func_ov004_022275a0(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x43, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02227580(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x40, 0x0, 0x0);
    *(u8 *) (self + 0x8e9) = 0x0;
    return;
}

void func_ov004_02227574(int a, int b)
{
    func_ov004_022275a0((void *) a, 9, b);
    return;
}

void func_ov004_02227524(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 1) || func_02056f28(self + 0x2d0, 6) || func_02056f28(self + 0x2d0, 0xc) ||
        func_02056f28(self + 0x2d0, 0x14)) {
        func_0200f888(self);
    }
}

int func_ov004_022274c4(struct UnkStruct_022274c4 *self)
{
    int result = func_02056f94(&self->sub);
    if (result) {
        func_0200f3e8(self);
        self->handle = func_02008258(self, self->src);
        func_0200d4e8(self, 3, 1, -1);
        result = func_02073908(data_020ccf94, self->room);
        if (result) {
            result = func_0203e110();
        }
    }
    return result;
}

void func_ov004_022274a0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02227524((char *) self);
    func_ov004_0222626c(self, 0x1f, 0x6);
    func_02010d64(self);
    func_ov004_022274c4((struct UnkStruct_022274c4 *) self);
    return;
}

int func_ov004_02227468(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x44, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02227448(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x41, 0x0, 0x0);
    *(u8 *) (self + 0x8e9) = 0x0;
    return;
}

void func_ov004_0222743c(int a, int b)
{
    func_ov004_02227468((void *) a, 9, b);
    return;
}

void func_ov004_022273ec(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 1) || func_02056f28(self + 0x2d0, 6) || func_02056f28(self + 0x2d0, 0xc) ||
        func_02056f28(self + 0x2d0, 0x14)) {
        func_0200f888(self);
    }
}

int func_ov004_0222738c(struct UnkStruct_0222738c *self)
{
    int result = func_02056f94(&self->sub);
    if (result) {
        func_0200f3e8((struct UnkStruct_022274c4 *) self);
        self->handle = func_02008258((struct UnkStruct_022274c4 *) self, self->src);
        func_0200d4e8((struct UnkStruct_022274c4 *) self, 3, 1, -1);
        result = func_02073908(data_020ccf94, self->room);
        if (result) {
            result = func_0203e110();
        }
    }
    return result;
}

void func_ov004_02227368(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022273ec((char *) self);
    func_ov004_0222626c(self, 0x1f, 0x6);
    func_02010d64(self);
    func_ov004_0222738c((struct UnkStruct_0222738c *) self);
    return;
}

int func_ov004_02227324(void *self, int a, int b, int arg, short v)
{
    struct Msg m;
    int r;

    func_0200e92c((void *) (&m));
    func_0200e90c((void *) (&m), 0x7a, arg, (short) v);
    {
        struct Pair *q = &m.p;
        q->a = (u8) a;
        q->b = (u8) b;
    }
    r = func_0200e894(self, (void *) (&m));
    func_0200e91c((void *) (&m));
    return r;
}
