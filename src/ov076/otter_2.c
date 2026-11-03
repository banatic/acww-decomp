/* otter_2: 5 functions, module ov076
 * mwccarm 1.2/base -O4,s
 * func_ov076_02279230 @ 0x02279230, 0x48 bytes, Thumb
 * func_ov076_02279178 @ 0x02279178, 0xb8 bytes, Thumb
 * func_ov076_0227908c @ 0x0227908c, 0xec bytes, Thumb
 * func_ov076_02279034 @ 0x02279034, 0x58 bytes, Thumb
 * func_ov076_02278fec @ 0x02278fec, 0x48 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02279178 UnkStruct_02279178;

struct UnkStruct_02279178 {
    u8 unk_00[0x64];
    int unk_64;
    u8 p1[0x8e - 0x68];
    short unk_8E;
    u8 p2[0x94 - 0x90];
    short unk_94;
    u8 p3[0x350 - 0x96];
    u8 unk_350[0x3b0 - 0x350];
    u8 unk_3B0[0x514 - 0x3b0];
    u8 unk_514[0x564 - 0x514];
    u8 unk_564[0x720 - 0x564];
    int unk_720;
    u16 unk_724;
};

typedef struct {
    unsigned int : 12;
    unsigned int field : 16;
    unsigned int : 4;
} Bitfield190;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C; // 0x5c
    unsigned int unk_60; // 0x60
    unsigned int unk_64; // 0x64
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;            // 0x8e
    unsigned char pad_90[4]; // 0x90 .. 0x94
    short unk_94;            // 0x94
    unsigned char pad_96[0x190 - 0x96];
    Bitfield190 bf190; // 0x190
    unsigned char pad_194[0x334 - 0x194];
} UnkStruct_0227908c;

typedef struct {
    char pad_00[0x64];
    int counter;
    char pad_68[0x8e - 0x64 - 4];
    unsigned short flags_low;
    char pad_90[0x94 - 0x8e - 2];
    unsigned short flags_high;
    char pad_96[0x350 - 0x94 - 2];
    char sub[1];
    char pad_351[0x720 - 0x350 - 1];
    int threshold;
} UnkStruct_02278fec;

extern int func_02019e00(unsigned char *p);
extern int func_02019de8(unsigned char *p);
extern void func_ov076_02279370(unsigned char *obj, int arg);
extern int func_02019c20(u8 *, int, int, int, int, int);
extern int func_0200442c(u8 *, int, int, int);
extern void func_0201ad18(u8 *, int, int, int, void *, int, int, int);
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_020164a0(void *, int);
extern int func_020164cc(void *, void *);
extern int func_020e8870(void *, int, int);
extern int func_ov003_02228400(void *, unsigned int);
extern int func_020912d4(int, void *, int, int);
extern void func_0201aff4(void *, int);
extern void func_0201addc(void *a);
extern void func_020ee470(void *);

int func_ov076_02279230(unsigned char *obj)
{
    if (func_02019e00(obj + 0x564) == 3) {
        if (func_02019de8(obj + 0x564) != 0) {
            if (*(unsigned char *) (obj + 0x71c) == 0) {
                func_ov076_02279370(obj, 0);
            } else {
                func_ov076_02279370(obj, 4);
            }
        }
    }
    return 1;
}

int func_ov076_02279178(UnkStruct_02279178 *self)
{
    int t;

    func_02019c20(self->unk_564, 1, 0xf9, 1, 0, 0);
    func_0200442c(self->unk_514, 0x814, 0x7f, 0);
    self->unk_8E = self->unk_8E + 0x8000;
    self->unk_94 = self->unk_8E;
    func_0201aff4((void *) self->unk_350, self->unk_8E);
    t = -(self->unk_8E / 6);
    if (t < 0) {
        t = -t;
    }
    self->unk_724 = (u16) t;
    func_0201ad18(self->unk_3B0, 0, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    self->unk_720 = self->unk_64;
    return 1;
}

int func_ov076_0227908c(void *self)
{
    unsigned int arr[3];

    if (func_020164a0((char *) self + 0x334, 0) == 0xf9) {
        if (func_020164cc((char *) self + 0x334, self) != 0) {
            func_ov076_02279370((unsigned char *) self, 5);
            goto exit;
        }
    }

    if (func_020164a0((char *) self + 0x334, 0) == 0xf9) {
        if (((UnkStruct_0227908c *) self)->bf190.field == 0xb) {
            *((unsigned char *) self + 0x511) = 0;
            *((unsigned char *) self + 0x510) = 0;
        }
    }

    func_020e8870((char *) self + 0x8e, 0, *(short *) ((char *) self + 0x724));

    if (((UnkStruct_0227908c *) self)->bf190.field == 0x1b) {
        unsigned int *p = (unsigned int *) ((char *) self + 0x5c);
        arr[0] = *(unsigned int *) ((char *) self + 0x5c);
        arr[1] = p[1];
        arr[2] = p[2];
        arr[1] = 0;
        arr[2] += 0x3800;
        func_ov003_02228400(arr, 0x5000);
        func_020912d4(0x16, arr, 0, 0);
        func_0200442c((u8 *) ((char *) self + 0x514), 0x7ed, 0x7f, 0);
    }

exit:
    ((UnkStruct_0227908c *) self)->unk_94 = ((UnkStruct_0227908c *) self)->unk_8E;
    func_0201aff4((char *) self + 0x350, ((UnkStruct_0227908c *) self)->unk_8E);
    return 1;
}

int func_ov076_02279034(void *p)
{
    func_02019c20((u8 *) ((char *) p + 0x564), 1, 0xfa, 0, 0, 0);
    func_0201addc((char *) p + 0x3b0);
    *(unsigned short *) ((char *) p + 0x8e) = 0;
    *(unsigned short *) ((char *) p + 0x94) = 0;
    func_0201aff4((char *) p + 0x350, 0);
    *(unsigned int *) ((char *) p + 0x64) += 0x4000;
    return 1;
}

int func_ov076_02278fec(UnkStruct_02278fec *self)
{
    self->flags_high = 0;
    self->flags_low = 0;
    func_0201aff4(&self->sub, 0);
    self->counter += 0xeb;
    if (self->counter > (self->threshold + 0x14000)) {
        func_020ee470(self);
    }
    return 1;
}
