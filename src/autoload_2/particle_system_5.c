/* particle_system_5: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ff8ec @ 0x020ff8ec, 0x4c bytes, ARM
 * func_020ff8a8 @ 0x020ff8a8, 0x44 bytes, ARM
 * func_020ff83c @ 0x020ff83c, 0x6c bytes, ARM
 */

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

typedef struct Node_020ff8a8 Node_020ff8a8;

typedef struct List_020ff8a8 List_020ff8a8;

struct Node_020ff8a8 {
    Node_020ff8a8 *next;
    Node_020ff8a8 *prev;
};

struct List_020ff8a8 {
    Node_020ff8a8 *head;
    int count;
};

struct Node_020ff83c;

struct List {
    struct Node_020ff83c *first;
    int count;
};

struct Node_020ff83c {
    struct Node_020ff83c *a;
    struct Node_020ff83c *b;
};

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

Node_020ff8a8 *func_020ff8a8(List_020ff8a8 *list)
{
    Node_020ff8a8 *ret = 0;
    Node_020ff8a8 *node;
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

struct Node_020ff83c *func_020ff83c(struct List *list, struct Node_020ff83c *node)
{
    if (node->a == 0) {
        if (list->first == node) {
            list->first = 0;
        } else {
            node->b->a = 0;
        }
    } else {
        if (list->first == node) {
            list->first = node->a;
            list->first->b = 0;
        } else {
            node->a->b = node->b;
            node->b->a = node->a;
        }
    }
    list->count--;
    return node;
}
