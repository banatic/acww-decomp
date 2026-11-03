/* cell_layer_sprite: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208e878 @ 0x0208e878, 0x5c bytes, Thumb
 * func_0208e84c @ 0x0208e84c, 0x2c bytes, Thumb
 * func_0208e81c @ 0x0208e81c, 0x30 bytes, Thumb
 * func_0208e7f0 @ 0x0208e7f0, 0x2c bytes, Thumb
 * func_0208e600 @ 0x0208e600, 0x1f0 bytes, Thumb
 * func_0208e5d4 @ 0x0208e5d4, 0x2a bytes, Thumb
 * func_0208e5cc @ 0x0208e5cc, 0x8 bytes, Thumb
 * func_0208e5c4 @ 0x0208e5c4, 0x8 bytes, Thumb
 * func_0208e594 @ 0x0208e594, 0x30 bytes, Thumb
 * func_0208e508 @ 0x0208e508, 0x8c bytes, Thumb
 * func_0208e4c0 @ 0x0208e4c0, 0x48 bytes, Thumb
 * func_0208e4bc @ 0x0208e4bc, 0x4 bytes, Thumb
 * func_0208e484 @ 0x0208e484, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    unsigned char pad_04[8];
    unsigned char unk_0C[0x20];
    unsigned char unk_2C[4];
} UnkStruct_0208e84c;

typedef struct {
    void *vtbl;
    char pad_04[8];
    int sub1;
    char pad_10[28];
    int sub2;
} UnkStruct_0208e81c;

typedef struct SubObject {
    char data[0x20];
} SubObject;

typedef struct MyObject {
    void *vtable;
    char pad_04[8];
    SubObject sub1;
    SubObject sub2;
} MyObject;

typedef struct {
    u8 pad_00[0x0c];
    u8 unk_0C[0x20 - 0x0c];
    int unk_20;
    int unk_24;
    int unk_28;
    u8 unk_2C[0x40 - 0x2c];
    int unk_40;
    u8 pad_44[0x48 - 0x44];
    u8 unk_48;
    u8 unk_49;
    u8 unk_4A;
} UnkStruct_0208e600;

typedef struct {
    char pad_00[0x20];
    int unk_20;
    int unk_24;
    char pad_28[0x18];
    int unk_40;
} UnkStruct_0208e594;

typedef struct {
    u8 pad_00[0xc];
    u32 sub0;
    u8 pad_10[0x2c - 0xc - 4];
    u32 sub1;
    u8 pad_30[0x40 - 0x2c - 4];
    u32 unk_40;
    u8 pad_44[0x49 - 0x44];
    volatile u8 unk_49;
} Parent;

/* Constructor-style function; returns self after initialisation.
   Twin of func_0208e8d4 (identical structure, different address). */

extern void func_0208af30(void *self);
extern void func_0208a1f8(void *self);
extern unsigned char data_020e2314[];
extern void func_0208a1f4(void *);
extern void func_0208af00(UnkStruct_0208e84c *);
extern void func_020edb3c(void *self);
extern void *func_0208a1d0(void *p);
extern short func_0208a1b0(void *p, int n);
extern short func_0208a198(void *p, int n);
extern int func_0208aef0(UnkStruct_0208e600 *s);
extern int func_0208aeec(UnkStruct_0208e600 *s);
extern void func_02088df8(int m, void *h, int a, int b, int c, int d, int e, int g, int i, int j, int k, int l);
extern void func_0208a0c8(void *);
extern void func_020041bc(unsigned char c);
extern u32 data_020d0b08[];
extern u8 data_020d0af4[];
extern u8 data_020d0ae0[];
extern u64 data_020d6fcc[];
extern void func_0208a1f0(void *obj, void *data);
extern void func_0208a1ec(void *obj, int flag);
extern void *func_0208a144(void *obj);
extern void *func_0208a1c8(void *);
extern void *func_0208a1e0(void *, int, int);
extern int func_0208a160(void *);

void func_0208e508(Parent *self, int idx);

void *func_0208e878(void *self, u8 a)
{
    func_0208af30(self);
    *(u32 *) ((char *) self + 0) = (unsigned int) data_020e2314;
    func_0208a1f8((char *) self + 0xc);
    *(u32 *) ((char *) self + 0x20) = 0;
    *(u32 *) ((char *) self + 0x24) = 0;
    *(u32 *) ((char *) self + 0x28) = -1;
    func_0208a1f8((char *) self + 0x2c);
    *(u32 *) ((char *) self + 0x40) = 0;
    *(u32 *) ((char *) self + 0x44) = 0x16;
    *(u8 *) ((char *) self + 0x48) = a;
    *(u8 *) ((char *) self + 0x49) = 1;
    *(u8 *) ((char *) self + 0x4a) = 0;
    func_0208e508((Parent *) self, 0);
    return self;
}

UnkStruct_0208e84c *func_0208e84c(UnkStruct_0208e84c *obj)
{
    obj->unk_00 = ((int *) data_020e2314);
    func_0208a1f4(obj->unk_2C);
    func_0208a1f4(obj->unk_0C);
    func_0208af00(obj);
    return obj;
}

