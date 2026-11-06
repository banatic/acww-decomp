/* gatekeeper_talk_3: 13 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02261b54 @ 0x02261b54, 0x94 bytes, Thumb
 * func_ov048_02261b28 @ 0x02261b28, 0x2c bytes, Thumb
 * func_ov048_02261b1c @ 0x02261b1c, 0xc bytes, Thumb
 * func_ov048_02261b10 @ 0x02261b10, 0xc bytes, Thumb
 * func_ov048_02261b04 @ 0x02261b04, 0xc bytes, Thumb
 * func_ov048_02261af8 @ 0x02261af8, 0xc bytes, Thumb
 * func_ov048_02261a88 @ 0x02261a88, 0x70 bytes, Thumb
 * func_ov048_02261a38 @ 0x02261a38, 0x50 bytes, Thumb
 * func_ov048_02261a14 @ 0x02261a14, 0x24 bytes, Thumb
 * func_ov048_022619f0 @ 0x022619f0, 0x24 bytes, Thumb
 * func_ov048_022619b0 @ 0x022619b0, 0x40 bytes, Thumb
 * func_ov048_022619ac @ 0x022619ac, 0x2 bytes, Thumb
 * func_ov048_0226196c @ 0x0226196c, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02261b54_2 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261b54_2;

typedef struct UnkStruct_02261b54 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02261b54;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261b28;

typedef struct UnkStruct_02261a88 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xae - 0x44];
    u8 unk_AE;
} UnkStruct_02261a88;

struct UnkStruct_02261a38 {
    char pad_00[0x40];
    int unk_40;
};

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02261a14;

struct UnkStruct_022619f0 {
    char pad_00[0x40];
    void *unk_40;
};

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb8 - 0x44];
    void *unk_B8;
} UnkStruct_022619b0;

typedef struct {
    char pad_00[0x14];
    int unk_14;
} PType;

extern UnkStruct_02261b54 *data_020ccf94;
extern int func_020984e8(void);
extern int func_02099020(int t, int a);
extern int func_02073d90(UnkStruct_02261b54 *g);
extern int func_02073918(UnkStruct_02261b54 *g, int a);
extern int func_02073dd4(UnkStruct_02261b54 *g, int a);
extern int func_ov048_02260a24(void *receiver);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov048_02263d20;
extern unsigned char func_ov048_022609fc(void *receiver);
extern int func_ov004_0222d4f4(void);
extern void func_0207428c(void);
extern int func_020ec1e8(void);
extern void func_ov048_022616b8(struct UnkStruct_02261a38 *self, int arg);
extern int func_ov048_02262658(void *receiver);
extern void func_ov048_022635f4(void *ptr, int n);

void func_ov048_02261a88(UnkStruct_02261a88 *self, int mode, int v);

void func_ov048_02261b54(UnkStruct_02261b54_2 *self, int mode)
{
    u8 arg;
    int code;
    int t;
    UnkStruct_02261b54 *g;

    t = func_020984e8();
    code = 0xff;
    switch (mode) {
        case 0:
            if (func_02099020(t, 1) != 0) {
                code = 8;
                break;
            }
            g = data_020ccf94;
            if (func_02073d90(g) != 0 && func_02073918(g, 0) != 0) {
                code = 0x50;
                break;
            }
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
                code = 0x51;
            } else {
                code = 0x52;
            }
            break;
        case 1:
            if (func_02099020(t, 1) != 0) {
                code = 0xe;
            } else {
                code = func_ov048_02260a24(self);
            }
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, data_ov048_02263d20);
    }
}

void func_ov048_02261b28(UnkStruct_02261b28 *obj, int arg1)
{
    if (arg1 == 1) {
        char c = func_ov048_022609fc(obj);
        func_0206844c(obj->unk_40, (u8 *) (&c), data_ov048_02263d20);
    }
}

void func_ov048_02261b1c(int a0, int a1)
{
    func_ov048_02261a88((UnkStruct_02261a88 *) a0, a1, 0x46);
}

void func_ov048_02261b10(int a, int b)
{
    func_ov048_02261a88((UnkStruct_02261a88 *) a, b, 0x3e);
}

void func_ov048_02261b04(int a, int b)
{
    func_ov048_02261a88((UnkStruct_02261a88 *) a, b, 0x54);
}

void func_ov048_02261af8(int a, int b)
{
    func_ov048_02261a88((UnkStruct_02261a88 *) a, b, 0x5b);
}

void func_ov048_02261a88(UnkStruct_02261a88 *self, int mode, int v)
{
    u8 a;
    u8 b;
    u8 c;

    if (mode == 0) {
        self->unk_AE = (u8) v;
        if (*((u8 *) self + 0x811) != 0) {
            a = self->unk_AE;
            func_0206844c(self->unk_40, &a, data_ov048_02263d20);
        } else {
            b = 0x6a;
            func_0206844c(self->unk_40, &b, data_ov048_02263d20);
        }
    }
    if (mode == 1) {
        c = func_ov048_022609fc(self);
        func_0206844c(self->unk_40, &c, data_ov048_02263d20);
    }
}

void func_ov048_02261a38(struct UnkStruct_02261a38 *self, int flag)
{
    char c[8];

    if (flag != 0) {
        return;
    }

    c[0] = 0x52;

    func_0206844c(self->unk_40, (u8 *) c, data_ov048_02263d20);
    func_ov004_0222d4f4();
    func_0207428c();

    if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
        func_ov048_022616b8(self, 0x14);
    } else {
        func_ov048_02262658(self);
    }
}

void func_ov048_02261a14(UnkStruct_02261a14 *self, int cond)
{
    if (cond == 0) {
        char local = 0x59;
        func_0206844c((int) self->unk_40, (u8 *) (&local), (int) ((*(void **) &data_ov048_02263d20)));
    }
}

void func_ov048_022619f0(struct UnkStruct_022619f0 *obj, int flag)
{
    if (flag == 0) {
        char c = 0x62;
        func_0206844c((int) obj->unk_40, (u8 *) (&c), data_ov048_02263d20);
    }
}

void func_ov048_022619b0(UnkStruct_022619b0 *obj, int mode)
{
    PType *p = obj->unk_40;
    if (mode == 0) {
        p->unk_14 = 0;
        func_ov048_022635f4(obj->unk_B8, 0xe);
    } else if (mode == 1) {
        char buf[8];
        buf[0] = func_ov048_022609fc(obj);
        func_0206844c((int) p, (u8 *) buf, data_ov048_02263d20);
    }
}

void func_ov048_022619ac(void *callbackObject, int callbackArgument1) {}

void func_ov048_0226196c(void *self, int which)
{
    char local;

    switch (which) {
        case 0:
            func_ov048_022616b8((struct UnkStruct_02261a38 *) self, 20);
            break;
        case 1:
            local = 0x6c;
            func_0206844c(*(unsigned int *) ((char *) self + 0x40), (u8 *) (&local), data_ov048_02263d20);
            break;
        case 2:
            func_ov048_022616b8((struct UnkStruct_02261a38 *) self, 20);
            break;
    }
}
