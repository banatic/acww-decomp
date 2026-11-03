/* field_actor_9: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220f9f8 @ 0x0220f9f8, 0x64 bytes, Thumb
 * func_ov003_0220f994 @ 0x0220f994, 0x64 bytes, Thumb
 * func_ov003_0220f968 @ 0x0220f968, 0x2c bytes, Thumb
 * func_ov003_0220f8e0 @ 0x0220f8e0, 0x88 bytes, Thumb
 * func_ov003_0220f884 @ 0x0220f884, 0x5c bytes, Thumb
 * func_ov003_0220f7cc @ 0x0220f7cc, 0xb8 bytes, Thumb
 * func_ov003_0220f7b8 @ 0x0220f7b8, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
    unsigned char pad_08[2];
    unsigned char flag;
} UnkStruct_0220f994_2;

typedef struct {
    char pad_00[0x7D4];
    UnkStruct_0220f994_2 sub;
    char pad_7E0[0x20];
    int unk_800;
} UnkStruct_0220f994;

struct UnkStruct_0220f968 {
    unsigned char pad_00[0x8e];
    short unk_8E;
    unsigned char pad_90[0x74c];
    short unk_7DC;
};

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u8 pad_08[3];
    u8 unk_0B;
    u8 unk_0C;
} UnkStruct_0220f884;

typedef struct UnkStruct_0220f7cc {
    u32 unk_00;
    u32 w1;
    u8 pad_08[2];
    u8 count;
} UnkStruct_0220f7cc;

typedef struct SVec {
    u32 x;
    u32 y;
    u32 z;
} SVec;

struct UnkStruct_0220f7b8 {
    int a;
    int b;
    unsigned char c;
    unsigned char d;
};

extern void func_ov003_0220fae4(char *p, unsigned int *out1, unsigned int *out2, unsigned char *out3);
extern int func_ov003_0220fb30(char *self, unsigned int out1, unsigned int out2, int flag1, int flag2, int six, int val);
extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_0204f818(int *out0, int *out1, int *input);
extern void func_ov003_02224384(int a, int *b, int c);
extern int func_020113e0(short *a, int b);
extern void func_020110a0(void *object, short *values);
extern int func_02056f94(void *);
extern int func_ov003_0220f768(void *, int, int, unsigned char, int, int, int);
extern int func_02008258(void *, int);
extern int func_0200d4e8(void *, int, int, int);
extern void func_ov003_022235d8(void *p, u32 *v);
extern void func_02010f5c(void *self);
extern void func_02010d64(void *self);
extern int func_0200f554(void *self);

void func_ov003_0220f9f8(char *self, int val)
{
    unsigned char b;
    unsigned int out1, out2;
    if (*(int *) (self + 0x7f0) == 0x68) {
        *(unsigned short *) (self + 0xc84) = val;
    } else {
        int flag1, flag2;
        func_ov003_0220fae4(self + 0x8f0, &out1, &out2, &b);
        flag1 = (b != 0);
        flag2 = (b >> 4) != 0;
        func_ov003_0220fb30(self, out1, out2, flag1, flag2, 6, val);
    }
}

void func_ov003_0220f994(UnkStruct_0220f994 *self)
{
    int out[2];
    int copy[2];
    int input[3];
    UnkStruct_0220f994_2 *p;
    int a, b;

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        return;
    }
    p = &self->sub;
    if (p->flag >= 5u) {
        return;
    }
    b = p->b;
    a = p->a;
    input[0] = a;
    input[1] = 0;
    input[2] = b;
    out[0] = 0;
    out[1] = 0;
    func_0204f818(&out[0], &out[1], input);
    copy[0] = out[0];
    copy[1] = out[1];
    func_ov003_02224384(self->unk_800, copy, 2);
}

void func_ov003_0220f968(struct UnkStruct_0220f968 *self)
{
    short local;

    local = self->unk_8E;
    func_020113e0(&local, self->unk_7DC);
    func_020110a0((void *) (self), (short *) (&local));
}

void func_ov003_0220f8e0(void *self)
{
    typedef struct {
        int field0;
        int field4;
        unsigned char pad[3];
        unsigned char field_b;
        unsigned char field_c;
    } UnkStruct_0220f8e0;
    UnkStruct_0220f8e0 *sub = (UnkStruct_0220f8e0 *) ((char *) self + 0x7d4);
    if (sub->field_c) {
        if (func_02056f94((char *) self + 0x2d0) != 0) {
            func_ov003_0220f768(self, sub->field0, sub->field4, sub->field_b, 1, 6, -1);
        }
    } else {
        if (*(int *) ((char *) self + 0x818) == 1) {
            sub->field_c = 1;
            *(unsigned char *) ((char *) self + 0x2e4) = 1;
        } else if (*(int *) ((char *) self + 0x818) == 2) {
            int tmp = func_02008258(self, *(int *) ((char *) self + 0x7f0));
            *(int *) ((char *) self + 0x7fc) = tmp;
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}

void func_ov003_0220f884(void *self)
{
    UnkStruct_0220f884 *sub = (UnkStruct_0220f884 *) ((char *) self + 0x7d4);
    *(u32 *) ((char *) self + 0x7fc) = func_02008258(self, *(u32 *) ((char *) self + 0x7f0));
    if (sub->unk_0C != 0) {
        if (func_02056f94((char *) self + 0x2d0) != 0) {
            func_ov003_0220f768(self, sub->unk_00, sub->unk_04, (u8) sub->unk_0B, 1, 6, -1);
        }
    }
}

void func_ov003_0220f7cc(char *self)
{
    u32 out[2];
    u32 v[2];
    u32 v2[2];
    SVec st;
    UnkStruct_0220f7cc *sb;
    u32 a, b;

    sb = (UnkStruct_0220f7cc *) (self + 0x7d4);
    a = sb->w1;
    b = sb->unk_00;
    st.x = b;
    st.y = 0;
    st.z = a;
    out[0] = 0;
    out[1] = 0;
    func_0204f818((int *) out, (int *) (&out[1]), (int *) (&st));

    if (sb->count > 5u) {
        v[0] = out[0];
        v[1] = out[1];
        func_ov003_022235d8(*(void **) (self + 0x800), v);
    } else {
        sb->count = (u8) (sb->count + 1);
        if (sb->count == 5u) {
            v2[0] = out[0];
            v2[1] = out[1];
            func_ov003_02224384((int) (*(void **) (self + 0x800)), (int *) v2, 2);
        }
    }

    func_02010f5c(self);

    if (func_02073908((*(u32 *) &data_020ccf94), (int) (*(void **) (self + 0x800))) != 0) {
        func_ov003_0220f968((struct UnkStruct_0220f968 *) self);
        func_02010d64(self);
        func_ov003_0220f8e0(self);
    } else {
        if (func_0200f554(self) != 0) {
            func_ov003_0220f968((struct UnkStruct_0220f968 *) self);
        }
        func_02010d64(self);
        func_ov003_0220f884(self);
    }
}

void func_ov003_0220f7b8(struct UnkStruct_0220f7b8 *out, int a, int b, unsigned char c, unsigned char d)
{
    out->a = a;
    out->b = b;
    out->c = c;
    out->d = d;
}
