/* func_ov066_0226ab28 @ 0x0226ab28, 0x140 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Node {
    char pad0[4];
    struct Node *next; // 0x04
    char pad_08[0x20 - 8];
    u8 unk_20; // 0x20
} Node;

typedef struct Ctl {
    u8 unk_00;
    u8 lo : 4;         // 0x01 bits 0..3
    u8 hi : 4;         // 0x01 bits 4..7
    signed char count; // 0x02
    u8 unk_03;
    u8 x : 1; // 0x04 bit 0
    u8 y : 1; // bit 1
    u8 z : 1; // bit 2
    u8 rest : 5;
    char pad0[0x18 - 5];
    Node **list; // 0x18
} Ctl;

typedef struct UnkStruct_0226ab28 {
    char pad0[0xc];
    u8 *item; // 0x0c
    u16 unk_10;
    u16 unk_12;
} UnkStruct_0226ab28;

extern Ctl *data_ov066_0226be08;
extern void func_ov066_0226ac68(int h, u8 *p, int c);
extern void func_ov066_0226b1d0(u8 *p);

void func_ov066_0226ab28(UnkStruct_0226ab28 *q)
{
    u8 *p;
    Node *n;

    if (q->unk_10 == 0) {
        return;
    }
    if (q->unk_12 != 0) {
        func_ov066_0226ac68(q->unk_12, q->item, q->unk_10);
        return;
    }
    p = q->item;
    if (data_ov066_0226be08->x || *p == ((data_ov066_0226be08->lo + 1) & 0xf)) {
        n = *data_ov066_0226be08->list;
        n->unk_20 = *p;
        *data_ov066_0226be08->list = n->next;
        func_ov066_0226b1d0(p);
        data_ov066_0226be08->x = 0;
        data_ov066_0226be08->z = 0;
        data_ov066_0226be08->lo = *p;
        return;
    }
    if (*p != ((data_ov066_0226be08->lo + 2) & 0xf)) {
        data_ov066_0226be08->y = 1;
        return;
    }
    data_ov066_0226be08->z = 1;
    data_ov066_0226be08->hi = (data_ov066_0226be08->lo + 1) & 0xf;
}
