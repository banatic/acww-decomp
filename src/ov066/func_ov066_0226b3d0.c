/* func_ov066_0226b3d0 @ 0x0226b3d0, 0x1c4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
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

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    u8 pad[0x18];
    Attr attr;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

typedef struct UnkStruct_0226b3d0 {
    u8 unk_00;
    struct {
        u8 lo : 4;
        u8 hi : 4;
    } unk_01;
    s8 unk_02;
    s8 unk_03;
    struct {
        u8 x0 : 1;
        u8 x1 : 1;
        u8 x2 : 1;
        u8 x3 : 1;
        u8 x4 : 1;
        u8 x5 : 1;
        u8 x6 : 1;
        u8 x7 : 1;
    } unk_04;
    u8 pad[0xb];
    Node *cur;
    u8 pad_14[4];
    Queue *q;
} UnkStruct_0226b3d0;

extern UnkStruct_0226b3d0 *data_ov066_0226be08;

extern int func_ov066_0226b5c4(Attr *a);
extern void func_ov066_0226ae50(int a, Attr *b, int c, int d, void (*cb)(void));
extern void func_ov066_0226b738(void);

void func_ov066_0226b3d0(void)
{
    UnkStruct_0226b3d0 *p = data_ov066_0226be08;
    Attr *a;
    int r = 0;

    a = &p->cur->attr;

    if (p->unk_04.x2) {
        a->mode = 3;
        r = 2;
        a->idx = data_ov066_0226be08->unk_01.hi;
    } else if (p->unk_04.x3) {
        if (p->unk_03 < 2) {
            if (!p->unk_04.x4) {
                if (!p->unk_04.x1) {
                    r = func_ov066_0226b5c4(a);
                    data_ov066_0226be08->unk_03 = (s8) (data_ov066_0226be08->unk_03 + 1);
                }
            }
        }
    }

    if (data_ov066_0226be08->q->head != data_ov066_0226be08->q->tail) {
        if (r == 0) {
            a->mode = 2;
            r = 2;
            a->f2 = 0;
        }
        a->f3 = 1;
        a->idx = data_ov066_0226be08->q->tail->attr.raw;
        data_ov066_0226be08->q->tail = data_ov066_0226be08->q->tail->next;
    } else {
        a->f3 = 0;
    }

    if (r != 0) {
        data_ov066_0226be08->unk_02 = (s8) (data_ov066_0226be08->unk_02 + 1);
        func_ov066_0226ae50(0xd, a, r, 1, func_ov066_0226b738);
        data_ov066_0226be08->cur = data_ov066_0226be08->cur->next;
    }

    data_ov066_0226be08->unk_04.x1 = 0;
}
