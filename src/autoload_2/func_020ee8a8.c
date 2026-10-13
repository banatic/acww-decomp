/* func_020ee8a8 @ 0x020ee8a8, 0x8c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
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
extern int func_020e8ca8(List *list, Node *item);
extern int func_020e8d50(List *list, Node *item, Node *prev);

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
