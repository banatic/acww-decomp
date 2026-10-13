/* func_ov066_0226b088 @ 0x0226b088, 0x148 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226b088 {
    struct UnkStruct_0226b088 **unk_00;
    struct UnkStruct_0226b088 *unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    char pad0[0x20 - 0xe];
    u8 unk_20;
    char pad_21[1];
    u16 unk_22;
    char data[4];
} UnkStruct_0226b088;

typedef struct Ctl {
    u8 unk_00;
    u8 lo : 4;
    u8 hi : 4;
    char pad0[0x18 - 2];
    UnkStruct_0226b088 **list; // 0x18
} Ctl;

typedef struct Cfg {
    char pad0[0xb];
    u8 cnt; // 0x0b
} Cfg;

typedef struct Timer {
    char pad0[0x98];
    u16 unk_98;
} Timer;

extern Ctl *data_ov066_0226be08;
extern Cfg *data_ov066_0226bdec;
extern Timer *data_ov066_0226bdf4;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void func_ov066_0226b1d0(void *p);

int func_ov066_0226b088(UnkStruct_0226b088 *e, UnkStruct_0226b088 *n)
{
    Ctl *g;
    u16 mask;
    u16 i;
    u8 stride;
    u16 total;
    u8 *src;
    u8 *dst;
    u8 old;
    int ret;

    ret = 0;
    mask = n->unk_22;
    if (mask != 0) {
        g = data_ov066_0226be08;
        src = (u8 *) n + 0x24;
        total = 4;
        stride = g->unk_00;
        dst = (u8 *) e + 0x24;
        e->unk_22 = mask;

        old = data_ov066_0226be08->lo;
        data_ov066_0226be08->lo = old + 1;
        e->unk_20 = old;

        for (i = 0; i < data_ov066_0226bdec->cnt; i++) {
            if (mask & (1 << i)) {
                MI_CpuCopy8(src + stride * i, dst, stride);
                dst += stride;
                total = total + stride;
            }
            g = data_ov066_0226be08;
            if (g->list[i] == n) {
                g->list[i] = n->unk_04;
            }
        }

        n->unk_22 = 0;
        e->unk_0A = data_ov066_0226bdf4->unk_98;
        e->unk_0C = 0;
        e->unk_08 = total;
        func_ov066_0226b1d0((u8 *) e + 0x20);
        ret = 1;
    }
    return ret;
}
