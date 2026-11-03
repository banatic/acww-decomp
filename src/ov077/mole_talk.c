/* mole_talk: 5 functions, module ov077
 * mwccarm 1.2/base -O4,s
 * func_ov077_02278c50 @ 0x02278c50, 0x50 bytes, Thumb
 * func_ov077_02278bfc @ 0x02278bfc, 0x54 bytes, Thumb
 * func_ov077_02278ba0 @ 0x02278ba0, 0x5c bytes, Thumb
 * func_ov077_02278b54 @ 0x02278b54, 0x4c bytes, Thumb
 * func_ov077_02278a9c @ 0x02278a9c, 0xb8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02278bfc {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_02278ba0 {
    unsigned char pad_00[0x1e];
    unsigned char flag;
    unsigned char pad_1F[0x40 - 0x1f];
    void *unk_40;
    unsigned char pad_44[0xb8 - 0x44];
    unsigned char *arr;
};

typedef struct {
    u8 pad_00[0x14];
    u32 unk_14;
} Inner40;

typedef struct {
    u8 pad_00[0x1e];
    u8 state;
    u8 pad_1F[0x40 - 0x1f];
    Inner40 *unk_40;
    u8 pad_44[0xb8 - 0x44];
    u8 *unk_B8;
} UnkStruct_02278b54;

typedef struct UnkStruct_02278a9c UnkStruct_02278a9c;

struct UnkStruct_02278a9c {
    unsigned char pad_00[0x1e];
    unsigned char cmd;
    unsigned char pad_1F[0x40 - 0x1f];
    unsigned int unk_40;
};

extern int func_0200442c(void *dst, void *src, int size, int fill);
extern void func_ov003_02219648(void);
extern int func_020984e8(void);
extern int func_02099670(int);
extern int func_02088b7c(unsigned char *);
extern int func_020644cc(int);
extern unsigned char data_ov077_02279600[];
extern int data_ov077_02279700;
extern int func_020683e4(void *a, int b, void *c, void *d);
extern unsigned char data_ov077_02279938;
extern void func_ov077_02278e10(UnkStruct_02278b54 *self, int arg);
extern void func_020157b0(UnkStruct_02278b54 *self, int a1, int a2, int a3);
extern int func_02015828(UnkStruct_02278b54 *self, int arg);
extern void *func_020160b4(UnkStruct_02278a9c *self);
extern int func_020ab504(void *p);
extern int func_020ab4f8(void *p);
extern int func_020e8b0c(int a, int b, int c);
extern void func_0206844c(unsigned int a, void *b, unsigned int c);

void func_ov077_02278c50(void *obj, int mode)
{
    switch (mode) {
        case 0:
            func_ov003_02219648();
            break;
        case 1:
            func_0200442c((char *) (*(int *) ((char *) obj + 0xb8)) + 0x514, (void *) 0x7f4, 0x7f, 0);
            break;
        case 2:
            func_0200442c((char *) (*(int *) ((char *) obj + 0xb8)) + 0x514, (void *) 0x7f5, 0x7f, 0);
            break;
    }
}

void func_ov077_02278bfc(int a, struct UnkStruct_02278bfc *out)
{
    int var;

    var = func_02088b7c((unsigned char *) func_02099670((int) func_020984e8())) - 1;
    if (var < 0) {
        var = 0;
    } else if (var > 5) {
        var = 5;
    }
    if (var == 5) {
        var = func_020644cc(4) + 1;
    }
    if (var < 0) {
        var = 0;
    } else if (var > 4) {
        var = 4;
    }
    out->unk_04 = data_ov077_02279600[var];
    out->unk_00 = data_ov077_02279700;
}

void func_ov077_02278ba0(struct UnkStruct_02278ba0 *self)
{
    if (self->flag == 0x17) {
        unsigned char cur = (unsigned char) func_020644cc(0x10);
        if (cur == self->arr[0x718]) {
            cur++;
            if (cur == 0x10) {
                cur = 0;
            }
        }
        self->arr[0x718] = cur;
        {
            unsigned char v = self->arr[0x718];
            func_020683e4(self->unk_40, 0, &v, &data_ov077_02279938);
        }
    }
}

void func_ov077_02278b54(UnkStruct_02278b54 *self)
{
    switch (self->state) {
        case 0xf:
            self->unk_40->unk_14 = 0;
            func_ov077_02278e10(self, 2);
            break;
        case 0x17:
            func_020157b0(self, 0xc, self->unk_B8[0x718], 0);
            func_02015828(self, 3);
            func_ov077_02278e10(self, 1);
            break;
    }
}

void func_ov077_02278a9c(UnkStruct_02278a9c *self)
{
    int chk;
    unsigned char out;
    unsigned char cmd;

    chk = func_020ab504(func_020160b4(self));
    out = 0xff;
    cmd = self->cmd;

    switch (cmd) {
        case 0xb:
            if (chk == 0) {
                out = (func_020644cc(2) == 0) ? 0xe : 0xd;
            } else {
                out = (func_020644cc(2) == 0) ? 0xe : 0xc;
            }
            break;
        case 0x1f:
        case 0x20:
        case 0x21: {
            int r = func_020644cc(0xd);
            int x = func_020ab4f8(func_020160b4(self));
            if (func_020e8b0c(x, r, r + 5) != 0) {
                out = 0x22;
            } else {
                out = (func_020644cc(2) == 0) ? 0x20 : 0x21;
            }
            break;
        }
        default:
            break;
    }

    if (out != 0xff) {
        unsigned char buf = out;
        func_0206844c(self->unk_40, &buf, (*(unsigned int *) &data_ov077_02279700));
    }
}
