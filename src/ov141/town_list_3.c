/* town_list_3: 11 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229a634 @ 0x0229a634, 0x80 bytes, Thumb
 * func_ov141_0229a5e0 @ 0x0229a5e0, 0x54 bytes, Thumb
 * func_ov141_0229a5b4 @ 0x0229a5b4, 0x2c bytes, Thumb
 * func_ov141_0229a59c @ 0x0229a59c, 0x16 bytes, Thumb
 * func_ov141_0229a580 @ 0x0229a580, 0x1c bytes, Thumb
 * func_ov141_0229a560 @ 0x0229a560, 0x20 bytes, Thumb
 * func_ov141_0229a524 @ 0x0229a524, 0x3c bytes, Thumb
 * func_ov141_0229a4e8 @ 0x0229a4e8, 0x3c bytes, Thumb
 * func_ov141_0229a4ac @ 0x0229a4ac, 0x3c bytes, Thumb
 * func_ov141_0229a490 @ 0x0229a490, 0x1c bytes, Thumb
 * func_ov141_0229a470 @ 0x0229a470, 0x20 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a634;

typedef struct UnkStruct_0229a634 UnkStruct_0229a634;

struct UnkStruct_0229a634 {
    u8 pad_00[0xa38];
    u8 obj;
    u8 pad_A39[0x83b];
    u32 unk_1274;
    u8 pad_1278[0x807];
    u8 unk_1A7F[13];
    u8 unk_1A8C;
};

typedef struct {
    char base[0xa38];
    int unk_A38;
    char pad_A3C[0x1042];
    unsigned char unk_1A7E;
    char pad_1A7F[13];
    unsigned char unk_1A8C;
} UnkStruct_0229a5e0;

typedef struct UnkStruct_0229a5b4 {
    unsigned char pad_00[0x1a8b];
    unsigned char cnt;
} UnkStruct_0229a5b4;

typedef struct UnkStruct_0229a524 {
    char pad_00[0x1274];
    int unk_1274;
    char pad_1278[0x813];
    char unk_1A8B;
} UnkStruct_0229a524;

struct UnkStruct_0229a4e8 {
    unsigned char pad_00[0x1278];
    int unk_1278;
    unsigned char pad_127C[0x80f];
    unsigned char unk_1A8B;
};

typedef struct UnkStruct_0229a4ac {
    char pad_00[0xa38];
    int unk_A38;
} UnkStruct_0229a4ac;

extern int func_0208e484(u8 *p);
extern int func_ov141_02299f94(UnkStruct_0229a634 *self, int _x);
extern void func_ov141_02299f6c(UnkStruct_0229a634 *self, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov141_0229a358(UnkStruct_0229a634 *self);
extern void func_ov141_0229a3a4(UnkStruct_0229a5e0 *obj);
extern int func_ov141_02299f7c(UnkStruct_0229a5e0 *obj, int x);
extern void func_ov141_02299f5c(UnkStruct_0229a5e0 *obj, int x);
extern void func_ov141_0229a428(UnkStruct_0229a5e0 *obj);
extern void func_ov141_0229a44c(UnkStruct_0229a5b4 *self);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207fc0(void *p);
extern int func_0206fe60(void);
extern void func_ov002_02208090(UnkStruct_0229a524 *, int);
extern void func_0200467c(int);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);

void func_ov141_0229a524(UnkStruct_0229a524 *self);
void func_ov141_0229a4e8(struct UnkStruct_0229a4e8 *param);
void func_ov141_0229a4ac(UnkStruct_0229a4ac *obj);
int func_ov141_0229a490(unsigned char *p);
int func_ov141_0229a470(unsigned char *p);

void func_ov141_0229a634(UnkStruct_0229a634 *self)
{
    u8 b;

    if (func_0208e484(&self->obj) == 0) {
        return;
    }

    b = self->unk_1A8C;

    if (b == 7) {
        if (self->unk_1274 == 8) {
            func_ov141_0229a524((UnkStruct_0229a524 *) self);
            return;
        }
    } else if (b == 6) {
        func_ov141_0229a4e8((struct UnkStruct_0229a4e8 *) self);
        return;
    } else {
        if (self->unk_1A7F[b] != 0) {
            func_ov141_02299f94(self, b);
            func_0200467c(0x29);
            func_ov141_02299f6c(self, 8);
            func_ov141_02299f6c(self, 0x10);
        }
    }

    func_ov002_02208098((void *) (self), 1);
    func_ov141_0229a358(self);
}

void func_ov141_0229a5e0(UnkStruct_0229a5e0 *obj)
{
    if (func_0208e484((u8 *) (&obj->unk_A38)) != 0) {
        func_ov141_0229a3a4(obj);
        func_ov002_02208098((void *) (obj), obj->unk_1A7E);
        if (func_ov141_02299f7c(obj, 8) != 0) {
            func_ov141_02299f5c(obj, 8);
            obj->unk_1A8C = 7;
            func_ov141_0229a428(obj);
        }
    }
}

void func_ov141_0229a5b4(UnkStruct_0229a5b4 *self)
{
    if (self->cnt != 0) {
        self->cnt = self->cnt - 1;
    } else {
        func_ov141_0229a44c(self);
        func_ov002_022080a0((void *) (self), 1);
    }
}

void func_ov141_0229a59c(void *p)
{
    func_ov141_0229a44c((UnkStruct_0229a5b4 *) p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov141_0229a580(void *p)
{
    func_ov141_0229a4ac((UnkStruct_0229a4ac *) p);
    func_ov002_02207fc0(p);
    func_ov002_02208098((void *) (p), 1);
}

void func_ov141_0229a560(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov141_0229a59c((void *) r4);
    } else {
        func_ov141_0229a580((void *) r4);
    }
}

void func_ov141_0229a524(UnkStruct_0229a524 *self)
{
    func_ov141_02299f5c((UnkStruct_0229a5e0 *) self, 2);
    self->unk_1274 = 10;
    self->unk_1A8B = 5;
    func_ov002_02208090(self, 3);
    func_ov002_02208098((void *) (self), 5);
    func_0200467c(0x27);
}

void func_ov141_0229a4e8(struct UnkStruct_0229a4e8 *param)
{
    func_ov141_02299f6c((UnkStruct_0229a634 *) param, 2);
    param->unk_1278 = 10;
    param->unk_1A8B = 5;
    func_ov002_02208090((UnkStruct_0229a524 *) param, 3);
    func_ov002_02208098((void *) (param), 5);
    func_0200467c(0x28);
}

void func_ov141_0229a4ac(UnkStruct_0229a4ac *obj)
{
    int r4, r2;
    r4 = func_ov141_0229a490((unsigned char *) obj);
    r2 = func_ov141_0229a470((unsigned char *) obj);
    func_ov002_0220a0b4(&obj->unk_A38, r4, r2);
    func_ov002_0220a374(&obj->unk_A38, 7);
    func_ov141_0229a3a4((UnkStruct_0229a5e0 *) obj);
}

int func_ov141_0229a490(unsigned char *p)
{
    unsigned char v = p[0x1a8c];
    if (v == 6) {
        return 0x43;
    }
    if (v == 7) {
        return 0x95;
    }
    return 0x2c;
}

int func_ov141_0229a470(unsigned char *p)
{
    unsigned char b;
    b = p[0x1a8c];
    if ((unsigned char) (b + 0xfa) > 1) {
        goto compute;
    }
    return 0xae;
compute:
    return (b << 4) + 0x46;
}
