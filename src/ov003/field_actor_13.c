/* field_actor_13: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220ff40 @ 0x0220ff40, 0x80 bytes, Thumb
 * func_ov003_0220ff14 @ 0x0220ff14, 0x2c bytes, Thumb
 * func_ov003_0220fe4c @ 0x0220fe4c, 0xc8 bytes, Thumb
 * func_ov003_0220fe04 @ 0x0220fe04, 0x48 bytes, Thumb
 * func_ov003_0220fdf4 @ 0x0220fdf4, 0xe bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0220ff40 {
    char pad_00[0x7d4];
    int vec2[3];
    char pad_7E0[0x800 - 0x7d4 - 0xc];
    int unk_800;
} UnkStruct_0220ff40;

struct UnkStruct_0220ff14 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x750];
    short unk_7E0;
};

typedef struct UnkStruct_0220fe4c {
    u32 unk_00;   // 0x00
    u32 unk_04;   // 0x04
    u32 unk_08;   // 0x08
    u8 pad_0C[2]; // 0x0c
    u8 unk_0E;    // 0x0e
    u8 unk_0F;    // 0x0f
} UnkStruct_0220fe4c;

typedef struct UnkStruct_0220fe4c_2 {
    u8 pad_00[0x7d4];
    UnkStruct_0220fe4c sub; // 0x7d4
    u8 pad_7E4[0x7f0 - 0x7e4];
    u32 unk_7F0; // 0x7f0
    u32 unk_7F4; // 0x7f4
    u32 unk_7F8; // 0x7f8
    u32 unk_7FC; // 0x7fc
    u32 unk_800; // 0x800
    u8 pad_804[0x818 - 0x804];
    u32 unk_818; // 0x818
} UnkStruct_0220fe4c_2;

typedef struct {
    char pad_00[0x7d4];
    int arr[3];
} UnkStruct_0220fe04;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0220fdf4;

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0200f290(UnkStruct_0220ff40 *, int);
extern void func_0200f268(UnkStruct_0220ff40 *, int);
extern int func_ov003_02220db4(int, int *);
extern int func_020113e0(short *p, short val);
extern void func_020110a0(void *object, short *values);
extern u32 func_02008258(void *self, u32 val);
extern int func_ov003_0220fda0(void *self, u32 *arr, int a, int b);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_02010f5c(void *self);
extern int func_0200f434(void *self, int *arr);
extern void func_02010d64(void *self);

void func_ov003_0220ff40(UnkStruct_0220ff40 *self, int param)
{
    int r;

    r = func_02073908(data_020ccf94, self->unk_800);
    if (r == 0) {
        if (param == 2) {
            func_0200f268(self, 0x1c);
            return;
        }
        if (param != 0x67) {
            if (func_0200f290(self, 0x1c) != 0) {
                int tmp[3];
                int *v = self->vec2;
                tmp[0] = v[0];
                tmp[1] = v[1];
                tmp[2] = v[2];
                func_ov003_02220db4(self->unk_800, tmp);
                func_0200f268(self, 0x1c);
            }
        } else {
            func_0200f268(self, 0x1c);
        }
        return;
    }
    func_0200f268(self, 0x1c);
}

void func_ov003_0220ff14(struct UnkStruct_0220ff14 *self)
{
    short local;
    local = self->unk_8E;
    func_020113e0(&local, self->unk_7E0);
    func_020110a0((void *) (self), (short *) (&local));
}

void func_ov003_0220fe4c(UnkStruct_0220fe4c_2 *self)
{
    UnkStruct_0220fe4c *p = &self->sub;
    void *g = (*(void * *) &data_020ccf94);

    if (func_02073908((int) g, self->unk_800) != 0) {
        if (p->unk_0F == 0) {
            if (self->unk_818 == 1) {
                p->unk_0F = 1;
            } else if (self->unk_818 == 2) {
                p->unk_0F = 2;
            }
        }
    }

    if (p->unk_0E < 2) {
        p->unk_0E++;
        return;
    }

    if (func_02073908((int) g, self->unk_800) == 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }

    switch (p->unk_0F) {
        case 0:
            break;
        case 1: {
            u32 tmp[3];
            tmp[0] = p->unk_00;
            tmp[1] = p->unk_04;
            tmp[2] = p->unk_08;
            func_ov003_0220fda0(self, tmp, 6, -1);
            break;
        }
        case 2: {
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
        }
    }
}

void func_ov003_0220fe04(UnkStruct_0220fe04 *self)
{
    int local[3];
    int *p = self->arr;
    func_02010f5c(self);
    local[0] = self->arr[0];
    local[1] = p[1];
    local[2] = p[2];
    if (func_0200f434(self, local)) {
        func_ov003_0220ff14((struct UnkStruct_0220ff14 *) self);
    }
    func_02010d64(self);
    func_ov003_0220fe4c((UnkStruct_0220fe4c_2 *) self);
}

void func_ov003_0220fdf4(UnkStruct_0220fdf4 *dst, UnkStruct_0220fdf4 *src)
{
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
}
