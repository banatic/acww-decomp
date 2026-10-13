/* func_020ff83c @ 0x020ff83c, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Node;
struct List {
    struct Node *first;
    int count;
};
struct Node {
    struct Node *a;
    struct Node *b;
};
struct Node *func_020ff83c(struct List *list, struct Node *node)
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
