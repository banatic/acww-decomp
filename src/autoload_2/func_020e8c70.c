/* func_020e8c70 @ 0x020e8c70, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node Node;
struct Node {
    Node *prev;
    Node *next;
};

typedef struct List List;
struct List {
    Node *head;
    Node *tail;
};

int func_020e8c70(List *list, Node *node)
{
    if (node != 0) {
        if (list->head != 0) {
            list->head->prev = node;
            node->next = list->head;
        } else {
            list->tail = node;
        }
        list->head = node;
    } else {
        return 0;
    }
    return 1;
}
