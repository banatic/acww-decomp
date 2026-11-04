/* links: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e8ce0 @ 0x020e8ce0, 0x70 bytes, ARM
 * func_020e8ca8 @ 0x020e8ca8, 0x38 bytes, ARM
 * func_020e8c70 @ 0x020e8c70, 0x38 bytes, ARM
 */

struct Node {
    struct Node *prev;
    struct Node *next;
};

struct List {
    struct Node *head;
    struct Node *tail;
};

typedef struct Node_020e8ca8 Node_020e8ca8;

struct Node_020e8ca8 {
    Node_020e8ca8 *prev;
    Node_020e8ca8 *next;
};

typedef struct Node_020e8c70 Node_020e8c70;

struct Node_020e8c70 {
    Node_020e8c70 *prev;
    Node_020e8c70 *next;
};

typedef struct List_020e8c70 List_020e8c70;

struct List_020e8c70 {
    Node_020e8c70 *head;
    Node_020e8c70 *tail;
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

int func_020e8ca8(Node_020e8ca8 *r0, Node_020e8ca8 *r1)
{
    if (r1 != 0) {
        if (r0->next != 0) {
            r0->next->next = r1;
            r1->prev = r0->next;
        } else {
            r0->prev = r1;
        }
        r0->next = r1;
    } else {
        return 0;
    }
    return 1;
}

int func_020e8c70(List_020e8c70 *list, Node_020e8c70 *node)
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
