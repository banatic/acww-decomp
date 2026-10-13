/* func_ov066_0226bbb4 @ 0x0226bbb4, 0x98 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    unsigned char pad_08[0x20 - 8];
    u8 id;
} Node;
typedef struct Cfg {
    unsigned char pad_00[0x1a];
    u16 size;
} Cfg;
extern Cfg *data_ov066_0226bdec;
void *func_ov066_02266908(u32 size, u32 align);
void MI_CpuFill8(void *dest, u8 data, u32 size);

Node *func_ov066_0226bbb4(int n)
{
    u32 stride;
    u32 total;
    Node *cur;
    Node *head;
    u16 i;
    Node *prev;
    int last;
    stride = (data_ov066_0226bdec->size + 0x43) & ~0x1f;
    total = stride * n;
    cur = (Node *) func_ov066_02266908(total, 0x20);
    MI_CpuFill8(cur, 0, total);
    head = cur;
    last = n - 1;
    i = 0;
    {
        u8 b = (u8) i;
        while ((int) i < last) {
            cur->id = b;
            i = (u16) (i + 1);
            cur->next = (Node *) ((u8 *) cur + stride);
            prev = cur;
            cur = cur->next;
            cur->prev = prev;
        }
    }
    cur->id = (u8) last;
    cur->next = head;
    head->prev = cur;
    return head;
}
