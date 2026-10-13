/* func_020ff8a8 @ 0x020ff8a8, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node Node;
typedef struct List List;

struct Node {
    Node *next;
    Node *prev;
};

struct List {
    Node *head;
    int count;
};

Node *func_020ff8a8(List *list)
{
    Node *ret = 0;
    Node *node;
    if ((node = list->head) != 0) {
        ret = node;
        list->head = node->next;
        if (list->head) {
            node->next->prev = 0;
        }
        list->count--;
    }
    return ret;
}
