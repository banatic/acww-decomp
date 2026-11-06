/* local_join_2: 4 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02268a1c @ 0x02268a1c, 0x44 bytes, ARM
 * func_ov066_0226890c @ 0x0226890c, 0x110 bytes, ARM
 * func_ov066_022688cc @ 0x022688cc, 0x40 bytes, ARM
 * func_ov066_02268878 @ 0x02268878, 0x54 bytes, ARM
 */

#include "types.h"

typedef struct UnkStruct_0226890c {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[4];
    u16 unk_08;
} UnkStruct_0226890c;

typedef struct GStruct {
    u8 pad_00[0xc0];
    u32 unk_C0;
} GStruct;

struct Arg {
    u8 pad_00[2];
    u16 unk_02;
};

struct UnkStruct_02268878 {
    u8 pad_00[4];
    u32 unk_04;
};

extern int WM_StartConnectEx(void (*func)(void *), int arg, int a, int b, int c);
extern void func_ov066_0226686c(int status);
extern GStruct *data_ov066_0226bdf4;
extern int func_ov066_02266e08(void);
extern void func_ov066_02268ea0(UnkStruct_0226890c *self);
extern void func_ov066_02268e9c(void *self);
extern void func_ov066_02268e14(void *self);
extern void func_ov066_02266e64(void);
extern void func_ov066_02266a08(void (*cb)(void *));
extern void func_ov066_02268410(void *packet);
extern int WM_Disconnect(void (*cb)(void *), int arg);
extern void func_ov066_02269dcc(void);
extern void func_ov066_02266bf4(void);
extern struct UnkStruct_02268878 *data_ov066_0226bdec;

void func_ov066_0226890c(UnkStruct_0226890c *self);
void func_ov066_02268878(struct Arg *arg);

void func_ov066_02268a1c(int arg)
{
    int status = WM_StartConnectEx((void (*)(void *))(void (*)(void *)) func_ov066_0226890c, arg, 0, 1, 0);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_0226890c(UnkStruct_0226890c *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }

    if (self->unk_02 == 0) {
        switch (self->unk_08) {
            case 7:
                func_ov066_02268ea0(self);
                return;
            case 8:
                func_ov066_02268e9c(self);
                return;
            case 9:
                if (((int) (data_ov066_0226bdf4->unk_C0 << 29)) >> 31) {
                    func_ov066_02266e64();
                } else {
                    func_ov066_02268e14(self);
                }
                return;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                func_ov066_0226686c(0x10);
                return;
            case 6:
                break;
        }
    } else if (self->unk_02 == 1) {
        if (((int) (data_ov066_0226bdf4->unk_C0 << 25)) >> 31) {
            func_ov066_02266a08(func_ov066_02268410);
            return;
        } else {
            func_ov066_02266e64();
            return;
        }
    } else {
        func_ov066_0226686c(self->unk_02);
    }
}

int func_ov066_022688cc(int param)
{
    int status = WM_Disconnect((void (*)(void *))(void (*)(void *)) func_ov066_02268878, param);
    if (status == 2) {
        return 1;
    } else {
        func_ov066_0226686c(status);
        return 0;
    }
}

void func_ov066_02268878(struct Arg *arg)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }

    if (arg->unk_02 == 0) {
        struct UnkStruct_02268878 *p = data_ov066_0226bdec;
        p->unk_04 = 4;
        func_ov066_02269dcc();
        func_ov066_02266bf4();
        return;
    } else {
        func_ov066_0226686c(arg->unk_02);
        return;
    }
}
