/* aquarium_fish_classes_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022387b0 @ 0x022387b0, 0x54 bytes, Thumb
 * func_ov004_02238704 @ 0x02238704, 0xac bytes, Thumb
 * func_ov004_02238698 @ 0x02238698, 0x6c bytes, Thumb
 * func_ov004_02238608 @ 0x02238608, 0x90 bytes, Thumb
 * func_ov004_022385dc @ 0x022385dc, 0x2c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02238704 {
    int x, y, z;
};

struct UnkStruct_02238704_2 {
    u8 pad_00[0x158];
    int unk_158;
    u8 pad_15C[0x1a8 - 0x15c];
    int unk_1A8;
    int unk_1AC;
    int unk_1B0;
    u8 pad_1B4[0x1fc - 0x1b4];
    int unk_1FC;
    u8 pad_200[0x208 - 0x200];
    unsigned short unk_208;
    u8 pad_20A[0x211 - 0x20a];
    u8 unk_211;
};

extern void *data_ov004_022593ac;
extern int func_0200430c(void *p);
extern struct UnkStruct_02238704 data_ov004_02258a30;
extern void func_020042c0(void *p, struct UnkStruct_02238704 *v);
extern int func_ov004_02239460(int, int);
extern int func_02056f28(void *p, int k);
extern void func_020042a0(void *p, int k);

void func_ov004_02238698(char *self);
void func_ov004_02238608(void *self);

void func_ov004_022387b0(void *self)
{
    *((char *) self + 0x1c7) = 0;
    *(int *) ((char *) self + 0x1a8) = 0x14500;
    *(int *) ((char *) self + 0x1ac) = 0x3700;
    *(int *) ((char *) self + 0x1b0) = 0x15400;
    *(short *) ((char *) self + 0x1c0) = 0;
    data_ov004_022593ac = self;
    func_0200430c((char *) self + 0x1fc);
}

void func_ov004_02238704(struct UnkStruct_02238704_2 *self)
{
    struct {
        struct UnkStruct_02238704 t;
        struct UnkStruct_02238704 u;
    } o;

    o.t.x = data_ov004_02258a30.x;
    o.t.y = data_ov004_02258a30.y;
    o.t.z = data_ov004_02258a30.z;
    self->unk_1A8 = o.t.x;
    self->unk_1AC = o.t.y;
    self->unk_1B0 = o.t.z;
    o.u.x = self->unk_1A8;
    o.u.y = self->unk_1AC;
    o.u.z = self->unk_1B0;
    func_020042c0(&self->unk_1FC, &o.u);
    switch (self->unk_211) {
        case 2:
            func_ov004_02238698((char *) self);
            break;
        case 4:
            func_ov004_02238608((void *) self);
            break;
        case 6:
            if (self->unk_158 >= self->unk_208) {
                self->unk_211 = 2;
                self->unk_158 = 0;
            }
            break;
    }
    self->unk_158 = self->unk_158 + 1;
}

void func_ov004_02238698(char *self)
{
    *(s16 *) (self + 0x208) = (s16) func_ov004_02239460(0x28, 0xc8);
    *(int *) (self + 0x20c) = (func_ov004_02239460(0x32, 0x4b) << 0xc) / 0x64;
    *(int *) (self + 0x110) = *(int *) (self + 0x20c);
    *(u8 *) (self + 0x20a) = (u8) func_ov004_02239460(1, 7);
    *(u8 *) (self + 0x210) = 0;
    *(int *) (self + 0x158) = 0;
    *(u8 *) (self + 0x211) = 4;
}

void func_ov004_02238608(void *self)
{
    unsigned char *c;

    if (func_02056f28((char *) self + 0x100, 1) != 0) {
        func_020042a0((char *) self + 0x1fc, 0x832);
        c = (unsigned char *) ((char *) self + 0x210);
        *c = (unsigned char) (*c + 1);
    }
    if (*((unsigned char *) self + 0x210) >= *((unsigned char *) self + 0x20a)) {
        if (func_02056f28((char *) self + 0x100,
                          (unsigned short) (((((unsigned int) *(int *) ((char *) self + 0x104)) << 4) >> 16) - 1)) != 0) {
            *((char *) self + 0x211) = 6;
            *(int *) ((char *) self + 0x158) = 0;
            *(int *) ((char *) self + 0x108) = 0;
            *(int *) ((char *) self + 0x110) = 0;
        }
    }
}

void *func_ov004_022385dc(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x1c7) = 0x0;
    *(void **) (self + 0x1a8) = 0x0;
    *(void **) (self + 0x1ac) = 0x0;
    *(void **) (self + 0x1b0) = 0x0;
    *(u16 *) (self + 0x1c0) = 0x0;
    return self;
}
