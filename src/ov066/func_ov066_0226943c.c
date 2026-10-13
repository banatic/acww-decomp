/* func_ov066_0226943c @ 0x0226943c, 0xec bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef void (*Send_t)(void *buf, u32 len, u32 mask, void *cb);

typedef struct UnkStruct_0226943c {
    unsigned char pad_00[0x14];
    void *buf; // 0x14
    unsigned char pad_18[0x28 - 0x18];
    unsigned char block[0x60]; // 0x28
    unsigned char pad_88[0xac - 0x88];
    Send_t send; // 0xac
    unsigned char pad_B0[0xc0 - 0xb0];
    int busy : 1;    // 0xc0 bit 0
    int pending : 1; // bit 1
    u32 rest : 30;
} UnkStruct_0226943c;

typedef struct Msg {
    u16 kind;
    u16 len;
    u32 val;
} Msg;

extern UnkStruct_0226943c *data_ov066_0226bdf4;
extern u32 data_ov066_0226bdf8;
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void func_ov066_022693f0(void);

void func_ov066_0226943c(void)
{
    Msg m;
    if (data_ov066_0226bdf4->busy) {
        data_ov066_0226bdf4->pending = 1;
        return;
    }
    data_ov066_0226bdf4->busy = 1;
    data_ov066_0226bdf4->pending = 0;
    m.kind = 0;
    m.len = 0x68;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    m.val = data_ov066_0226bdf8;
    MI_CpuCopy8(&m, data_ov066_0226bdf4->buf, 8);
    MI_CpuCopy8(data_ov066_0226bdf4->block, (u8 *) data_ov066_0226bdf4->buf + 8, 0x60);
    data_ov066_0226bdf4->send(data_ov066_0226bdf4->buf, 0x68, 0xffff, (void *) func_ov066_022693f0);
}
