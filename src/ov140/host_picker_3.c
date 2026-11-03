/* host_picker_3: 14 functions, module ov140
 * mwccarm 1.2/base -O4,s
 * func_ov140_0229a914 @ 0x0229a914, 0xa0 bytes, Thumb
 * func_ov140_0229a8c0 @ 0x0229a8c0, 0x54 bytes, Thumb
 * func_ov140_0229a894 @ 0x0229a894, 0x2c bytes, Thumb
 * func_ov140_0229a85c @ 0x0229a85c, 0x38 bytes, Thumb
 * func_ov140_0229a800 @ 0x0229a800, 0x5c bytes, Thumb
 * func_ov140_0229a7e8 @ 0x0229a7e8, 0x16 bytes, Thumb
 * func_ov140_0229a7cc @ 0x0229a7cc, 0x1c bytes, Thumb
 * func_ov140_0229a7ac @ 0x0229a7ac, 0x20 bytes, Thumb
 * func_ov140_0229a774 @ 0x0229a774, 0x38 bytes, Thumb
 * func_ov140_0229a73c @ 0x0229a73c, 0x38 bytes, Thumb
 * func_ov140_0229a6dc @ 0x0229a6dc, 0x60 bytes, Thumb
 * func_ov140_0229a6a0 @ 0x0229a6a0, 0x3c bytes, Thumb
 * func_ov140_0229a67c @ 0x0229a67c, 0x24 bytes, Thumb
 * func_ov140_0229a65c @ 0x0229a65c, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229a914 {
    u8 pad_00[0xa0];
    u32 unk_A0;
    u8 pad_A4[0x4];
    u32 unk_A8;
    u8 pad_AC[0x8af - 0xac];
    u8 arr1[0x31];
    u8 arr2[0x100];
    u8 pad_9E0[0x128c - (0x8e0 + 0x100)];
} UnkStruct_0229a914;

typedef struct {
    unsigned char pad_00[0x8AE];
    unsigned char unk_8AE;
    unsigned char pad_8AF[0x2D];
    unsigned char unk_8DC;
    unsigned char pad_8DD[0x9AF];
    unsigned char unk_128C;
} UnkStruct_0229a8c0;

typedef struct {
    unsigned char pad_00[0x8db];
    unsigned char unk_8DB;
} UnkStruct_0229a894;

struct UnkStruct_0229a6dc {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[0x8db - 0xac];
    unsigned char unk_8DB;
    unsigned char pad_8DC;
    unsigned char unk_8DD;
    unsigned char unk_8DE;
};

extern int func_0208e484(void *);
extern void func_ov140_0229a3fc(void *, int _x);
extern void func_ov140_02299fa0(void *, int);
extern void func_0200467c(int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov140_0229a544(void *);
extern void func_ov140_0229a590(void *);
extern int func_ov140_02299fb0(void *, int);
extern void func_ov140_02299f90(void *, int);
extern int func_ov140_0229a614(void *);
extern void func_ov140_0229a638(UnkStruct_0229a894 *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov140_0229a164(unsigned char *param, unsigned char value);
extern void func_ov140_0229a280(unsigned char *param);
extern int func_0206fe60(void);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208090(int, int);
extern void func_ov140_02299fc8(struct UnkStruct_0229a6dc *self);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);

void func_ov140_0229a7e8(void *ptr);
void func_ov140_0229a774(int r0);
void func_ov140_0229a73c(int param1);
void func_ov140_0229a6dc(struct UnkStruct_0229a6dc *self);
void func_ov140_0229a6a0(unsigned char *p);
int func_ov140_0229a67c(unsigned char *p);
int func_ov140_0229a65c(unsigned char *p);

void func_ov140_0229a914(UnkStruct_0229a914 *self)
{
    if (func_0208e484((char *) self + 0x128c) != 0) {
        u8 c = self->arr1[0x2d];
        if (c == 6) {
            if (self->unk_A8 != 8) {
                goto tail;
            }
            func_ov140_0229a6dc((struct UnkStruct_0229a6dc *) self);
            goto exit;
        } else if (c == 8) {
            if (self->unk_A0 != 8) {
                goto tail;
            }
            func_ov140_0229a774((int) self);
            goto exit;
        } else if (c == 7) {
            func_ov140_0229a73c((int) self);
            goto exit;
        } else {
            if (self->arr1[c] != 0 && self->arr2[c] != 4) {
                func_ov140_0229a3fc(self, c);
                func_0200467c(0x29);
                func_ov140_02299fa0(self, 8);
                func_ov140_02299fa0(self, 0x10);
            }
        }
    tail:
        func_ov002_02208098((void *) (self), 1);
        func_ov140_0229a544(self);
    }
exit:
    return;
}

void func_ov140_0229a8c0(UnkStruct_0229a8c0 *obj)
{
    if (func_0208e484(&obj->unk_128C) == 0) {
        return;
    }
    func_ov140_0229a590(obj);
    func_ov002_02208098((void *) (obj), obj->unk_8AE);
    if (func_ov140_02299fb0(obj, 8) == 0) {
        return;
    }
    func_ov140_02299f90(obj, 8);
    obj->unk_8DC = 8;
    func_ov140_0229a614(obj);
}

int func_ov140_0229a894(UnkStruct_0229a894 *p)
{
    if (p->unk_8DB != 0) {
        int v = p->unk_8DB - 1;
        p->unk_8DB = v;
        return v;
    } else {
        func_ov140_0229a638(p);
        return (int) func_ov002_022080a0((void *) (p), 1);
    }
}

void func_ov140_0229a85c(unsigned char *param)
{
    unsigned char *p = param;
    p += 0x8db;
    if (*p > 1) {
        *p = *p - 1;
        func_ov140_0229a164(param, *p);
    } else {
        func_ov140_0229a164(param, 0);
        func_ov140_0229a280(param);
        func_ov002_02208098((void *) (param), 7);
    }
}

void func_ov140_0229a800(unsigned char *p)
{
    if (p[0x8db] < 5) {
        func_ov140_0229a164(p, p[0x8db]);
        p[0x8db]++;
    } else {
        func_ov140_0229a164(p, 5);
        *(int *) (p + 0xa8) = 8;
        if (func_0206fe60()) {
            func_ov140_0229a7e8(p);
        } else {
            func_ov002_02208098((void *) (p), 1);
            func_ov140_0229a544(p);
        }
        func_ov140_02299f90(p, 0x20);
    }
}

void func_ov140_0229a7e8(void *ptr)
{
    func_ov140_0229a638((UnkStruct_0229a894 *) ptr);
    func_ov002_02208098((void *) (ptr), 0);
}

void func_ov140_0229a7cc(void *arg)
{
    func_ov140_0229a6a0((unsigned char *) arg);
    func_ov002_02207fc0(arg);
    func_ov002_02208098((void *) (arg), 1);
}

void func_ov140_0229a7ac(void *p)
{
    if (func_0206fe60() != 0) {
        func_ov140_0229a7e8(p);
    } else {
        func_ov140_0229a7cc(p);
    }
}

void func_ov140_0229a774(int r0)
{
    int r4 = r0;
    func_ov140_02299f90((void *) r4, 2);
    *(int *) (r4 + 0xa0) = 0xa;
    *(char *) (r4 + 0x8db) = 5;
    func_ov002_02208090(r4, 3);
    func_ov002_02208098((void *) (r4), 5);
    func_0200467c(0x27);
}

void func_ov140_0229a73c(int param1)
{
    int *ptr;
    int value;

    func_ov140_02299fa0((void *) param1, 2);
    ptr = (int *) (param1 + 0xa4);
    *ptr = 10;
    *(char *) (param1 + 0x8db) = 5;
    func_ov002_02208090(param1, 3);
    func_ov002_02208098((void *) (param1), 5);
    func_0200467c(0x28);
}

void func_ov140_0229a6dc(struct UnkStruct_0229a6dc *self)
{
    func_ov140_02299fa0((void *) self, 0x20);
    func_ov002_02208098((void *) (self), 6);
    self->unk_8DB = 5;
    self->unk_8DD = self->unk_8DD + 1;
    if (self->unk_8DD > self->unk_8DE) {
        self->unk_8DD = 0;
    }
    func_ov140_02299fc8(self);
    self->unk_A8 = 0xa;
    func_ov140_0229a3fc((void *) self, -1);
    func_0200467c(0xc);
}

void func_ov140_0229a6a0(unsigned char *p)
{
    int a;
    int b;
    a = func_ov140_0229a67c(p);
    b = func_ov140_0229a65c(p);
    func_ov002_0220a0b4(p + 0x128c, a, b);
    func_ov002_0220a374(p + 0x128c, 7);
    func_ov140_0229a590((void *) p);
}

int func_ov140_0229a67c(unsigned char *p)
{
    unsigned char v = p[0x8dc];
    if (v == 7) {
        return 0x6a;
    }
    if (v == 8) {
        return 0xab;
    }
    if (v == 6) {
        return 0x29;
    }
    return 0x24;
}

int func_ov140_0229a65c(unsigned char *p)
{
    unsigned char b = p[0x8dc];
    unsigned char t = (unsigned char) (b + 0xfa);
    if (t <= 2) {
        return 0xae;
    } else {
        return (b << 4) + 0x46;
    }
}