UnkStruct_0208e81c *func_0208e81c(UnkStruct_0208e81c *self)
{
    self->vtbl = (void *) data_020e2314;
    func_0208a1f4(&self->sub2);
    func_0208a1f4(&self->sub1);
    func_0208af00((UnkStruct_0208e84c *) self);
    func_020edb3c(self);
    return self;
}

MyObject *func_0208e7f0(MyObject *obj)
{
    obj->vtable = (void *) data_020e2314;
    func_0208a1f4(&obj->sub2);
    func_0208a1f4(&obj->sub1);
    func_0208af00((UnkStruct_0208e84c *) obj);
    return obj;
}

void func_0208e600(UnkStruct_0208e600 *self)
{
    // DECLS
    int t30;
    void *x;
    int t2c;
    unsigned int ax;
    int py;
    int dx;
    int bx;
    int t7;
    int t34;
    int px;
    int cx;
    void *y;
    // ENDDECLS

    if (self->unk_40 == 0) {
        return;
    }

    x = func_0208a1d0(self->unk_0C);
    if (self->unk_49 != 0) {
        y = func_0208a1d0(self->unk_2C);
    } else {
        y = 0;
    }

    t7 = func_0208a1b0(self->unk_0C, -1);
    t2c = func_0208a198(self->unk_0C, -1);
    t30 = func_0208a1b0(self->unk_2C, -1);
    t34 = func_0208a198(self->unk_2C, -1);

    px = (int) ((char *) 0 + (self->unk_20 + func_0208aef0(self)));
    py = (int) ((char *) 0 + (self->unk_24 + func_0208aeec(self)));

    ax = px + t7;
    bx = py + t2c;
    cx = px + t30;
    dx = py + t34;

    if (self->unk_48 != 0) {
        func_02088df8(0, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        if (y != 0) {
            func_02088df8(0, y, cx, (py + t34), -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_4A != 0) {
            func_02088df8(0, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            if (y != 0) {
                func_02088df8(0, y, cx, dx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    } else {
        func_02088df8(1, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        if (y != 0) {
            func_02088df8(1, y, cx, dx, -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_4A != 0) {
            func_02088df8(1, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            if (y != 0) {
                func_02088df8(1, y, cx, dx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    }
}

void func_0208e5d4(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x40) != 0) {
        func_0208a0c8((char *) arg0 + 0xc);
        if (*(unsigned char *) ((char *) arg0 + 0x49) != 0) {
            func_0208a0c8((char *) arg0 + 0x2c);
        }
    }
}

void func_0208e5cc(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (74))) + (0)) = 1;
}

void func_0208e5c4(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (74))) + (0)) = 0;
}

void func_0208e594(UnkStruct_0208e594 *self, int a, int b)
{
    self->unk_20 = a;
    self->unk_24 = b;
    if (self->unk_40 != 0) {
        int value;
        value = func_0208aef0((UnkStruct_0208e600 *) self) + self->unk_20;
        if (value < 0) {
            value = 0;
        }
        if (value > 0xff) {
            value = 0xff;
        }
        func_020041bc((unsigned char) value);
    }
}

void func_0208e508(Parent *self, int idx)
{
    u32 word = data_020d0b08[idx];
    u32 word_plus_1 = word + 1;
    u8 byte_val = data_020d0af4[idx];
    int flag;

    switch (byte_val) {
        default:
            flag = 0;
            break;
        case 0:
            flag = 1;
            break;
    }

    self->unk_40 = idx;

    func_0208a1f0(&self->sub0, &data_020d6fcc[word]);
    func_0208a1ec(&self->sub0, flag);
    func_0208a144(&self->sub0);

    self->unk_49 = data_020d0ae0[idx];
    if (self->unk_49 != 0) {
        func_0208a1f0(&self->sub1, &data_020d6fcc[word_plus_1]);
        func_0208a1ec(&self->sub1, flag);
        func_0208a144(&self->sub1);
    }
}

void func_0208e4c0(void *arg, int argument1)
{
    void *ret;
    void *ret2;

    func_0208e508((Parent *) arg, (int) argument1);
    ret = func_0208a1c8((char *) arg + 0xc);
    func_0208a1e0((char *) arg + 0xc, ((int *) ret)[1] - 1, 0);
    if (*((unsigned char *) arg + 0x49) != 0) {
        ret2 = func_0208a1c8((char *) arg + 0x2c);
        func_0208a1e0((char *) arg + 0x2c, ((int *) ret2)[1] - 1, 0);
    }
}

int func_0208e4bc(int *p0)
{
    return p0[16];
}

int func_0208e484(void *arg)
{
    int ret = 0;
    int cond;
    if (func_0208a160((char *) arg + 0xC) != 0) {
        if (((unsigned char *) arg)[0x49] != 0) {
            cond = func_0208a160((char *) arg + 0x2C);
        } else {
            cond = 1;
        }
        if (cond != 0) {
            ret = 1;
        }
    }
    return ret;
}
