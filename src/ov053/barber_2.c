/* barber_2: 22 functions, module ov053
 * mwccarm 1.2/base -O4,s
 * func_ov053_022614f8 @ 0x022614f8, 0x1c bytes, Thumb
 * func_ov053_022614e4 @ 0x022614e4, 0x12 bytes, Thumb
 * func_ov053_022614b0 @ 0x022614b0, 0x34 bytes, Thumb
 * func_ov053_02261484 @ 0x02261484, 0x2c bytes, Thumb
 * func_ov053_022613b0 @ 0x022613b0, 0xd4 bytes, Thumb
 * func_ov053_022612a4 @ 0x022612a4, 0x10c bytes, Thumb
 * func_ov053_022612a0 @ 0x022612a0, 0x4 bytes, Thumb
 * func_ov053_0226129c @ 0x0226129c, 0x4 bytes, Thumb
 * func_ov053_02261260 @ 0x02261260, 0x3c bytes, Thumb
 * func_ov053_02261230 @ 0x02261230, 0x30 bytes, Thumb
 * func_ov053_022611ec @ 0x022611ec, 0x44 bytes, Thumb
 * func_ov053_022610f0 @ 0x022610f0, 0xfc bytes, Thumb
 * func_ov053_02261090 @ 0x02261090, 0x60 bytes, Thumb
 * func_ov053_02260f94 @ 0x02260f94, 0xfc bytes, Thumb
 * func_ov053_02260f20 @ 0x02260f20, 0x74 bytes, Thumb
 * func_ov053_02260dfc @ 0x02260dfc, 0x124 bytes, Thumb
 * func_ov053_02260dc4 @ 0x02260dc4, 0x38 bytes, Thumb
 * func_ov053_02260d00 @ 0x02260d00, 0xc4 bytes, Thumb
 * func_ov053_02260cf0 @ 0x02260cf0, 0x10 bytes, Thumb
 * func_ov053_02260c34 @ 0x02260c34, 0xbc bytes, Thumb
 * func_ov053_02260c30 @ 0x02260c30, 0x4 bytes, Thumb
 * func_ov053_02260c2c @ 0x02260c2c, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    Vec3 pos;
    char pad_68[0x3b0 - 0x68];
    char unk_3B0;
    char pad_3B1[0x618 - 0x3b1];
    char unk_618;
    char pad_619[0x658 - 0x619];
    char unk_658;
    char pad_659[0x71b - 0x659];
    u8 unk_71B;
} UnkStruct_022613b0;

typedef struct {
    char pad_00[0x618];
    char unk_618;
    char pad_619[0x654 - 0x619];
    int unk_654;
    char unk_658;
    char pad_659[0x71b - 0x659];
    char unk_71B;
} UnkStruct_022612a4;

struct UnkStruct_02261260 {
    unsigned char pad_00[0x71c];
    short unk_71C;
};

typedef struct {
    int a, b, c;
} Entry12;

typedef struct {
    int a, b, c;
} Vec3_02261090;

typedef struct {
    int unk_00;
    int w1;
    int w2;
} Entry;

typedef struct {
    unsigned char pad_00[0x350];
    int unk_350;
    unsigned char pad_354[0x214 - 4];
    int unk_564;
    unsigned char pad_568[0x1b5 - 4];
    unsigned char unk_719;
} UnkStruct_02260dfc;

typedef struct {
    char pad_00[0x564];
    char unk_564[0x1b6];
    unsigned char unk_71A;
} UnkStruct_02260dc4;

struct s_ov053 {
    char pad_00[0x718];
    char unk_718;
};

extern int func_0203e0a8(void *a, int b);
extern unsigned short data_020c80f8;
extern int func_ov053_02260558(int);
extern int func_ov053_02260504(int);
extern int func_ov053_022604bc(int);
extern char data_021fbee8[];
extern int data_020c814c;
extern void func_0201ad18(void *p, int a, int b, int c, void *d, int e, int f, int g);
extern int func_02016104(void *p);
extern int func_0201c314(UnkStruct_022613b0 *self, int a);
extern int func_ov053_02260ba8(void *p);
extern int func_ov004_0224719c(Vec3 *v);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_020e8858(void *p);
extern void func_02035624(int a);
extern int func_02014868(void *p);
extern void func_0208b514(unsigned int context);
extern int func_ov053_02260488(void *receiver);
extern void func_ov053_02260bb0(void *p, int a);
extern int func_020960f8(int a, int b);
extern int func_ov004_0222c070(int a);
extern int func_0203e020(UnkStruct_022612a4 *self);
extern void *func_020b5e10(void);
extern int func_020b6098(void *h, int a);
extern int func_0203b144(void);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov053_02261524(void *, int);
extern void func_0201b044(void *p, Entry12 *e);
extern Entry12 data_ov053_022617fc[];
extern Entry12 data_ov053_02261804[];
extern int func_0200322c(void *dst, Vec3_02261090 *src);
extern Entry12 data_ov053_02261814[];
extern Entry12 data_ov053_0226181c[];
extern int func_02019c20(void *p, int a, int b, int c, int d, int e);
extern unsigned char func_ov053_02261514(void *ptr);
extern unsigned char func_ov053_0226151c(void *ptr);
extern int func_ov004_0222bf20(void *ptr1, void *ptr2);
extern int func_ov004_0222c8c8(void);
extern int func_0200442c(void *ptr, int a, int b, int c);
extern int func_02016884(void *ptr, int a, void *ptr2);
extern int func_020984e8(void);
extern const int *func_02095794(int);
extern void func_0204f818(int *a, int *b, const int *c);
extern int func_02095ab0(void *dst, int val, int size);
extern void *func_0209615c(unsigned int size);
extern const int data_ov053_022617d4[3];

int func_ov053_022614f8(int x)
{
    func_ov053_02260bb0((void *) (x + 0x658), 0);
    return 1;
}

int func_ov053_022614e4(void *a)
{
    func_0203e0a8(a, 0);
    return 1;
}

int func_ov053_022614b0(char *p)
{
    func_02019d0c((void *) (p + 0x564), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov053_02261484(int r0)
{
    int r4 = r0;
    if (func_ov053_02260558(r4) != 0) {
        return 1;
    }
    if (func_ov053_02260504(r4) != 0) {
        return 1;
    }
    func_ov053_022604bc(r4);
    return 1;
}

int func_ov053_022613b0(UnkStruct_022613b0 *self)
{
    Vec3 v;
    Vec3 *q;
    int n;
    int x;

    func_0201ad18(&self->unk_3B0, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    x = func_02016104(&self->unk_658);
    n = 0;
    if (x != 0) {
        n = func_0201c314(self, x);
    }
    if (func_ov053_02260ba8(&self->unk_658) == 5) {
        q = &self->pos;
        v.x = q->x;
        v.y = q->y;
        v.z = q->z;
        v.y = v.y + 0x2000;
        func_ov004_0224719c(&v);
        self->unk_71B = 0x1f;
    }
    if (func_ov053_02260ba8(&self->unk_658) == 5 || func_ov053_02260ba8(&self->unk_658) == 8 ||
        func_ov053_02260ba8(&self->unk_658) == 0xa) {
        func_020147fc(&self->unk_618, 0, n, 1);
        return 1;
    }
    func_020147fc(&self->unk_618, 0, n, 0);
    return 1;
}

int func_ov053_022612a4(UnkStruct_022612a4 *self)
{
    int old;

    if (func_020e8858(&self->unk_71B) == 1) {
        func_02035624(0xe);
    }
    if (func_02014868(&self->unk_618) == 0) {
        old = self->unk_654;
        func_0208b514(0x654);
        if (func_ov053_02260ba8(&self->unk_658) == 4 || func_ov053_02260ba8(&self->unk_658) == 3) {
            func_ov053_02261524((void *) self, 7);
        } else if (func_ov053_02260ba8(&self->unk_658) == 5 && func_ov053_02260488(self) != 0) {
            func_ov053_02260bb0(&self->unk_658, 9);
            func_ov053_02261524((void *) self, 6);
            return 1;
        } else if (func_020960f8(0x28, 4) != 0) {
            if (func_ov004_0222c070(0) != 0) {
                func_0203e020(self);
                func_ov053_02261524((void *) self, 3);
            }
        } else if (func_ov053_02260ba8(&self->unk_658) == 0xa) {
            if (func_02014868(&self->unk_618) == 0) {
                func_020b6098(func_020b5e10(), 0);
                func_ov053_02261524((void *) self, 3);
            }
        } else {
            func_0203e020(self);
            func_ov053_02261524((void *) self, 3);
        }
        if (old != self->unk_654 && func_ov053_02260ba8(&self->unk_658) == 5) {
            func_0203b144();
        }
    }
    return 1;
}

int func_ov053_022612a0(void)
{
    return 1;
}

int func_ov053_0226129c(void)
{
    return 1;
}

int func_ov053_02261260(struct UnkStruct_02261260 *obj)
{
    func_02019d0c((char *) obj + 0x564, 3, 1, 0, 0, 0, obj->unk_71C, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov053_02261230(void *arg)
{
    if (func_02019e00((char *) arg + 0x564) == 3) {
        if (func_02019de8((char *) arg + 0x564) != 0) {
            func_ov053_02261524(arg, 1);
        }
    }
    return 1;
}

int func_ov053_022611ec(unsigned char *base)
{
    base[0x719] = 0;
    func_02019d0c(base + 0x564, 3, 1, 0, 0, 0, 0x4000, 0, 0, (unsigned short) ((unsigned short) data_020c80f8), 0);
    return 1;
}

int func_ov053_022610f0(void *self)
{
    u8 *p = (u8 *) self;
    Entry12 buf;
    Entry12 *src;
    int idx, t1, t2;

    if (func_02019e00(p + 0x564) == 6) {
        idx = p[0x719];
        src = &data_ov053_022617fc[idx];
        buf.a = src->a;
        buf.b = src->b;
        buf.c = src->c;
        func_0201b044(p + 0x350, &buf);
        if (func_02019de8(p + 0x564) != 0) {
            p[0x719] = p[0x719] + 1;
            idx = p[0x719];
            t2 = data_ov053_02261804[idx].a;
            t1 = data_ov053_022617fc[idx].a;
            func_02019d0c(p + 0x564, 6, 1, t1, t2, 0x800, 0, 0, 0, (u16) ((*(u16 *) &data_020c80f8)), 0);
            if (p[0x719] >= 2) {
                func_ov053_02261524(self, 4);
            }
        }
    }

    if (func_02019e00(p + 0x564) == 3) {
        if (func_02019de8(p + 0x564) != 0) {
            idx = p[0x719];
            t2 = data_ov053_02261804[idx].a;
            t1 = data_ov053_022617fc[idx].a;
            func_02019d0c(p + 0x564, 6, 1, t1, t2, 0x800, 0, 0, 0, (u16) ((*(u16 *) &data_020c80f8)), 0);
        }
    }

    return 1;
}

int func_ov053_02261090(char *p)
{
    Vec3_02261090 local;
    int ret;

    *(unsigned char *) (p + 0x719) = 0;
    local.a = (*(Vec3_02261090 *) data_ov053_02261814).a;
    local.b = (*(Vec3_02261090 *) data_ov053_02261814).b;
    local.c = (*(Vec3_02261090 *) data_ov053_02261814).c;
    ret = func_0200322c(p + 0x5c, &local);
    func_02019d0c(p + 0x564, 3, 1, 0, 0, 0, ret, 0, 0, (int) data_020c80f8, 0);
    return 1;
}

int func_ov053_02260f94(void *self)
{
    u8 *p = (u8 *) self;
    Entry12 buf;
    Entry12 *src;
    int idx, t1, t2;

    if (func_02019e00(p + 0x564) == 6) {
        idx = p[0x719];
        src = &data_ov053_02261814[idx];
        buf.a = src->a;
        buf.b = src->b;
        buf.c = src->c;
        func_0201b044(p + 0x350, &buf);
        if (func_02019de8(p + 0x564) != 0) {
            p[0x719] = p[0x719] + 1;
            idx = p[0x719];
            t2 = data_ov053_0226181c[idx].a;
            t1 = data_ov053_02261814[idx].a;
            func_02019d0c(p + 0x564, 6, 1, t1, t2, 0x800, 0, 0, 0, (u16) ((*(u16 *) &data_020c80f8)), 0);
            if (p[0x719] >= 2) {
                func_ov053_02261524(self, 2);
            }
        }
    }

    if (func_02019e00(p + 0x564) == 3) {
        if (func_02019de8(p + 0x564) != 0) {
            idx = p[0x719];
            t2 = data_ov053_0226181c[idx].a;
            t1 = data_ov053_02261814[idx].a;
            func_02019d0c(p + 0x564, 6, 1, t1, t2, 0x800, 0, 0, 0, (u16) ((*(u16 *) &data_020c80f8)), 0);
        }
    }

    return 1;
}

int func_ov053_02260f20(char *param)
{
    func_0201ad18((void *) (param + 0x3b0), 0, 0, 0, (void *) ((int) ((char *) data_021fbee8)), 4,
                  (*(unsigned int *) &data_020c814c), 1);
    *((unsigned char *) (param + 0x719)) = 0;
    func_02019d0c((void *) (param + 0x564), 3, 1, 0, 0, 0, 0x4000, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov053_02260dfc(UnkStruct_02260dfc *p)
{
    int tmp[3];
    Entry *e;
    unsigned short val;

    if (func_02019e00((char *) p + 0x564) == 6) {
        e = &((Entry *) data_ov053_022617fc)[p->unk_719];
        tmp[0] = e->unk_00;
        tmp[1] = e->w1;
        tmp[2] = e->w2;
        func_0201b044((char *) p + 0x350, (Entry12 *) tmp);
        if (func_02019de8((char *) p + 0x564)) {
            p->unk_719++;
            val = (*(volatile unsigned short *) &data_020c80f8);
            func_02019d0c((char *) p + 0x564, 6, 1, ((Entry *) data_ov053_022617fc)[p->unk_719].unk_00,
                          ((Entry *) data_ov053_02261804)[p->unk_719].unk_00, 0x800, 0, 0, 0,
                          (*(volatile unsigned short *) &data_020c80f8), 0);
            if (p->unk_719 >= 2) {
                func_02019d0c((char *) p + 0x564, 3, 1, 0, 0, 0, 0xffffc000, 0, 0, val, 0);
            }
        }
    }

    if (func_02019e00((char *) p + 0x564) == 3) {
        if (func_02019de8((char *) p + 0x564)) {
            if (p->unk_719 >= 2) {
                func_ov053_02261524(p, 8);
            } else {
                func_02019d0c((char *) p + 0x564, 6, 1, ((Entry *) data_ov053_022617fc)[p->unk_719].unk_00,
                              ((Entry *) data_ov053_02261804)[p->unk_719].unk_00, 0x800, 0, 0, 0,
                              (*(volatile unsigned short *) &data_020c80f8), 0);
            }
        }
    }

    return 1;
}

int func_ov053_02260dc4(UnkStruct_02260dc4 *obj)
{
    unsigned short val;
    int param;

    obj->unk_71A = 100;
    val = data_020c80f8;
    param = 1;

    func_02019c20(obj->unk_564, param, 0xf1, param, val, 0);
    return 1;
}

int func_ov053_02260d00(void *self)
{
    if (func_020e8858(((char *) self) + 0x71a) == 0) {
        func_ov053_02260bb0(((char *) self) + 0x658, 5);
        func_ov053_02261524(self, 2);
    }
    if ((*((unsigned char *) (((char *) self) + 0x71a))) == 0x55) {
        unsigned char pair[2];
        pair[1] = func_ov053_02261514(((char *) self) + 0x658);
        pair[0] = func_ov053_0226151c(((char *) self) + 0x658);

        (void) ((void *) func_ov004_0222bf20(&pair[0], &pair[1]));
        func_ov004_0222c8c8();
        func_0200442c(((char *) self) + 0x514, 0x41, 0x7f, 0);
    }
    if (func_02016884(((char *) self) + 0x334, 0xf1, ((char *) self) + 0x2a0)) {
        if (func_02019de8(((char *) self) + 0x564)) {
            func_02019d0c(((char *) self) + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }
    return 1;
}

int func_ov053_02260cf0(struct s_ov053 *self)
{
    self->unk_718 = 0;
    return 1;
}

int func_ov053_02260c34(unsigned char *self)
{
    int z[4];
    int data[3];
    int gdata[3];
    int tmp[3];
    int a, b, c;

    func_020984e8();
    {
        const int *p = func_02095794(4);
        data[0] = p[0];
        data[1] = p[1];
        data[2] = p[2];
    }
    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    z[3] = 0;

    a = data_ov053_022617d4[0];
    gdata[0] = a;
    b = data_ov053_022617d4[1];
    gdata[1] = b;
    c = data_ov053_022617d4[2];
    gdata[2] = c;

    func_0204f818(&z[2], &z[3], gdata);
    func_0204f818(&z[0], &z[1], data);

    switch (self[0x718]) {
        case 0:
            if (func_02014868(self + 0x618) == 0) {
                func_0203b144();
                self[0x718] = 1;
            }
            break;
        case 1:
            tmp[0] = a;
            tmp[1] = b;
            tmp[2] = c;
            func_02095ab0(tmp, 0x266, 4);
            self[0x718] = 2;
            break;
        case 2:
            if (func_0209615c(4) == 0) {
                func_0203e020((UnkStruct_022612a4 *) self);
                func_ov053_02261524((void *) self, 4);
            }
            break;
        default:
            break;
    }
    return 1;
}

int func_ov053_02260c30(void)
{
    return 1;
}

int func_ov053_02260c2c(void)
{
    return 1;
}
