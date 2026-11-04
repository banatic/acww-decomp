/* process_7: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ee934 @ 0x020ee934, 0x30 bytes, ARM
 * func_020ee8a8 @ 0x020ee8a8, 0x8c bytes, ARM
 */

#include "types.h"

typedef struct Node Node;

struct Node {
    u8 pad_00[4];
    Node *next;
    u8 pad_08[0xc - 8];
    u16 key;
};

typedef struct {
    Node *head;
} List;

extern void func_020ee964(void);
extern void func_020ee9a0(void);
extern int func_020e8ca8(List *list, Node *item);
extern int func_020e8d50(List *list, Node *item, Node *prev);

void func_020ee934(int param)
{
    if (param != 0) {
        func_020ee964();
    } else {
        func_020ee9a0();
    }
}

int func_020ee8a8(List *list, Node *item)
{
    Node *head;
    Node *prev;
    Node *next;

    head = list->head;
    if (item == 0) {
        return 0;
    }
    if (head == 0) {
        return func_020e8ca8(list, item);
    }
    if (head->key > item->key) {
        return func_020e8d50(list, item, 0);
    }
    prev = head;
    while (prev->next != 0 && prev->next->key <= ((volatile Node *) item)->key) {
        prev = prev->next;
    }
    return func_020e8d50(list, item, prev);
}
