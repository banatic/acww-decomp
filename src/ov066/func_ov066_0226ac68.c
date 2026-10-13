/* func_ov066_0226ac68 @ 0x0226ac68, 0x134 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 k : 2;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 idx : 4;
    u8 unk_01;
} Hdr;

typedef struct Node {
    char pad0[4];
    struct Node *unk_04;
    char pad_08[0x22 - 8];
    u16 unk_22;
    char data[2];
} Node;

typedef struct UnkStruct_0226ac68 {
    char pad0[0xa];
    u16 unk_0A;
    u16 unk_0C;
} UnkStruct_0226ac68;

typedef struct Ctl {
    u8 unk_00;
    char pad0[0x10 - 1];
    int unk_10;
    UnkStruct_0226ac68 *unk_14;
    Node **list;
} Ctl;

extern Ctl *data_ov066_0226be08;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern UnkStruct_0226ac68 *func_ov066_0226ad9c(int idx, int g10);

void func_ov066_0226ac68(int a, u8 *b, int c)
{
    Hdr h;
    UnkStruct_0226ac68 *e;
    Node *nd;

    MI_CpuCopy8(b, &h, 2);
    if (h.b3) {
        e = func_ov066_0226ad9c(h.idx, data_ov066_0226be08->unk_10);
        if (e != 0) {
            e->unk_0C |= e->unk_0A & (1 << a);
        }
    }
    if (h.k == 3) {
        if (data_ov066_0226be08->unk_14 != 0) {
            return;
        }
        e = func_ov066_0226ad9c(h.idx, data_ov066_0226be08->unk_10);
        if (e != 0) {
            data_ov066_0226be08->unk_14 = e;
        }
        return;
    }
    if (h.k == 2) {
        return;
    }
    nd = data_ov066_0226be08->list[a];
    MI_CpuCopy8(b, (u8 *) nd + 0x24 + a * data_ov066_0226be08->unk_00, c);
    nd->unk_22 |= 1 << a;
    data_ov066_0226be08->list[a] = nd->unk_04;
}
