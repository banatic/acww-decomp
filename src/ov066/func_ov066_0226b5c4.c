/* func_ov066_0226b5c4 @ 0x0226b5c4, 0x158 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Pkt {
    u8 kind : 2;
    u8 done : 1;
    u8 rest : 5;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 data[4];
} Pkt;

typedef struct Ctl {
    u8 unk_00;
    char pad_01[3];
    u8 a : 1;
    u8 b : 1;
    u8 c : 1;
    u8 d : 1;
    u8 v : 1;
    u8 e : 3;
    char pad_05[0x1e - 5];
    u16 unk_1E;
    u8 *unk_20;
    u32 unk_24;
    u32 unk_28;
} Ctl;

extern Ctl *data_ov066_0226be08;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

u16 func_ov066_0226b5c4(Pkt *hdr)
{
    Ctl *g;
    u32 sent;
    u32 total;
    u32 rem;
    u8 *src;
    u8 *dst;
    u32 lim;
    u32 v;
    u8 n;
    u16 ret;

    g = data_ov066_0226be08;
    sent = g->unk_28;
    total = g->unk_24;
    rem = total - sent;
    src = g->unk_20 + sent;
    if (sent == 0) {
        hdr->kind = 0;
        dst = (u8 *) hdr + 8;
        hdr->unk_02 = data_ov066_0226be08->unk_1E;
        hdr->unk_04 = (u16) data_ov066_0226be08->unk_24;
        hdr->unk_06 = (u16) (data_ov066_0226be08->unk_24 >> 16);
        lim = data_ov066_0226be08->unk_00 - 8;
        v = data_ov066_0226be08->unk_24;
        if (v > lim) {
            v = lim;
        }
        n = (u8) v;
        ret = (u16) ((n + 9) & ~1);
    } else {
        hdr->kind = 1;
        dst = (u8 *) hdr + 2;
        lim = data_ov066_0226be08->unk_00 - 2;
        if (rem > lim) {
            rem = lim;
        }
        n = (u8) rem;
        ret = (u16) ((n + 3) & ~1);
    }
    data_ov066_0226be08->unk_28 = data_ov066_0226be08->unk_28 + n;
    hdr->unk_01 = n;
    hdr->done = (data_ov066_0226be08->unk_28 == data_ov066_0226be08->unk_24);
    data_ov066_0226be08->v = hdr->done;
    MI_CpuCopy8(src, dst, n);
    return ret;
}
