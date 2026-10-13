/* func_020ff8ec @ 0x020ff8ec, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

void func_020ff8ec(List *list, Node *node)
{
    if (list->head == 0) {
        list->head = node;
        node->prev = 0;
        node->next = node->prev;
    } else {
        node->prev = list->head;
        node->next = 0;
        list->head->next = node;
        list->head = node;
    }
    list->count++;
}
