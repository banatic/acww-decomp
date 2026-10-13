/* func_02065c2c @ 0x02065c2c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node Node;
struct Node {
    int unk_00;
    Node *next;
    unsigned char priority;
};

typedef struct List {
    Node *head;
    Node *tail;
} List;

extern void func_020e8d50(List *list, Node *new_node, Node *prev);

int func_02065c2c(List *list, Node *new_node)
{
    Node *prev;
    Node *curr;
    if (list->head == 0) {
        list->head = new_node;
        list->tail = new_node;
        return 1;
    }
    prev = list->head;
    curr = prev->next;
    while (curr != 0) {
        if (curr->priority > new_node->priority) {
            func_020e8d50(list, new_node, prev);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    func_020e8d50(list, new_node, prev);
    return 1;
}
