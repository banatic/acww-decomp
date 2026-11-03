/* screen_icon: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02003b78 @ 0x02003b78, 0x4c bytes, Thumb
 * func_02003b50 @ 0x02003b50, 0x28 bytes, Thumb
 * func_02003b24 @ 0x02003b24, 0x2c bytes, Thumb
 * func_02003a90 @ 0x02003a90, 0x94 bytes, Thumb
 * func_02003a74 @ 0x02003a74, 0x1a bytes, Thumb
 * func_02003a64 @ 0x02003a64, 0x10 bytes, Thumb
 * func_02003a54 @ 0x02003a54, 0x10 bytes, Thumb
 * func_02003a44 @ 0x02003a44, 0x10 bytes, Thumb
 * func_02003a34 @ 0x02003a34, 0x10 bytes, Thumb
 * func_020039f0 @ 0x020039f0, 0x44 bytes, Thumb
 * func_020039e4 @ 0x020039e4, 0xc bytes, Thumb
 * func_020039d4 @ 0x020039d4, 0x10 bytes, Thumb
 * func_020039c4 @ 0x020039c4, 0x10 bytes, Thumb
 * func_0200396c @ 0x0200396c, 0x58 bytes, Thumb
 * func_02003938 @ 0x02003938, 0x32 bytes, Thumb
 * func_020038bc @ 0x020038bc, 0x7c bytes, Thumb
 * func_02003814 @ 0x02003814, 0xa8 bytes, Thumb
 * func_020037c8 @ 0x020037c8, 0x4c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02003b78_2 {
    int data[5];
};

struct UnkStruct_02003b78 {
    int unk_00;
    char pad_04[8];
    struct UnkStruct_02003b78_2 sub;
    int arr0;
    int arr1;
    int arr2;
    int arr3;
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    int c;
    int d;
    int e;
};

struct UnkStruct_02003a90 {
    u8 pad_00[0x0c];
    void *unk_0C;
    u8 pad_10[0x10];
    u32 unk_20;
    u32 unk_24;
    u8 pad_28[0x8];
    u8 unk_30;
    u8 pad_31;
    u8 unk_32;
};

struct UnkStruct_020039f0 {
    unsigned char pad_00[0x20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    unsigned char unk_30;
    unsigned char unk_31;
    unsigned char unk_32;
    unsigned char unk_33;
    int unk_34;
    int unk_38;
    int unk_3C;
};

typedef void (*Func)(void *);

struct UnkStruct_020039d4 {
    Func *vtable;
};

struct UnkStruct_0200396c {
    char pad_00[0xc];
    char unk_0C;
    char pad_0D[0x33 - 0xc - 1];
    char unk_33;
};

typedef struct {
    unsigned char pad_00[0x20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    unsigned char unk_30;
    unsigned char pad_31[2];
    unsigned char unk_33;
} UnkStruct_020038bc;

typedef struct {
    unsigned char pad_00[0x20];
    int value20;
    unsigned int value24;
    unsigned char pad_28[0x32 - 0x28];
    unsigned char flag32;
    unsigned char flag33;
    unsigned char pad_34[0x3c - 0x34];
    int value3c;
} UnkStruct_02003814;

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
    char pad_28[0x0A];
    unsigned char unk_32;
    unsigned char unk_33;
    unsigned int unk_34;
    unsigned int unk_38;
} UnkStruct_020037c8;

extern void func_0208af30(struct UnkStruct_02003b78 *p);
extern void func_0208a1f8(struct UnkStruct_02003b78_2 *s);
extern unsigned char data_020d72cc[];
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern int func_0208a1d0(void *p);
extern int func_0208aef0(struct UnkStruct_02003a90 *p);
extern int func_0208a1b0(void *p, int v);
extern int func_0208aeec(struct UnkStruct_02003a90 *p);
extern int func_0208a198(void *p, int v);
extern void func_02088df8(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern unsigned char data_0213ffb0[];
extern signed char data_020c7588[];
extern void *func_0208a144(int);
extern int data_020d5c64;
extern void func_0208a1f0(char *ptr, void *arg2);
extern void func_0208a1ec(char *ptr, int val);
extern void *func_0208a1e0(char *ptr, int val1, int val2);
extern void func_0208a158(char *ptr);
extern int func_0206fd04(void);
extern int func_0206fd10(void);
extern void func_0208a0c8(void *ptr);
extern void func_02011f1c(unsigned int);

void func_020039f0(struct UnkStruct_020039f0 *self);
void func_020039e4(int p0);
void func_020039d4(struct UnkStruct_020039d4 *obj);
void func_020039c4(void *r0);
void func_0200396c(struct UnkStruct_0200396c *obj, int flag);
void func_020038bc(UnkStruct_020038bc *p);
void func_02003814(UnkStruct_02003814 *self);
void func_020037c8(UnkStruct_020037c8 *p);

struct UnkStruct_02003b78 *func_02003b78(struct UnkStruct_02003b78 *p)
{
    func_0208af30(p);
    p->unk_00 = (unsigned int) data_020d72cc;
    func_0208a1f8(&p->sub);
    p->arr0 = 0;
    p->arr1 = 0;
    p->arr2 = 0;
    p->arr3 = 0;
    p->b0 = 0;
    p->b1 = 0;
    p->b2 = 1;
    p->b3 = 0;
    p->c = 0;
    p->d = 5;
    p->e = 0;
    return p;
}

void *func_02003b50(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_020d72cc;
    func_020039e4((int) obj);
    func_0208a1f4((char *) obj + 12);
    func_0208af00(obj);
    return obj;
}

void *func_02003b24(void *this)
{
    *(unsigned int *) this = (unsigned int) data_020d72cc;
    func_020039e4((int) this);
    func_0208a1f4((char *) this + 0xc);
    func_0208af00(this);
    func_020edb3c(this);
    return this;
}

void func_02003a90(struct UnkStruct_02003a90 *s)
{
    int r7, r4, r6, r3;
    if (s->unk_24 == 0) {
        return;
    }
    r7 = func_0208a1d0((char *) s + 0xc);
    if (r7 == 0) {
        return;
    }
    r4 = func_0208aef0(s);
    r4 += func_0208a1b0((char *) s + 0xc, -1);
    r6 = func_0208aeec(s);
    r3 = r6 + func_0208a198((char *) s + 0xc, -1);
    if (s->unk_32) {
        r4 += 0x78;
        r3 += 0x48;
    } else {
        r4 += s->unk_20;
        r3 += (s->unk_30 ? 0x8c : 0);
    }
    func_02088df8(0, r7, r4, r3, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_02003a74(int arg)
{
    func_020038bc((UnkStruct_020038bc *) arg);
    func_02003814((UnkStruct_02003814 *) arg);
    func_020037c8((UnkStruct_020037c8 *) arg);
}

void func_02003a64(void)
{
    func_020039f0((struct UnkStruct_020039f0 *) ((void *) data_0213ffb0));
}

void func_02003a54(void)
{
    func_020039e4((int) ((void *) data_0213ffb0));
}

void func_02003a44(void)
{
    func_020039d4((struct UnkStruct_020039d4 *) ((void *) data_0213ffb0));
}

void func_02003a34(void)
{
    func_020039c4((void *) data_0213ffb0);
}

void func_020039f0(struct UnkStruct_020039f0 *self)
{
    self->unk_31 = 0;
    self->unk_20 = data_020c7588[0];
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_2C = 0;
    self->unk_30 = 0;
    self->unk_32 = 1;
    func_0200396c((struct UnkStruct_0200396c *) self, 0);
    self->unk_33 = 0;
    self->unk_34 = 0;
    self->unk_38 = 5;
    self->unk_3C = 0;
}

void func_020039e4(int p0)
{
    func_0208a144((p0 + 12));
}

void func_020039d4(struct UnkStruct_020039d4 *obj)
{
    obj->vtable[3](obj);
}

void func_020039c4(void *r0)
{
    void *r1;
    void *r2;

    r1 = *(void **) r0;
    r1 = *(void **) ((char *) r1 + 8);
    r1 = ((void *(*) (void *) ) r1)(r0);
}

void func_0200396c(struct UnkStruct_0200396c *obj, int flag)
{
    func_0208a1f0(&obj->unk_0C, &data_020d5c64);
    if (flag != 0) {
        func_0208a1ec(&obj->unk_0C, 1);
        func_0208a1e0(&obj->unk_0C, 1, 0);
        func_0208a158(&obj->unk_0C);
    } else {
        func_0208a1ec(&obj->unk_0C, 0);
        func_0208a144((int) (&obj->unk_0C));
    }
    obj->unk_33 = 0;
}

int func_02003938(void *p)
{
    int result;
    int field38;

    if (*(unsigned char *) ((char *) p + 0x31) != 0 && *(int *) ((char *) p + 0x2c) == 0 && *(int *) ((char *) p + 0x3c) > 0) {
        result = 1;
    } else {
        result = 0;
    }

    if (result != 0) {
        field38 = *(int *) ((char *) p + 0x38);
        if (field38 != 5 && field38 != *(int *) ((char *) p + 0x34)) {
            result = 0;
        }
    }

    return result;
}

void func_020038bc(UnkStruct_020038bc *p)
{
    int r4, r6;

    r4 = (func_0206fd04() != 0) ? 1 : 0;
    r6 = func_0206fd10();

    if (p->unk_2C > 0) {
        p->unk_2C--;
        if (p->unk_2C == 0) {
            p->unk_33 = 1;
        }
    }

    if (p->unk_30 != 0) {
        if (p->unk_28 == 0x1000) {
            if (r6 < 0x1000) {
                p->unk_2C = 0x17;
            }
        }
    } else {
        if (r4 != 0) {
            p->unk_24 = 0;
            p->unk_20 = (int) (signed char) data_020c7588[0];
            func_0200396c((struct UnkStruct_0200396c *) p, 1);
            p->unk_2C = 0xe;
        }
    }

    p->unk_30 = r4;
    p->unk_28 = r6;
}

void func_02003814(UnkStruct_02003814 *self)
{
    if (self->flag33 != 0) {
        func_0200396c((struct UnkStruct_0200396c *) self, 0);
    }

    if (self->flag32 != 0) {
        if (func_02003938(self) != 0) {
            unsigned int v = 4;
            self->value24 = v;
            self->value20 = data_020c7588[v];
        } else {
            unsigned int v = 0;
            self->value24 = v;
            self->value20 = data_020c7588[v];
        }
    } else {
        if (func_02003938(self) != 0) {
            if (self->value24 < 4) {
                self->value24 = self->value24 + 1;
                self->value20 = data_020c7588[self->value24];
                if (self->value24 == 4) {
                    func_0200396c((struct UnkStruct_0200396c *) self, 0);
                }
            }
        } else {
            if (self->value24 != 0) {
                if (self->value24 == 4) {
                    func_0200396c((struct UnkStruct_0200396c *) self, 1);
                }
                self->value24 = self->value24 - 1;
                self->value20 = data_020c7588[self->value24];
            }
        }
    }

    if (self->value3c > 0) {
        self->value3c = self->value3c - 1;
    }

    self = (UnkStruct_02003814 *) ((char *) self + 0xc);
    func_0208a0c8(self);
}

void func_020037c8(UnkStruct_020037c8 *p)
{
    if (p->unk_24 != 0) {
        return;
    }
    if (p->unk_38 == 5) {
        return;
    }
    if (p->unk_38 == p->unk_34) {
        return;
    }

    func_02011f1c(p->unk_38);
    p->unk_34 = p->unk_38;
    p->unk_38 = 5;

    {
        unsigned int flag = 0;
        if (p->unk_34 <= 4) {
            if ((1U << p->unk_34) & 0x19U) {
                flag = 1;
            }
        }
        p->unk_32 = (unsigned char) flag;
    }
    p->unk_33 = 1;
}
