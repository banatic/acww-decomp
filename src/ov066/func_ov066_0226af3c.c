/* func_ov066_0226af3c @ 0x0226af3c, 0x14c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226af3c {
    struct UnkStruct_0226af3c **unk_00;
    struct UnkStruct_0226af3c *unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    char pad0[0x20 - 0xe];
    char data[4];
} UnkStruct_0226af3c;

typedef struct Node {
    char pad0[0x22];
    u16 unk_22;
} Node;

typedef struct Ctl {
    char pad0[2];
    signed char count;  // 0x02
    signed char unk_03; // 0x03
    u8 x : 1;           // 0x04 bit 0
    u8 y : 1;
    u8 z : 1;
    u8 w : 1; // bit 3
    u8 rest : 4;
    char pad_05[0x10 - 5];
    UnkStruct_0226af3c *unk_10; // 0x10
    UnkStruct_0226af3c *unk_14; // 0x14
    Node **list;                // 0x18
} Ctl;

extern Ctl *data_ov066_0226be08;
extern void func_ov066_0226b594(Node *n);
extern int func_ov066_0226b088(UnkStruct_0226af3c *e, Node *n);
extern int func_ov066_0226ae50(int a, void *p, int b, int c, void *fn);
extern void func_ov066_0226b71c(void);

void func_ov066_0226af3c(void)
{
    Ctl *g;
    UnkStruct_0226af3c *cur;
    Node *nd;
    UnkStruct_0226af3c *e;

    g = data_ov066_0226be08;
    if (g->count >= 1) {
        return;
    }
    cur = 0;
    nd = g->list[0];
    if (g->unk_14 != 0) {
        cur = g->unk_14;
        if (cur->unk_04 == g->unk_10) {
            g->unk_14 = 0;
        } else {
            g->unk_14 = cur->unk_04;
        }
    } else {
        e = *g->unk_10->unk_00;
        if (e->unk_0A == 0 || e->unk_0A == e->unk_0C) {
            if (g->w) {
                func_ov066_0226b594(nd);
                nd->unk_22 |= 1;
                data_ov066_0226be08->unk_03++;
            }
            if (func_ov066_0226b088(data_ov066_0226be08->unk_10, nd) != 0) {
                cur = data_ov066_0226be08->unk_10;
                data_ov066_0226be08->unk_10 = cur->unk_04;
            }
        }
    }
    if (cur == 0) {
        return;
    }
    if (cur->unk_0A == 0) {
        return;
    }
    data_ov066_0226be08->count++;
    func_ov066_0226ae50(0xd, (u8 *) cur + 0x20, cur->unk_08, cur->unk_0A, (void *) func_ov066_0226b71c);
}
