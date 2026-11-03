/* list_ops: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02065c68 @ 0x02065c68, 0x8 bytes, Thumb
 * func_02065c2c @ 0x02065c2c, 0x3c bytes, Thumb
 * func_02065c1c @ 0x02065c1c, 0x10 bytes, Thumb
 * func_02065c00 @ 0x02065c00, 0x1c bytes, Thumb
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

struct Node_02065c00 {
    int unk_00;
    struct Node_02065c00 *next;
    int key;
};

extern int func_020e8d50(List *list, Node *new_node, Node *prev);
extern int func_020e8ca8(void *, void *);

void func_02065c68(int *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

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

int func_02065c1c(void *argument0, void *argument1)
{
    func_020e8ca8((void *) argument0, (void *) argument1);
    return 1;
}

struct Node_02065c00 *func_02065c00(struct Node_02065c00 **head, int key)
{
    struct Node_02065c00 *node;

    if (key == 0) {
        return 0;
    }
    node = *head;
    while (node) {
        if (key == node->key) {
            return node;
        }
        node = node->next;
    }
    return 0;
}
