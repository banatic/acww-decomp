/* design_picker: 16 functions, module ov125
 * mwccarm 1.2/base -O4,s
 * func_ov125_0229fa80 @ 0x0229fa80, 0x78 bytes, Thumb
 * func_ov125_0229fa2c @ 0x0229fa2c, 0x54 bytes, Thumb
 * func_ov125_0229f9c8 @ 0x0229f9c8, 0x64 bytes, Thumb
 * func_ov125_0229f994 @ 0x0229f994, 0x34 bytes, Thumb
 * func_ov125_0229f948 @ 0x0229f948, 0x4c bytes, Thumb
 * func_ov125_0229f928 @ 0x0229f928, 0x20 bytes, Thumb
 * func_ov125_0229f8ec @ 0x0229f8ec, 0x3c bytes, Thumb
 * func_ov125_0229f8b8 @ 0x0229f8b8, 0x34 bytes, Thumb
 * func_ov125_0229f890 @ 0x0229f890, 0x28 bytes, Thumb
 * func_ov125_0229f868 @ 0x0229f868, 0x28 bytes, Thumb
 * func_ov125_0229f784 @ 0x0229f784, 0xe4 bytes, Thumb
 * func_ov125_0229f76c @ 0x0229f76c, 0x18 bytes, Thumb
 * func_ov125_0229f75c @ 0x0229f75c, 0x10 bytes, Thumb
 * func_ov125_0229f74c @ 0x0229f74c, 0x10 bytes, Thumb
 * func_ov125_0229f6f4 @ 0x0229f6f4, 0x58 bytes, Thumb
 * func_ov125_0229f6a0 @ 0x0229f6a0, 0x54 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229f928 UnkStruct_0229f928;

typedef struct My My;

struct UnkStruct_0229f928 {
    char pad_00[0xc];
    void (*func)(void *);
};

struct My {
    char pad_00[0x644];
    UnkStruct_0229f928 *sub;
};

struct UnkStruct_0229f8ec {
    u8 pad_00[0x87c];
    u8 cur;
};

typedef struct {
    u8 pad_00[0x87c];
    u8 value;
} UnkStruct_0229f8b8;

typedef struct {
    unsigned char pad_00[0x87c];
    unsigned char unk_87C;
} UnkStruct_0229f784;

typedef struct {
    void *unk_00;
} UnkStruct_0229f6f4;

extern int func_ov125_0229fb34(void *self);
extern int func_ov125_0229fb1c(void *self);
extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov002_0220a05c(void *addr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char func_ov002_022090e4(void *p, int arg1);
extern void func_0208e4c0(void *p, int n);
extern void func_ov002_0220a374(void *p, int a);
extern void func_ov002_0220a0ec(void *p);
extern int func_ov002_022088ac(int a);
extern int func_ov002_0220889c(int a);
extern int func_ov002_022088cc(int a);
extern int func_ov002_022088bc(int a);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a314(void *p);
extern unsigned char data_ov125_022a0ab8;
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov124_0229f43c(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

int func_ov125_0229f76c(unsigned short *ptr, unsigned short mask);
void func_ov125_0229f75c(unsigned short *p, unsigned short mask);
void func_ov125_0229f74c(unsigned short *p, unsigned short mask);

void func_ov125_0229fa80(unsigned char *self)
{
    if (func_ov125_0229f76c((unsigned short *) self, 2)) {
        int a = func_ov125_0229fb34(self);
        int b = func_ov125_0229fb1c(self);
        func_ov002_0220a0b4(self + 0x644, a, b);
        func_ov125_0229f74c((unsigned short *) self, 2);
    } else {
        int a = func_ov125_0229fb34(self);
        int b = func_ov125_0229fb1c(self);
        func_ov002_0220a05c(self + 0x644, a, b, 3, 1);
        self[0x87f] = self[0x8d];
        func_ov002_02208098(self, 5);
    }
}

void func_ov125_0229fa2c(unsigned char *self)
{
    int a;
    int b;
    a = func_ov002_02208ae4(self + 0x180);
    b = func_ov002_02208ad8(self + 0x180, *(self + 0x87e));
    func_ov002_0220a08c(self + 0x644, a, b, 2);
    *(self + 0x87f) = *(self + 0x8d);
    func_ov002_02208098(self, 5);
}

void func_ov125_0229f9c8(void *param)
{
    int v1, v2;
    ((unsigned char *) param)[0x87d] = 1;
    ((unsigned char *) param)[0x87e] = func_ov002_022090e4((char *) param + 0x180, 1);
    v1 = func_ov002_02208ae4((char *) param + 0x180);
    v2 = func_ov002_02208ad8((char *) param + 0x180, ((unsigned char *) param)[0x87e]);
    func_ov002_0220a0b4((char *) param + 0x644, v1, v2);
    func_0208e4c0((char *) param + 0x644, 8);
    func_ov002_02208098(param, 8);
}

void func_ov125_0229f994(void *p)
{
    int a = func_ov125_0229fb34(p);
    int b = func_ov125_0229fb1c(p);
    func_ov002_0220a0b4((char *) p + 0x644, a, b);
    func_ov002_0220a374((char *) p + 0x644, 1);
}

void func_ov125_0229f948(unsigned char *self)
{
    int a, b;

    self[0x87e] = 0;
    a = func_ov002_02208ae4(self + 0x180);
    b = func_ov002_02208ad8(self + 0x180, self[0x87e]);
    func_ov002_0220a0b4(self + 0x644, a, b);
    func_ov002_0220a374(self + 0x644, 7);
}

void func_ov125_0229f928(My *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub->func(&self->sub);
}

int func_ov125_0229f8ec(struct UnkStruct_0229f8ec *obj, u32 a, u32 b)
{
    u8 c = obj->cur;
    if (c < a) {
        goto fail;
    }
    if (c > b) {
        goto fail;
    }
    if (c == b) {
        func_ov125_0229f75c((unsigned short *) obj, 8);
        obj->cur = (u8) a;
    } else {
        obj->cur = (u8) (c + 1);
    }
    return 1;
fail:
    return 0;
}

int func_ov125_0229f8b8(UnkStruct_0229f8b8 *self, unsigned int min, unsigned int max)
{
    u8 v = self->value;
    if (v < min) {
        goto fail;
    }
    if (v > max) {
        goto fail;
    }
    if (v == min) {
        self->value = (u8) max;
        func_ov125_0229f75c((unsigned short *) self, 4);
    } else {
        self->value = (u8) (v - 1);
    }
    return 1;
fail:
    return 0;
}

int func_ov125_0229f890(unsigned char *p, unsigned char min, unsigned char max, unsigned char delta)
{
    unsigned char v = p[0x87c];
    if (v >= min && v <= max) {
        p[0x87c] = v + (delta - min);
        return 1;
    }
    return 0;
}

unsigned char func_ov125_0229f868(unsigned char *param0, unsigned char param1, unsigned char param2, unsigned char param3)
{
    unsigned char temp;
    unsigned char result;

    temp = param0[0x87c];
    if (temp >= param1 && temp <= param2) {
        param0[0x87c] = temp + (param3 - param1);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov125_0229f784(UnkStruct_0229f784 *self, int param1)
{
    unsigned char original = self->unk_87C;
    func_ov125_0229f74c((unsigned short *) self, 0xc);
    if (func_ov002_022088ac(param1)) {
        if (func_ov125_0229f8b8((UnkStruct_0229f8b8 *) self, 0, 3) == 0) {
            func_ov125_0229f8b8((UnkStruct_0229f8b8 *) self, 4, 7);
        }
    } else {
        if (func_ov002_0220889c(param1)) {
            if (func_ov125_0229f8ec((struct UnkStruct_0229f8ec *) self, 0, 3) == 0) {
                func_ov125_0229f8ec((struct UnkStruct_0229f8ec *) self, 4, 7);
            }
        }
    }
    if (func_ov125_0229f76c((unsigned short *) self, 0xc) == 0) {
        if (func_ov002_022088cc(param1)) {
            if (func_ov125_0229f890((unsigned char *) self, 4, 7, 0) == 0) {
                if (self->unk_87C == 8) {
                    self->unk_87C = 7;
                    func_ov002_0220a2b4((char *) self + 0x644);
                }
            }
        } else {
            if (func_ov002_022088bc(param1)) {
                if ((int) func_ov125_0229f868((unsigned char *) self, 0, 3, 4) == 0) {
                    if (self->unk_87C >= 4 && self->unk_87C <= 7) {
                        self->unk_87C = 8;
                        func_ov002_0220a314((char *) self + 0x644);
                    }
                }
            }
        }
    }
    return original != self->unk_87C;
}

int func_ov125_0229f76c(unsigned short *ptr, unsigned short mask)
{
    return ((*(unsigned short *) ((char *) ptr + 0x878)) & mask) != 0;
}

void func_ov125_0229f75c(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x878);
    *p = (unsigned short) (*p | mask);
}

void func_ov125_0229f74c(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x878);
    *p = *p & ~mask;
}

UnkStruct_0229f6f4 *func_ov125_0229f6f4(UnkStruct_0229f6f4 *self)
{
    self->unk_00 = (void *) &data_ov125_022a0ab8;
    func_ov002_0220afdc((char *) self + 0x6a8);
    func_ov002_02209cb4((char *) self + 0x644);
    func_ov002_02207e28((char *) self + 0x574);
    func_ov002_02209ac8((char *) self + 0x180);
    func_ov124_0229f43c((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov125_0229f6a0(void *p)
{
    ((int *) p)[0] = (int) ((int *) &data_ov125_022a0ab8);
    func_ov002_0220afdc((char *) p + 0x6a8);
    func_ov002_02209cb4((char *) p + 0x644);
    func_ov002_02207e28((char *) p + 0x574);
    func_ov002_02209ac8((char *) p + 0x180);
    func_ov124_0229f43c((char *) p + 0x94);
    func_ov002_0220826c(p);
    return p;
}
