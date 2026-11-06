/* local_mp_4: 9 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_022695ac @ 0x022695ac, 0x8c bytes, ARM
 * func_ov066_02269528 @ 0x02269528, 0x84 bytes, ARM
 * func_ov066_0226943c @ 0x0226943c, 0xec bytes, ARM
 * func_ov066_022693f0 @ 0x022693f0, 0x4c bytes, ARM
 * func_ov066_02269320 @ 0x02269320, 0xd0 bytes, ARM
 * func_ov066_022692c0 @ 0x022692c0, 0x60 bytes, ARM
 * func_ov066_0226929c @ 0x0226929c, 0x24 bytes, ARM
 * func_ov066_0226923c @ 0x0226923c, 0x60 bytes, ARM
 * func_ov066_02269204 @ 0x02269204, 0x38 bytes, ARM
 */

#include "types.h"

typedef struct Mac {
    u8 b[6];
} Mac;

typedef struct UnkStruct_022695ac {
    unsigned char pad_00[0x28];
    Mac macs[1];
} UnkStruct_022695ac;

typedef void (*Send_t)(void *buf, u32 len, int a, int b);

typedef struct UnkStruct_02269528 {
    unsigned char pad_00[0x14];
    void *unk_14;
    unsigned char pad_18[0xac - 0x18];
    Send_t unk_AC;
} UnkStruct_02269528;

typedef struct Msg {
    u16 kind;
    u16 len;
    u32 val;
} Msg;

typedef void (*Send_t_0226943c)(void *buf, u32 len, u32 mask, void *cb);

typedef struct UnkStruct_0226943c {
    unsigned char pad_00[0x14];
    void *buf; // 0x14
    unsigned char pad_18[0x28 - 0x18];
    unsigned char block[0x60]; // 0x28
    unsigned char pad_88[0xac - 0x88];
    Send_t_0226943c send; // 0xac
    unsigned char pad_B0[0xc0 - 0xb0];
    int busy : 1;    // 0xc0 bit 0
    int pending : 1; // bit 1
    u32 rest : 30;
} UnkStruct_0226943c;

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned int bit0 : 1;
    int bit1 : 1;
} UnkStruct_022693f0;

struct data_s {
    unsigned char pad_00[0x1e];
    unsigned short flag;
};

typedef void (*handler_t)(void *);

struct ov066_0226bdf4 {
    char pad_00[0xbc];
    handler_t handler;
};

extern UnkStruct_022695ac *data_ov066_0226bdf4;
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void MI_CpuFill8(void *dest, u8 data, u32 size);
extern u32 data_ov066_0226bdf8;
int func_ov066_02268024(const Mac *m);
void func_ov066_02266800(int kind, int idx);
extern int func_ov066_02266e08(void);
extern int func_ov066_02268c90(void);
extern void func_ov066_02268f1c(void *arg);
extern void func_ov066_02268da4(void *arg);

void func_ov066_022693f0(void);
void func_ov066_022692c0(void);

void func_ov066_022695ac(int idx, const Mac *src)
{
    Mac tmp;
    if (src != 0) {
        MI_CpuCopy8(src, &tmp, 6);
    } else {
        MI_CpuFill8(&tmp, 0, 6);
    }
    data_ov066_0226bdf4->macs[idx] = tmp;
    func_ov066_022692c0();
}

void func_ov066_02269528(void)
{
    Msg m;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    m.kind = 2;
    m.len = 8;
    m.val = data_ov066_0226bdf8;
    MI_CpuCopy8(&m, (*(UnkStruct_02269528 **) &data_ov066_0226bdf4)->unk_14, 8);
    (*(UnkStruct_02269528 **) &data_ov066_0226bdf4)->unk_AC((*(UnkStruct_02269528 **) &data_ov066_0226bdf4)->unk_14, 8, 1, 0);
}

void func_ov066_0226943c(void)
{
    Msg m;
    if ((*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->busy) {
        (*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->pending = 1;
        return;
    }
    (*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->busy = 1;
    (*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->pending = 0;
    m.kind = 0;
    m.len = 0x68;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    m.val = data_ov066_0226bdf8;
    MI_CpuCopy8(&m, (*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->buf, 8);
    MI_CpuCopy8((*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->block,
                (u8 *) (*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->buf + 8, 0x60);
    (*(UnkStruct_0226943c **) &data_ov066_0226bdf4)
        ->send((*(UnkStruct_0226943c **) &data_ov066_0226bdf4)->buf, 0x68, 0xffff, (void *) func_ov066_022693f0);
}

void func_ov066_022693f0(void)
{
    (*(UnkStruct_022693f0 **) &data_ov066_0226bdf4)->bit0 = 0;
    if ((*(UnkStruct_022693f0 **) &data_ov066_0226bdf4)->bit1 == 0) {
        return;
    }
    func_ov066_0226943c();
}

void func_ov066_02269320(Mac *cur, Mac *next)
{
    u16 i;
    int zero = 0;
    int one = 1;
    for (i = 0; i < 0x10; i = (u16) (i + 1)) {
        Mac *pc = &cur[i];
        Mac *pn = &next[i];
        int had = func_ov066_02268024(pc);
        int has = func_ov066_02268024(pn);
        cur[i] = next[i];
        if (had == 0 && has != 0) {
            func_ov066_02266800(zero, i);
        }
        if (had != 0 && has == 0) {
            func_ov066_02266800(one, i);
        }
    }
}

void func_ov066_022692c0(void)
{
    int i;
    unsigned char count = 0;
    int off;
    for (i = 0, off = 0; i < 16; i++, off += 6) {
        if (func_ov066_02268024((const Mac *) ((*(unsigned char **) &data_ov066_0226bdf4) + 0x28 + off)) != 0) {
            count++;
        }
    }
    (*(unsigned char **) &data_ov066_0226bdf4)[0x8c] = count;
}

void func_ov066_0226929c(void)
{
    MI_CpuFill8((*(char **) &data_ov066_0226bdf4) + 0x28, 0, 0x60);
}

void func_ov066_0226923c(void *arg)
{
    if (func_ov066_02266e08()) {
        return;
    }
    if (func_ov066_02268c90()) {
        return;
    }
    if ((*(struct data_s **) &data_ov066_0226bdf4)->flag == 0) {
        func_ov066_02268f1c(arg);
    } else {
        func_ov066_02268da4(arg);
    }
}

void func_ov066_02269204(void *arg)
{
    if ((*(struct ov066_0226bdf4 **) &data_ov066_0226bdf4)->handler) {
        (*(struct ov066_0226bdf4 **) &data_ov066_0226bdf4)->handler(arg);
    }
}
