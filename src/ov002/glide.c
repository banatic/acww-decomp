/* glide: 43 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220a40c @ 0x0220a40c, 0x3c bytes, Thumb
 * func_ov002_0220a3e8 @ 0x0220a3e8, 0x24 bytes, Thumb
 * func_ov002_0220a3c0 @ 0x0220a3c0, 0x28 bytes, Thumb
 * func_ov002_0220a39c @ 0x0220a39c, 0x24 bytes, Thumb
 * func_ov002_0220a374 @ 0x0220a374, 0x28 bytes, Thumb
 * func_ov002_0220a314 @ 0x0220a314, 0x5e bytes, Thumb
 * func_ov002_0220a2b4 @ 0x0220a2b4, 0x60 bytes, Thumb
 * func_ov002_0220a254 @ 0x0220a254, 0x60 bytes, Thumb
 * func_ov002_0220a1dc @ 0x0220a1dc, 0x76 bytes, Thumb
 * func_ov002_0220a164 @ 0x0220a164, 0x76 bytes, Thumb
 * func_ov002_0220a0ec @ 0x0220a0ec, 0x76 bytes, Thumb
 * func_ov002_0220a0e0 @ 0x0220a0e0, 0xc bytes, Thumb
 * func_ov002_0220a0b4 @ 0x0220a0b4, 0x2a bytes, Thumb
 * func_ov002_0220a08c @ 0x0220a08c, 0x28 bytes, Thumb
 * func_ov002_0220a05c @ 0x0220a05c, 0x2e bytes, Thumb
 * func_ov002_0220a000 @ 0x0220a000, 0x5c bytes, Thumb
 * func_ov002_02209f9c @ 0x02209f9c, 0x62 bytes, Thumb
 * func_ov002_02209f70 @ 0x02209f70, 0x2c bytes, Thumb
 * func_ov002_02209f64 @ 0x02209f64, 0xc bytes, Thumb
 * func_ov002_02209f3c @ 0x02209f3c, 0x26 bytes, Thumb
 * func_ov002_02209f14 @ 0x02209f14, 0x26 bytes, Thumb
 * func_ov002_02209f00 @ 0x02209f00, 0x12 bytes, Thumb
 * func_ov002_02209eec @ 0x02209eec, 0x12 bytes, Thumb
 * func_ov002_02209eb8 @ 0x02209eb8, 0x34 bytes, Thumb
 * func_ov002_02209e50 @ 0x02209e50, 0x66 bytes, Thumb
 * func_ov002_02209e44 @ 0x02209e44, 0xc bytes, Thumb
 * func_ov002_02209e38 @ 0x02209e38, 0xc bytes, Thumb
 * func_ov002_02209e20 @ 0x02209e20, 0x18 bytes, Thumb
 * func_ov002_02209e18 @ 0x02209e18, 0x6 bytes, Thumb
 * func_ov002_02209d8c @ 0x02209d8c, 0x8c bytes, Thumb
 * func_ov002_02209d84 @ 0x02209d84, 0x6 bytes, Thumb
 * func_ov002_02209d7c @ 0x02209d7c, 0x6 bytes, Thumb
 * func_ov002_02209d74 @ 0x02209d74, 0x6 bytes, Thumb
 * func_ov002_02209d68 @ 0x02209d68, 0xa bytes, Thumb
 * func_ov002_02209d38 @ 0x02209d38, 0x30 bytes, Thumb
 * func_ov002_02209d08 @ 0x02209d08, 0x2e bytes, Thumb
 * func_ov002_02209ce8 @ 0x02209ce8, 0x20 bytes, Thumb
 * func_ov002_02209ccc @ 0x02209ccc, 0x1c bytes, Thumb
 * func_ov002_02209cb4 @ 0x02209cb4, 0x18 bytes, Thumb
 * func_ov002_02209c94 @ 0x02209c94, 0x20 bytes, Thumb
 * func_ov002_02209c78 @ 0x02209c78, 0x1c bytes, Thumb
 * func_ov002_02209c60 @ 0x02209c60, 0x18 bytes, Thumb
 * func_ov002_02209c40 @ 0x02209c40, 0x20 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0220a000 {
    u8 pad_00[0x20];
    int unk_20;
    int unk_24;
};

struct UnkStruct_02209f3c {
    char pad_00[0x20];
    int unk_20;
};

struct UnkStruct_02209f14 {
    char pad_00[0x24];
    int unk_24;
};

struct UnkStruct_02209f00 {
    char pad_00[0x20];
    int unk_20;
};

struct UnkStruct_02209eec {
    char pad_00[0x24];
    int unk_24;
};

struct UnkStruct_02209eb8 {
    char pad_00[0x20];
    int unk_20;
};

struct Anim {
    int unk_00;
    int x;
    int y;
    int dx;
    int dy;
    u8 steps;
    u8 mode;
};

struct UnkStruct_02209ce8 {
    u8 pad_00[0x14];
    u8 unk_14;
    u8 unk_15;
};

struct _Obj {
    void *vtbl;
};

struct UnkStruct_02209c78 {
    void *unk_00;
};

extern void func_0208e508(void *, int);
extern void func_0208e5cc(void *);
extern void *func_0208e8d4(void *, unsigned char parameter1);
extern void *data_ov002_0220bc88;
extern void *func_0208e7f0(void *);
extern void func_020edb3c(void *);
extern int func_0208e4bc(void *self);
extern void func_0208e594(void *p, int x, int y);
extern void func_0200467c(int command);
extern int func_0208a1cc(void *p);
extern int func_0208a1b0(void *p, int i);
extern int func_0208aef0(void *p);
extern int func_0208a198(void *p, int i);
extern int func_0208aeec(void *p);
extern void func_0208e600(void *self);
extern int func_0208e484(char *self);
extern void func_0208e5d4(char *self);
extern int data_ov002_0220bc40;
extern char data_ov002_0220bc50[];
extern int data_ov002_0220bc6c;

void func_ov002_0220a0b4(char *self, int a, int b);
int func_ov002_02209f3c(struct UnkStruct_02209f3c *self);
int func_ov002_02209f14(struct UnkStruct_02209f14 *self);
void func_ov002_02209e44(void **ptr);
void func_ov002_02209e38(void **ptr);
void func_ov002_02209e18(u8 *p);
int func_ov002_02209d8c(struct Anim *p);
int func_ov002_02209d84(int *p);
int func_ov002_02209d7c(int *p);
void func_ov002_02209d74(u8 *p);
void func_ov002_02209d68(int *p, int a, int b);
int func_ov002_02209d38(struct Anim *p, int x, int y, int steps);
void func_ov002_02209d08(char *self, int a1, int a2, int a3);
int func_ov002_02209ce8(struct UnkStruct_02209ce8 *p);

void *func_ov002_0220a40c(char *self, unsigned char arg1)
{
    // DECLS
    // ENDDECLS
    func_0208e8d4(self, arg1);
    *(void **) (self) = &data_ov002_0220bc88;
    func_ov002_02209e44((void **) (self + 0x4c));
    func_0208e508(self, 0x0);
    func_ov002_02209e18((u8 *) (self + 0x4c));
    *(void **) (self + 0x28) = 0x0;
    func_0208e5cc(self);
    return self;
}

void *func_ov002_0220a3e8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bc88;
    func_ov002_02209e38((void **) (self + 0x4c));
    func_0208e7f0(self);
    return self;
}

void *func_ov002_0220a3c0(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bc88;
    func_ov002_02209e38((void **) (self + 0x4c));
    func_0208e7f0(self);
    func_020edb3c(self);
    return self;
}

void *func_ov002_0220a39c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bc88;
    func_ov002_02209e38((void **) (self + 0x4c));
    func_0208e7f0(self);
    return self;
}

void func_ov002_0220a374(void *self, int v)
{
    if (v != func_0208e4bc(self) || v == 6 || v == 0xc) {
        func_0208e508(self, v);
    }
}

void func_ov002_0220a314(void *self)
{
    if (func_0208e4bc(self) == 1) {
        func_ov002_0220a0b4((char *) self, func_ov002_02209f3c((struct UnkStruct_02209f3c *) self) + 0x10,
                            func_ov002_02209f14((struct UnkStruct_02209f14 *) self));
    } else if (func_0208e4bc(self) == 0xd) {
        func_ov002_0220a0b4((char *) self, func_ov002_02209f3c((struct UnkStruct_02209f3c *) self) + 4,
                            func_ov002_02209f14((struct UnkStruct_02209f14 *) self) + 0x18);
    }
    func_ov002_0220a374(self, 7);
}

void func_ov002_0220a2b4(void *self)
{
    if (func_0208e4bc(self) == 7) {
        func_ov002_0220a0b4((char *) self, func_ov002_02209f3c((struct UnkStruct_02209f3c *) self) - 0x10,
                            func_ov002_02209f14((struct UnkStruct_02209f14 *) self));
    } else if (func_0208e4bc(self) == 0xd) {
        func_ov002_0220a0b4((char *) self, func_ov002_02209f3c((struct UnkStruct_02209f3c *) self) - 0xc,
                            func_ov002_02209f14((struct UnkStruct_02209f14 *) self) + 0x18);
    }
    func_ov002_0220a374(self, 1);
}

void func_ov002_0220a254(void *self)
{
    if (func_0208e4bc(self) == 1) {
        func_ov002_0220a0b4((char *) self, func_ov002_02209f3c((struct UnkStruct_02209f3c *) self) + 0xc,
                            func_ov002_02209f14((struct UnkStruct_02209f14 *) self) - 0x18);
    } else if (func_0208e4bc(self) == 7) {
        func_ov002_0220a0b4((char *) self, func_ov002_02209f3c((struct UnkStruct_02209f3c *) self) - 4,
                            func_ov002_02209f14((struct UnkStruct_02209f14 *) self) - 0x18);
    }
    func_ov002_0220a374(self, 0xd);
}

void func_ov002_0220a1dc(void *self)
{
    switch (func_0208e4bc(self)) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            func_0208e508(self, 2);
            break;
        case 7:
        case 8:
        case 9:
            func_0208e508(self, 8);
            break;
        case 13:
        case 14:
        case 15:
            func_0208e508(self, 0xe);
            break;
        case 16:
        case 17:
        case 18:
            func_0208e508(self, 0x11);
            break;
        default:
            func_0208e508(self, 8);
            break;
    }
}

void func_ov002_0220a164(void *self)
{
    switch (func_0208e4bc(self)) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            func_0208e508(self, 3);
            break;
        case 7:
        case 8:
        case 9:
            func_0208e508(self, 9);
            break;
        case 13:
        case 14:
        case 15:
            func_0208e508(self, 0xf);
            break;
        case 16:
        case 17:
        case 18:
            func_0208e508(self, 0x12);
            break;
        default:
            func_0208e508(self, 9);
            break;
    }
}

void func_ov002_0220a0ec(void *self)
{
    switch (func_0208e4bc(self)) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            func_0208e508(self, 1);
            break;
        case 7:
        case 8:
        case 9:
            func_0208e508(self, 7);
            break;
        case 13:
        case 14:
        case 15:
            func_0208e508(self, 0xd);
            break;
        case 16:
        case 17:
        case 18:
            func_0208e508(self, 0x10);
            break;
        default:
            func_0208e508(self, 9);
            break;
    }
}

void func_ov002_0220a0e0(void *p, int x, int y)
{
    func_0208e594(p, x - 0x80, y - 0x60);
}

void func_ov002_0220a0b4(char *self, int a, int b)
{
    func_ov002_02209d74((u8 *) (self + 0x4c));
    func_ov002_02209d68((int *) (self + 0x4c), a, b);
    func_ov002_0220a0e0((void *) self, a, b);
}

int func_ov002_0220a08c(char *self, int a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    func_0200467c(0xb);
    return func_ov002_02209d38((struct Anim *) (self + 0x4c), a1, a2, a3);
}

void func_ov002_0220a05c(char *self, int a, int b, int c, int flag)
{
    if (flag) {
        func_0200467c(0xb);
    }
    self += 0x4c;
    func_ov002_02209d08(self, a, b, c);
}

void func_ov002_0220a000(struct UnkStruct_0220a000 *self, int x, int y, int a, u8 b)
{
    int t;
    int u;

    t = x - (self->unk_20 + func_0208aef0((void *) self));
    func_0200467c(0xb);
    if (t >= -0x30 && t <= 0x30) {
        u = y - (self->unk_24 + func_0208aeec((void *) self));
        if (u >= -0x30 && u <= 0x30) {
            a = b;
        }
    }
    func_ov002_02209d08((char *) self + 0x4c, x, y, a);
}

int func_ov002_02209f9c(char *self)
{
    switch (func_0208e4bc(self)) {
        case 4:
        case 10:
            self += 0xc;
            if (func_0208a1cc(self) >= 4) {
                return 1;
            } else {
                return 0;
            }
        case 5:
        case 11:
            self += 0xc;
            if (func_0208a1cc(self) < 3) {
                return 1;
            } else {
                return 0;
            }
        case 6:
        case 12:
            return 1;
    }
    return 0;
}

int func_ov002_02209f70(char *self)
{
    int t = func_0208e4bc(self);

    if (t == 6 || t == 0xc) {
        self += 0xc;
        if (func_0208a1cc(self) == 2) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

int func_ov002_02209f64(char *self)
{
    // DECLS
    // ENDDECLS
    return func_ov002_02209ce8((struct UnkStruct_02209ce8 *) (self + 0x4c));
}

int func_ov002_02209f3c(struct UnkStruct_02209f3c *self)
{
    int a = func_0208a1b0((char *) self + 0xc, -1);
    int b = func_0208aef0(self);

    return a + (self->unk_20 + b);
}

int func_ov002_02209f14(struct UnkStruct_02209f14 *self)
{
    int a = func_0208a198((char *) self + 0xc, -1);
    int b = func_0208aeec(self);

    return a + (self->unk_24 + b);
}

int func_ov002_02209f00(struct UnkStruct_02209f00 *p)
{
    int r = func_0208aef0(p);
    return p->unk_20 + r;
}

int func_ov002_02209eec(struct UnkStruct_02209eec *p)
{
    int r = func_0208aeec(p);
    return p->unk_24 + r;
}

void func_ov002_02209eb8(struct UnkStruct_02209eb8 *self)
{
    int save;

    func_0208e600(self);
    save = self->unk_20;
    if (save + func_0208aef0(self) > 0xe0) {
        self->unk_20 = self->unk_20 - 0x100;
        func_0208e600(self);
        self->unk_20 = save;
    }
}

void func_ov002_02209e50(char *self)
{
    int a;
    int b;

    func_ov002_02209d8c((struct Anim *) (self + 0x4c));
    a = func_ov002_02209d84((int *) (self + 0x4c));
    b = func_ov002_02209d7c((int *) (self + 0x4c));
    func_ov002_0220a0e0((void *) self, a, b);
    if (func_0208e484(self)) {
        if (func_0208e4bc((void *) self) == 5) {
            func_0208e508((void *) self, 1);
        } else if (func_0208e4bc((void *) self) == 0xb) {
            func_0208e508((void *) self, 7);
        }
    }
    func_0208e5d4(self);
}

void func_ov002_02209e44(void **ptr)
{
    *ptr = &data_ov002_0220bc40;
}

void func_ov002_02209e38(void **ptr)
{
    *ptr = &data_ov002_0220bc40;
}

void *func_ov002_02209e20(void *arg)
{
    *((void **) arg) = &data_ov002_0220bc40;
    func_020edb3c(arg);
    return arg;
}

void func_ov002_02209e18(u8 *p)
{
    p[0x15] = 0;
}

int func_ov002_02209d8c(struct Anim *p)
{
    if (p->mode != 2 && p->mode != 3) {
        return 1;
    }
    if (p->steps != 0) {
        p->steps = p->steps - 1;
        switch (p->mode) {
            case 2:
                p->x += p->dx;
                p->y += p->dy;
                break;
            case 3:
                p->x += p->dx;
                p->y += p->dy;
                if (p->steps > 1) {
                    p->dx = p->dx >> 1;
                    p->dy = p->dy >> 1;
                }
                break;
        }
        while (p->x < 0) {
            p->x += 0x1000;
        }
        while (p->x > 0x1000) {
            p->x -= 0x1000;
        }
    }
    if (p->steps == 0) {
        return 1;
    }
    return 0;
}

int func_ov002_02209d84(int *p)
{
    return p[1] >> 4;
}

int func_ov002_02209d7c(int *p)
{
    return p[2] >> 4;
}

void func_ov002_02209d74(u8 *p)
{
    p[0x15] = 1;
}

void func_ov002_02209d68(int *p, int a, int b)
{
    p[1] = a << 4;
    p[2] = b << 4;
}

int func_ov002_02209d38(struct Anim *p, int x, int y, int steps)
{
    int result;
    p->mode = 2;
    p->dx = ((x << 4) - p->x) / steps;
    result = ((y << 4) - p->y) / steps;
    p->dy = result;
    p->steps = steps;
    return result;
}

void func_ov002_02209d08(char *self, int a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    if (a3 == 0x1) {
        func_ov002_02209d38((struct Anim *) self, a1, a2, 0x1);
    } else {
        *(u8 *) (self + 0x15) = 0x3;
        *(int *) (self + 0xc) = (((a1 << 4) - *(int *) (self + 0x4)) >> 1);
        *(int *) (self + 0x10) = (((a2 << 4) - *(int *) (self + 0x8)) >> 1);
        *(u8 *) (self + 0x14) = a3;
    }
}

int func_ov002_02209ce8(struct UnkStruct_02209ce8 *p)
{
    return (p->unk_15 == 2 || p->unk_15 == 3) && p->unk_14 != 0;
}

void *func_ov002_02209ccc(void *self)
{
    func_ov002_0220a40c((char *) self, 0);
    *(char **) self = data_ov002_0220bc50;
    return self;
}

void *func_ov002_02209cb4(void *arg)
{
    *((void **) arg) = ((int *) data_ov002_0220bc50);
    func_ov002_0220a39c((char *) arg);
    return arg;
}

void *func_ov002_02209c94(struct _Obj *obj)
{
    obj->vtbl = ((char *) data_ov002_0220bc50);
    func_ov002_0220a39c((char *) obj);
    func_020edb3c(obj);
    return obj;
}

struct UnkStruct_02209c78 *func_ov002_02209c78(struct UnkStruct_02209c78 *obj)
{
    func_ov002_0220a40c((char *) obj, 1);
    obj->unk_00 = &data_ov002_0220bc6c;
    return obj;
}

void *func_ov002_02209c60(void *arg)
{
    *((void **) arg) = &data_ov002_0220bc6c;
    func_ov002_0220a39c((char *) arg);
    return arg;
}

void *func_ov002_02209c40(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bc6c);
    func_ov002_0220a39c((char *) obj);
    func_020edb3c(obj);
    return obj;
}
