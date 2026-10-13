/* func_ov066_0226b27c @ 0x0226b27c, 0x154 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef union Attr {
    u8 raw;
    struct {
        u8 mode : 2;
        u8 f2 : 1;
        u8 f3 : 1;
        u8 idx : 4;
    };
} Attr;

typedef struct Entry {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} Entry;

typedef struct UnkStruct_0226b27c {
    u8 unk_00;
    u8 pad[0x1b];
    u16 flags;
    u8 pad_1E[0x12];
    Entry *entries;
} UnkStruct_0226b27c;

typedef struct UnkStruct_0226b27c_2 {
    u8 pad[0xb8];
    void (*cb)(int idx, u32 f0, u32 f8);
} UnkStruct_0226b27c_2;

extern UnkStruct_0226b27c *data_ov066_0226be08;
extern UnkStruct_0226b27c_2 *data_ov066_0226bdf4;

extern int func_ov066_022699cc(void);
extern void MI_CpuCopy8(void *src, void *dst, u32 size);

void func_ov066_0226b27c(int idx, u8 *src)
{
    u32 r7 = 0;
    Entry *entry = &data_ov066_0226be08->entries[idx];
    Attr *attr = (Attr *) src;
    u8 *r5;
    u32 mask;

    switch (attr->mode) {
        case 0:
            r5 = src + 8;
            if (*(u16 *) (src + 2) & (1 << func_ov066_022699cc())) {
                u16 hi;
                u16 lo;
                data_ov066_0226be08->flags |= (1 << idx);
                entry->unk_0C = r7;
                hi = *(u16 *) (src + 6);
                lo = *(u16 *) (src + 4);
                entry->unk_08 = ((u32) hi << 16) | lo;
                r7 = entry->unk_08;
                if (r7 > (u32) (data_ov066_0226be08->unk_00 - 8)) {
                    r7 = (u32) (data_ov066_0226be08->unk_00 - 8);
                }
            }
            break;
        case 1:
            r5 = src + 2;
            r7 = src[1];
            break;
    }

    mask = 1 << idx;
    if ((data_ov066_0226be08->flags & mask) == 0) {
        return;
    }

    if (entry->unk_0C + r7 <= entry->unk_04) {
        MI_CpuCopy8(r5, (void *) (entry->unk_00 + entry->unk_0C), r7);
        entry->unk_0C += r7;
    }

    if (entry->unk_08 != entry->unk_0C) {
        return;
    }

    data_ov066_0226be08->flags ^= mask;
    if (data_ov066_0226bdf4->cb != 0) {
        data_ov066_0226bdf4->cb(idx, entry->unk_00, entry->unk_08);
    }
}
