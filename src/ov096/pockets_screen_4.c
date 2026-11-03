/* pockets_screen_4: 20 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229dc08 @ 0x0229dc08, 0x20 bytes, Thumb
 * func_ov096_0229dbe8 @ 0x0229dbe8, 0x20 bytes, Thumb
 * func_ov096_0229dbc0 @ 0x0229dbc0, 0x28 bytes, Thumb
 * func_ov096_0229db78 @ 0x0229db78, 0x48 bytes, Thumb
 * func_ov096_0229db30 @ 0x0229db30, 0x48 bytes, Thumb
 * func_ov096_0229daec @ 0x0229daec, 0x44 bytes, Thumb
 * func_ov096_0229da6c @ 0x0229da6c, 0x80 bytes, Thumb
 * func_ov096_0229d9f0 @ 0x0229d9f0, 0x7c bytes, Thumb
 * func_ov096_0229d9cc @ 0x0229d9cc, 0x24 bytes, Thumb
 * func_ov096_0229d9a0 @ 0x0229d9a0, 0x2a bytes, Thumb
 * func_ov096_0229d93c @ 0x0229d93c, 0x64 bytes, Thumb
 * func_ov096_0229d8ec @ 0x0229d8ec, 0x50 bytes, Thumb
 * func_ov096_0229d8bc @ 0x0229d8bc, 0x30 bytes, Thumb
 * func_ov096_0229d878 @ 0x0229d878, 0x42 bytes, Thumb
 * func_ov096_0229d7d0 @ 0x0229d7d0, 0xa8 bytes, Thumb
 * func_ov096_0229d6dc @ 0x0229d6dc, 0xf4 bytes, Thumb
 * func_ov096_0229d664 @ 0x0229d664, 0x78 bytes, Thumb
 * func_ov096_0229d5f4 @ 0x0229d5f4, 0x70 bytes, Thumb
 * func_ov096_0229d5ec @ 0x0229d5ec, 0x8 bytes, Thumb
 * func_ov096_0229d5d4 @ 0x0229d5d4, 0x16 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229da6c {
    u8 pad_00[0xc4];
    int unk_C4;
} UnkStruct_0229da6c;

typedef struct UnkStruct_0229da6c_2 {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_0229da6c_2;

typedef struct UnkStruct_0229d9f0 {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char pad_B7[0x358 - 0xb7];
    char unk_358;
} UnkStruct_0229d9f0;

typedef struct {
    char pad_00[0xB6];
    unsigned char unk_B6;
} UnkStruct_0229d93c;

typedef struct {
    char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char unk_B7;
    unsigned char unk_B8;
} UnkStruct_0229d8ec;

typedef struct {
    char pad_00[0xb8];
    unsigned char b8;
} UnkStruct_0229d878;

typedef struct UnkStruct_0229d7d0 {
    char pad_00[0xbb];
    u8 unk_BB;
} UnkStruct_0229d7d0;

typedef struct {
    char pad_00[0xac];
    u16 unk_AC;
    char pad_AE[0xb4 - 0xae];
    u8 unk_B4;
    char pad_B5[0xbb - 0xb5];
    u8 unk_BB;
    char pad_BC[0xc0 - 0xbc];
    u8 unk_C0;
} UnkStruct_0229d6dc;

struct St {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
    unsigned short unk_AC;
    char pad_AE[2];
    unsigned char unk_B0;
    char pad_B1[5];
    unsigned char unk_B6;
    char pad_B7[0x2A1];
    char unk_358[1];
};

typedef struct UnkStruct_0229d5f4 UnkStruct_0229d5f4;

struct UnkStruct_0229d5f4 {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0xb6 - 0xac];
    unsigned char unk_B6;
    char pad_B7[0xdb8 - 0xb7];
    char unk_DB8;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern void func_ov002_0220a374(void *ptr, int size);
extern void func_ov096_0229c2dc(void *p0, int p1);
extern int func_ov002_02207d24(void *p0, int p1);
extern unsigned char data_020e54a8;
extern int func_ov098_022a31d8(int a, unsigned int argument1);
extern int func_020b67d4(void);
extern int func_ov097_022a27c0(void *self);
extern UnkStruct_0229da6c_2 *data_020ccf94;
extern int func_020435fc(int a, int b);
extern void func_0200467c(int a);
extern int func_ov097_022a27fc(UnkStruct_0229da6c *self, int p);
extern unsigned short func_ov096_0229f0dc(UnkStruct_0229d9f0 *self, int b);
extern int func_ov096_0229f7ac(UnkStruct_0229d9f0 *self, int b);
extern void func_ov096_0229c2ec(UnkStruct_0229d9f0 *self, int a);
extern void func_ov094_0229aa58(void *ptr, int y);
extern int func_ov096_0229c4dc(void *p);
extern void func_0206fcb0(unsigned int argument0);
extern int func_ov096_0229cc10(void *p);
extern void func_0206fba8(unsigned char);
extern int func_ov096_022a18dc(void *, int);
extern void func_ov096_022a1540(void *);
extern int func_ov096_0229f55c(void *receiver);
extern void func_ov096_0229fb9c(void *);
extern void func_ov096_0229f874(void *, int, int, int);
extern int func_ov096_0229f088(void *, unsigned char);
extern void func_ov096_0229f5ac(void *, unsigned char);
extern int func_ov096_0229f8cc(void *, unsigned char, int, int, int);
extern int func_0209a1e8(void);
extern void func_020665b8(void *p);
extern int func_ov096_0229e158(void *receiver);
extern int func_0204c120(int, int, int);
extern void func_ov096_0229e0f8(UnkStruct_0229d7d0 *, int);
extern u16 func_ov096_0229e4a4(UnkStruct_0229d6dc *self, int a);
extern void func_ov096_0229e6a0(UnkStruct_0229d6dc *self);
extern void func_ov096_0229e67c(UnkStruct_0229d6dc *self);
extern void func_ov096_0229e9a0(struct St *self, unsigned char b);
extern int func_ov096_0229f290(struct St *self, unsigned char b);
extern int func_ov096_0229f200(struct St *self, unsigned char b);
extern int func_0206fe54(void);
extern void func_ov094_0229a47c(void *ptr, unsigned short a, unsigned char b);
extern void func_ov096_0229e95c(UnkStruct_0229d5f4 *, int);
extern void func_ov094_0229b1d8(void *);
extern void func_ov096_0229cc24(unsigned int argument0);
extern unsigned char *func_ov096_0229fdb0(int a);

void func_ov096_0229dc08(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x2500);
    func_ov002_02208098((void *) (arg0), 0x10);
}

void func_ov096_0229dbe8(void *p)
{
    func_ov002_0220a164((char *) p + 0x2500);
    func_ov002_02208098((void *) (p), 0x11);
}

void func_ov096_0229dbc0(void *self)
{
    func_ov002_0220a374((char *) self + 0x2500, 4);
    func_ov002_02208098((void *) (self), 0x12);
    *((char *) self + 0xb9) = 0x26;
}

void func_ov096_0229db78(void *p0, int p1)
{
    func_ov002_02207d24((char *) p0 + 0x2418, 1);
    *((char *) p0 + 0xb7) = (char) p1;
    func_ov002_0220a374((char *) p0 + 0x2500, 5);
    func_ov002_02208098((void *) (p0), 0x14);
    func_ov096_0229c2dc(p0, 0x2000);
}

void func_ov096_0229db30(void *self, unsigned char v)
{
    func_ov002_02207d24((char *) self + 0x2418, 1);
    ((unsigned char *) self)[0xba] = ((unsigned char *) self)[0x8d];
    ((unsigned char *) self)[0xb7] = v;
    func_ov002_0220a374((char *) self + 0x2500, 6);
    func_ov002_02208098((void *) (self), 0x15);
}

int func_ov096_0229daec(int arg, unsigned int argument1)
{
    unsigned int first = (data_020e54a8 == 0);

    if (first > 0) {
        return func_ov098_022a31d8(arg, argument1);
    }

    if (func_020b67d4() != 0) {
        if (func_ov097_022a27c0((void *) arg) == 0) {
            return 0;
        }
        return 1;
    }

    return 0;
}

int func_ov096_0229da6c(UnkStruct_0229da6c *self, int p)
{
    unsigned int ok;

    ok = ((*(u8 *) &data_020e54a8) == 0) ? 1 : 0;
    if (ok > 0) {
        self->unk_C4 = func_020435fc(data_020ccf94->unk_64, p);
        if (self->unk_C4 == -1) {
            func_ov096_0229fb9c((void *) self);
            func_ov096_0229f874((void *) self, 3, 0xff, 0);
            func_0200467c(0x73);
            return 0;
        }
        return 2;
    }
    if (func_020b67d4() != 0) {
        return func_ov097_022a27fc(self, p);
    }
    return 0;
}

void func_ov096_0229d9f0(UnkStruct_0229d9f0 *self)
{
    unsigned char b;
    int r6;
    int x;
    int y;

    b = self->unk_B6;
    r6 = func_ov096_0229f0dc(self, b);
    if (func_ov096_0229daec((int) self, r6) == 0) {
        func_ov096_0229fb9c((void *) self);
        func_ov096_0229f874((void *) self, 9, 0xff, 1);
    } else {
        x = func_ov096_0229da6c((UnkStruct_0229da6c *) self, r6);
        if (x != 0) {
            if (x == 2) {
                func_ov002_02208098((void *) (self), 0x28);
                func_ov096_0229c2ec(self, 0x1000);
            } else {
                y = func_ov096_0229f7ac(self, b);
                func_ov094_0229aa58(&self->unk_358, y);
                func_ov096_0229fb9c((void *) self);
            }
        }
    }
}

void func_ov096_0229d9cc(void *p)
{

    func_0206fcb0(func_ov096_0229c4dc(p));
    func_ov096_0229cc10(p);
    func_ov096_0229c2dc(p, 0x200);
}

void func_ov096_0229d9a0(void *arg0)
{
    func_0206fba8(*(unsigned char *) ((char *) arg0 + 0xb6));

    func_0206fcb0(func_ov096_0229c4dc(arg0));
    func_ov096_022a18dc(arg0, 8);
    func_ov096_022a1540(arg0);
}

void func_ov096_0229d93c(UnkStruct_0229d93c *ptr)
{
    int rv;

    rv = func_ov096_0229f55c(ptr);
    if (rv == 0x26) {
        func_ov096_0229fb9c(ptr);
        func_ov096_0229f874(ptr, 0xb, 0xff, 1);
        return;
    } else {
        int r4;
        int r7;

        r4 = func_ov096_0229f088(ptr, ptr->unk_B6);
        r7 = (int) func_ov096_0229f0dc((UnkStruct_0229d9f0 *) ptr, (unsigned char) ptr->unk_B6);
        func_ov096_0229f5ac(ptr, ptr->unk_B6);
        func_ov096_0229f8cc(ptr, ptr->unk_B6, rv, r7, r4);
    }
}

int func_ov096_0229d8ec(UnkStruct_0229d8ec *p)
{
    int r4 = func_0209a1e8();
    if (r4 == -1) {
        func_ov096_0229fb9c(p);
        func_ov096_0229f874(p, 2, 0xff, 1);
        return 0;
    } else {
        func_0206fba8(p->unk_B6);
        p->unk_B8 = p->unk_B6;
        p->unk_B6 = (unsigned char) (r4 + 0xf);
        return 1;
    }
}

void func_ov096_0229d8bc(int arg)
{
    if (func_ov096_0229d8ec((UnkStruct_0229d8ec *) arg) != 0) {
        func_0206fcb0(func_ov096_0229c4dc((void *) arg));
        func_ov096_0229cc10((void *) arg);
        func_ov096_0229c2ec((UnkStruct_0229d9f0 *) arg, 0x200);
    }
}

void func_ov096_0229d878(UnkStruct_0229d878 *a)
{
    if (func_ov096_0229d8ec((UnkStruct_0229d8ec *) a)) {
        void *p;
        p = (void *) func_ov096_0229c4dc(a);
        func_020665b8(p);
        func_0206fcb0((unsigned int) p);
        func_ov096_0229f5ac(a, a->b8);
        func_ov096_022a18dc(a, 8);
        func_ov096_022a1540(a);
    }
}

void func_ov096_0229d7d0(UnkStruct_0229d7d0 *o)
{
    int v;
    int w;

    switch (o->unk_BB) {
        case 0xb:
            v = func_0204c120(func_ov096_0229e158(o), 0, 0);
            break;
        case 0xc:
            v = func_0204c120(100, 0, 0);
            break;
        case 0xd:
            v = func_0204c120(1000, 0, 0);
            break;
        case 0xe:
            v = func_0204c120(10000, 0, 0);
            break;
    }
    w = func_ov096_0229f55c(o);
    if (w == 0x26) {
        func_ov096_0229fb9c((void *) o);
        func_ov096_0229f874((void *) o, 0xc, 0xff, 1);
    } else {
        func_ov096_0229e0f8(o, v);
        func_ov096_0229f8cc((void *) o, 0x25, w, v, 0);
    }
}

void func_ov096_0229d6dc(UnkStruct_0229d6dc *self)
{
    volatile u16 t;
    int flag = 1;
    int r;

    t = 0xfff1;
    switch (self->unk_BB) {
        case 0xf:
            self->unk_C0 = 3;
            break;
        case 0x10: {
            unsigned int ok;
            u16 lo, hi;
            self->unk_C0 = 4;
            t = func_ov096_0229e4a4(self, 4);
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1429 && lo <= 0x1430) {
                ok = 1;
            }
            if (ok != 0) {
                flag = 0;
            }
        } break;
        case 0x11: {
            unsigned int ok;
            u16 lo, hi;
            self->unk_C0 = 5;
            t = func_ov096_0229e4a4(self, 5);
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x13a0 && lo <= 0x13a7) {
                ok = 1;
            }
            if (ok != 0) {
                flag = 0;
            }
        } break;
        default:
            func_ov096_0229fb9c((void *) self);
            return;
    }

    r = func_ov096_0229f55c(self);
    if (flag != 0 && r == 0x26) {
        func_ov096_0229fb9c((void *) self);
        func_ov096_0229f874((void *) self, 0xa, 0xff, 0);
        func_0200467c(0x73);
    } else {
        self->unk_B4 = (u8) r;
        func_ov096_0229e6a0(self);
        self->unk_AC = 0xfff1;
        func_ov096_0229e67c(self);
        func_ov096_0229c2ec((UnkStruct_0229d9f0 *) self, 0x8000);
    }
}

void func_ov096_0229d664(struct St *self)
{
    unsigned char b;
    b = self->unk_B6;
    func_ov096_0229e9a0(self, b);
    self->unk_A4 = func_ov096_0229f290(self, b);
    self->unk_A8 = func_ov096_0229f200(self, b);
    if (func_0206fe54() != 0) {
        self->unk_A4 -= 2;
        self->unk_A8 -= 2;
    }
    func_ov002_02208098((void *) (self), 0x2B);
    func_ov094_0229a47c(&self->unk_358[0], self->unk_AC, self->unk_B0);
}

void func_ov096_0229d5f4(UnkStruct_0229d5f4 *self)
{
    unsigned char b = self->unk_B6;
    func_ov096_0229e95c(self, b);
    self->unk_A4 = func_ov096_0229f290((struct St *) self, b);
    self->unk_A8 = func_ov096_0229f200((struct St *) self, b);
    if (func_0206fe54()) {
        self->unk_A4 -= 2;
        self->unk_A8 -= 2;
    }
    func_ov002_02208098((void *) (self), 0x2a);
    func_ov094_0229b1d8(&self->unk_DB8);
}

void func_ov096_0229d5ec(unsigned int argument0)
{
    func_ov096_0229cc24(argument0);
}

int func_ov096_0229d5d4(int arg)
{
    func_ov002_02208098((void *) (arg), 0x31);
    return (int) func_ov096_0229fdb0(arg);
}
