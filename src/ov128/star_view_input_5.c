/* star_view_input_5: 7 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229c208 @ 0x0229c208, 0x98 bytes, Thumb
 * func_ov128_0229c1bc @ 0x0229c1bc, 0x4c bytes, Thumb
 * func_ov128_0229c144 @ 0x0229c144, 0x78 bytes, Thumb
 * func_ov128_0229bff0 @ 0x0229bff0, 0x154 bytes, Thumb
 * func_ov128_0229bf80 @ 0x0229bf80, 0x70 bytes, Thumb
 * func_ov128_0229bf34 @ 0x0229bf34, 0x4c bytes, Thumb
 * func_ov128_0229bf0c @ 0x0229bf0c, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x4A4];
    unsigned char unk_4A4;
    unsigned char pad_4A5[0x2D6B - 0x4A4 - 1];
    unsigned char unk_2D6B;
} UnkStruct_0229c1bc;

typedef struct UnkStruct_0229bff0 {
    unsigned char pad_00[0x110];
    void *unk_110;
    unsigned char pad_114[0x4a4 - 0x114];
    void *unk_4A4;
    unsigned char pad_4A8[0x2d48 - 0x4a8];
    int unk_2D48;
    int unk_2D4C;
} UnkStruct_0229bff0;

typedef struct UnkStruct_0229bf34 {
    char pad_00[0x4a4];
    char sub_4a4;
    char pad_4A5[0x2d6b - 0x4a4 - 1];
    unsigned char unk_2D6B;
} UnkStruct_0229bf34;

extern int func_ov002_02208054(void *self, int a);
extern void func_ov128_0229be20(void *self);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov127_02299d20(void *p, int a, int b);
extern void func_ov127_02299c08(void *p, int v, int c);
extern void func_ov128_0229bb20(void *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov128_0229bdd4(void *self);
extern unsigned char data_021fbdd8;
extern void func_ov127_02299bbc(unsigned char *ptr, unsigned char val);
extern int func_ov127_02299b78(void *);
extern unsigned char data_021f6c60; // at 0x021f6c60
extern unsigned char data_021f6c5c; // at 0x021f6c5c
extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void *receiver);
extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov127_02299b58(void *addr, int val);
extern int func_ov127_02299abc(void *addr, int val, int zero);
extern void func_ov128_0229be44(void *self);
extern void func_ov128_0229bc10(void *self);
extern void func_ov128_0229b7cc(void *self, int val);
extern void func_ov128_0229bc88(void *self);
extern int func_ov128_0229bae0(void *receiver);

void func_ov128_0229c208(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int v;

    if (func_ov002_02208054(self, 0) != 0) {
        func_ov128_0229be20(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    *(u8 *) (self + 0x2d6b) = (u8) func_ov127_02299d20(self + 0x4a4, a, b);
    v = *(u8 *) (self + 0x2d6b);
    if (v != 4) {
        func_ov127_02299c08(self + 0x4a4, v, 1);
        func_ov128_0229bb20(self);
        func_ov002_02208098((void *) (self), 1);
        return;
    }
    if (a < 0xc0) {
        return;
    }
    if (b <= 0xab) {
        return;
    }
    func_ov128_0229bdd4(self);
}

void func_ov128_0229c1bc(UnkStruct_0229c1bc *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (s), 2);
        func_ov127_02299bbc(&s->unk_4A4, s->unk_2D6B);
        func_ov128_0229bb20(s);
    } else {
        func_ov127_02299c08((void *) (&s->unk_4A4), (unsigned char) s->unk_2D6B, 1);
        func_ov128_0229bb20(s);
    }
}

void func_ov128_0229c144(void *obj)
{
    if (!func_ov127_02299b78((char *) obj + 0x4a4)) {
        goto common;
    }
    if (!data_021fbdd8) {
        goto short_path;
    }
    {
        volatile unsigned char *p = (volatile unsigned char *) ((char *) obj + 0x2d6b);
        unsigned char v;

        *p = (unsigned char) func_ov127_02299d20((char *) obj + 0x4a4, (unsigned char) data_021f6c60,
                                                 (unsigned char) data_021f6c5c);
        v = *p;
        if (v == 4) {
            goto short_path;
        }
        func_ov127_02299c08((char *) obj + 0x4a4, v, 1);
        func_ov128_0229bb20(obj);
        func_ov002_02208098((void *) (obj), 1);
        return;
    }
short_path:
    func_ov002_02208098((void *) (obj), 0);
common:
    func_ov128_0229bb20(obj);
}

void func_ov128_0229bff0(UnkStruct_0229bff0 *self)
{
    if (func_ov002_02208014(self)) {
        func_ov128_0229be44(self);
        return;
    }
    {
        unsigned short flags1 = data_021fbe40[1];
        if (flags1 & 1) {
            func_ov128_0229bc10(self);
            return;
        }
        if (flags1 & 0x800) {
        flag_800:;
            func_ov128_0229b7cc(self, 2);
            func_ov002_02208098((void *) (self), 4);
            func_ov128_0229bc88(self);
            return;
        }
    }
    {
        int old1 = self->unk_2D48;
        int old2 = self->unk_2D4C;
        int *p48;
        if (data_021fbe40[0] & 0x20) {
            *(&self->unk_2D48) = old1 - 4;
        } else if (data_021fbe40[0] & 0x10) {
            *(&self->unk_2D48) = old1 + 4;
        }
        if (data_021fbe40[0] & 0x40) {
            self->unk_2D4C -= 4;
        } else if (data_021fbe40[0] & 0x80) {
            self->unk_2D4C += 4;
        }
        if ((old1 == self->unk_2D48) && (old2 == self->unk_2D4C)) {
            return;
        }
        if (self->unk_2D48 < 0x30) {
            self->unk_2D48 = 0x30;
            func_ov127_02299b58(&self->unk_4A4, -4);
            func_ov128_0229bb20(self);
        } else if (self->unk_2D48 > 0xd0) {
            self->unk_2D48 = 0xd0;
            func_ov127_02299b58(&self->unk_4A4, 4);
            func_ov128_0229bb20(self);
        }
        if (self->unk_2D4C < 0x20) {
            self->unk_2D4C = 0x20;
            func_ov127_02299abc(&self->unk_4A4, -4, 0);
            func_ov128_0229bb20(self);
        } else if (self->unk_2D4C > 0xa0) {
            self->unk_2D4C = 0xa0;
            func_ov127_02299abc(&self->unk_4A4, 4, 0);
            func_ov128_0229bb20(self);
        }
        func_ov002_0220a0b4(&self->unk_110, self->unk_2D48, self->unk_2D4C);
    }
}

void func_ov128_0229bf80(void *this)
{
    unsigned char *self = (unsigned char *) this;
    unsigned short flags;
    int ret;

    if (func_ov002_02208014(this)) {
        func_ov128_0229be44(this);
        return;
    }
    flags = data_021fbe40[1];
    if ((flags & 2) != 0 || (flags & 8) != 0) {
        func_ov128_0229bdd4(this);
        return;
    }
    ret = func_ov128_0229bae0(this);
    self[0x2d6b] = (unsigned char) ret;
    if (self[0x2d6b] == 4) {
        return;
    }
    func_ov127_02299c08(self + 0x4a4, self[0x2d6b], 1);
    func_ov128_0229bb20(this);
    func_ov002_02208098((void *) (this), 5);
}

void func_ov128_0229bf34(UnkStruct_0229bf34 *self)
{
    int r;

    r = func_ov128_0229bae0(self);
    if (r != self->unk_2D6B) {
        func_ov002_02208098((void *) (self), 6);
        func_ov127_02299bbc((unsigned char *) ((char *) self + 0x4a4), self->unk_2D6B);
        func_ov128_0229bb20(self);
    } else {
        func_ov127_02299c08((char *) self + 0x4a4, (unsigned char) self->unk_2D6B, 1);
        func_ov128_0229bb20(self);
    }
}

void func_ov128_0229bf0c(void *r0)
{
    if (func_ov127_02299b78((char *) r0 + 0x4a4)) {
        func_ov002_02208098((void *) (r0), 4);
    }
    func_ov128_0229bb20(r0);
}
