/* func_020e8d50 @ 0x020e8d50, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct Node {
    struct Node *prev;
    struct Node *next;
};
struct List {
    struct Node *head;
    struct Node *tail;
};
extern int func_020e8c70(struct List *, struct Node *);

int func_020e8d50(struct List *list, struct Node *node, struct Node *after)
{
    if (after == 0) {
        return func_020e8c70(list, node);
    }
    if (node == 0) {
        goto fail;
    }
    node->next = after->next;
    node->prev = after;
    after->next = node;
    if (node->next != 0) {
        node->next->prev = node;
    } else {
        list->tail = node;
    }
    goto success;
fail:
    return 0;
success:
    return 1;
}
