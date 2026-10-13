/* func_020e8ce0 @ 0x020e8ce0, 0x70 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    struct Node *prev;
    struct Node *next;
};

struct List {
    struct Node *head;
    struct Node *tail;
};

int func_020e8ce0(struct List *list, struct Node *node)
{
    if (node) {
        if (node->prev != 0) {
            node->prev->next = node->next;
        } else if (node == list->head) {
            list->head = node->next;
        }
        if (node->next != 0) {
            node->next->prev = node->prev;
        } else if (node == list->tail) {
            list->tail = node->prev;
        }
        node->prev = 0;
        node->next = 0;
    } else {
        return 0;
    }
    return 1;
}
