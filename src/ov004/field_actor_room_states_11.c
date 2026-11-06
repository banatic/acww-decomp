/* field_actor_room_states_11: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022287b4 @ 0x022287b4, 0x30 bytes, Thumb
 * func_ov004_02228774 @ 0x02228774, 0x40 bytes, Thumb
 * func_ov004_02228748 @ 0x02228748, 0x2c bytes, Thumb
 * func_ov004_022286e8 @ 0x022286e8, 0x60 bytes, Thumb
 * func_ov004_022286ac @ 0x022286ac, 0x3c bytes, Thumb
 * func_ov004_02228690 @ 0x02228690, 0x1a bytes, Thumb
 * func_ov004_02228678 @ 0x02228678, 0x18 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02228774 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02228774_2 {
    u8 pad_00[0x5c];
    struct UnkStruct_02228774 cur;
    u8 pad_68[0x7d4 - 0x68];
    struct UnkStruct_02228774 want;
    u8 pad_7E0[0x800 - 0x7e0];
    int room;
};

struct UnkStruct_022286ac {
    char pad_00[0x2d0];
    void *unk_2D0;
    char pad_2D4[0x51c];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

struct UnkStruct_02228678 {
    int unk_00;
    int unk_04;
    short unk_08;
    char unk_0A;
};

extern int func_ov004_02228850(void *, int, int);
extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_02051e38(int a);
extern int func_0200f328(void *argument0, void *argument1);
extern void func_02010f5c(int argument0);
extern int func_02056f28(void *argument0, int argument1);
extern void func_02010d64(void *self);
extern void func_02010e58(void *self, int *t, void *p);
extern void func_02089fc8(void *p);
extern int func_02056f94(void *p);
extern int func_02008258(void *self, int value);
extern int func_0200d4e8(void *self, int a, int b, int c);

void func_ov004_022287b4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((u32) (*(int *) (self + 0x7f0) - 0x29) > (u32) 0x1) {
        if (*(int *) (self + 0x7f0) == 0x2c) {
            *(u16 *) (self + 0xc84) = a1;
        } else {
            func_ov004_02228850(self, 0x6, a1);
        }
    }
}

void func_ov004_02228774(struct UnkStruct_02228774_2 *self, int stateId)
{
    struct UnkStruct_02228774 *src;
    struct UnkStruct_02228774 *dst;

    if (func_02073908(data_020ccf94, self->room)) {
        func_02051e38(0);
    }
    src = &self->want;
    dst = &self->cur;
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

int func_ov004_02228748(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_02010f5c((int) (self));
    v2 = func_02056f28(self + 0x2d0, 0xd);
    if (v2 != 0x0) {
        return func_0200f328((void *) (self), (void *) (0x4c6));
    }
    return v2;
}

void func_ov004_022286e8(char *self)
{
    if (func_02073908((int) ((*(char **) &data_020ccf94)), *(int *) (self + 0x800)) != 0) {
        func_02010d64(self);
    } else {
        int t[3];
        int *q = (int *) (self + 0x7d4);
        t[0] = q[0];
        t[1] = q[1];
        t[2] = q[2];
        func_02010e58(self, t, self + 0x7f0);
        func_02089fc8(self + 0x174);
    }
}

void func_ov004_022286ac(struct UnkStruct_022286ac *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 0, 1, -1);
    }
}

void func_ov004_02228690(void *self)
{
    func_ov004_02228748((char *) self);
    func_ov004_022286e8((char *) self);
    func_ov004_022286ac((struct UnkStruct_022286ac *) self);
}

void func_ov004_02228678(struct UnkStruct_02228678 *out, char fA, int f0, int f4, short f8)
{
    out->unk_0A = fA;
    out->unk_00 = f0;
    out->unk_04 = f4;
    out->unk_08 = f8;
}
