/* field_actor_40: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02216640 @ 0x02216640, 0x2 bytes, Thumb
 * func_ov003_0221660c @ 0x0221660c, 0x34 bytes, Thumb
 * func_ov003_022165e4 @ 0x022165e4, 0x28 bytes, Thumb
 * func_ov003_02216520 @ 0x02216520, 0xc4 bytes, Thumb
 * func_ov003_0221648c @ 0x0221648c, 0x94 bytes, Thumb
 * func_ov003_0221646c @ 0x0221646c, 0x20 bytes, Thumb
 * func_ov003_02216460 @ 0x02216460, 0xc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02216520 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x8e - 0x60];
    s16 unk_8E;
    char pad_90[0x7d4 - 0x90];
    u8 unk_7D4;
    u8 unk_7D5;
    u8 unk_7D6;
    char pad_7D7[0x800 - 0x7d7];
    int unk_800;
} UnkStruct_02216520;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x240];
    char unk_2D0[8];
    unsigned int unk_2D8;
    char pad_2DC[0x4fb];
    unsigned char unk_7D7;
    char pad_7D8[0x18];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
    int unk_800;
} UnkStruct_0221648c;

extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int, unsigned int);
extern int func_0200f290(void *, int);
extern void func_02010f5c(int argument0);
extern int func_02056f28(void *ptr, int value);
extern int func_0200fc90(UnkStruct_02216520 *self);
extern int func_0200f328(UnkStruct_02216520 *self, int arg);
extern unsigned int *func_0200f27c(UnkStruct_02216520 *self, int arg);
extern int func_02095694(int a, int b);
extern void func_0204f794(int *out, u8 a, u8 b);
extern int func_020912d4(int a, int *b, s16 *c, int d);
extern void func_ov003_02224234(int a, int *b, int c);
extern void func_0200f268(UnkStruct_02216520 *self, int arg);
extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern int func_02008dc0(void *, short, int, int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_ov003_0220d268(void *);
extern void func_02010d64(int);
extern int func_02010ca4(int);

void func_ov003_02216520(UnkStruct_02216520 *self);

void func_ov003_02216640(void *receiver, int event) {}

void func_ov003_0221660c(void *p)
{
    if (func_02073908(data_020ccf94, *(unsigned int *) ((char *) p + 0x800)) != 0) {
        return;
    }
    if (func_0200f290(p, 0x1c) == 0) {
        return;
    }
    func_ov003_02216520((UnkStruct_02216520 *) p);
}

void func_ov003_022165e4(void *self)
{
    func_02010f5c((int) self);
    if (func_02056f28((char *) self + 0x2d0, 8) != 0) {
        func_ov003_02216520((UnkStruct_02216520 *) self);
    }
}

void func_ov003_02216520(UnkStruct_02216520 *self)
{
    s16 angle;
    int pair1[2];
    int pair2[2];
    int res[2];
    u8 *p = (u8 *) self + 0x7d4;
    int v = func_0200fc90(self);
    u8 a, b;

    if (p[2] != 0) {
        v++;
        if (v == 7) {
            func_0200f328(self, 0x83e);
        } else if (v == 9) {
            func_0200f328(self, 0x83f);
        }
    }

    func_02095694(v, self->unk_800);
    func_0200f27c(self, 9);
    func_0200f328(self, 0x83b);

    a = p[0];
    b = p[1];
    func_0204f794(res, a, b);

    angle = (s16) (self->unk_8E + 0x2000);
    func_020912d4(2, res, &angle, 0);

    if (res[0] >= self->unk_5C) {
        pair1[0] = a;
        pair1[1] = b;
        func_ov003_02224234(self->unk_800, pair1, 5);
    } else {
        pair2[0] = a;
        pair2[1] = b;
        func_ov003_02224234(self->unk_800, pair2, 4);
    }

    func_0200f268(self, 0x1c);
}

void func_ov003_0221648c(UnkStruct_0221648c *self)
{
    unsigned char flag = self->unk_7D7;
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        if (flag != 0) {
            func_02008dc0(self, self->unk_8E, 6, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
    if (flag != 0) {
        return;
    }
    if (func_02073908((unsigned int) ((*(void **) &data_020ccf94)), self->unk_800) == 0) {
        return;
    }
    if (((self->unk_2D8 << 4) >> 16) > 8) {
        func_ov003_0220d268(self);
    }
}

void func_ov003_0221646c(int a)
{
    func_ov003_022165e4((void *) a);
    func_02010d64(a);
    func_02010ca4(a);
    func_ov003_0221648c((UnkStruct_0221648c *) a);
}

void func_ov003_02216460(unsigned char *r0, unsigned char r1, unsigned int *r2)
{
    r0[2] = r1;
    r0[0] = (unsigned char) r2[0];
    r0[1] = (unsigned char) r2[1];
}
