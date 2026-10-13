/* func_020e8e34 @ 0x020e8e34, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node2 Node2;
struct Node2 {
    void *parent;
    Node2 *child;
    void *prevsib;
    Node2 *nextsib;
};
struct Root {
    Node2 *first;
};

int func_020e8e34(struct Root *self, Node2 *node, Node2 *parent)
{
    Node2 *cur;
    Node2 *nx;
    if (node == 0) {
        goto fail;
    }
    if (parent != 0) {
        node->parent = parent;
        cur = parent->child;
        if (cur == 0) {
            parent->child = node;
            goto success;
        }
        nx = cur->nextsib;
        if (nx != 0) {
            do {
                cur = nx;
                nx = cur->nextsib;
            } while (nx != 0);
        }
        cur->nextsib = node;
        node->prevsib = cur;
        goto success;
    } else {
        if (self->first != 0) {
            return 0;
        }
        self->first = node;
        goto success;
    }
fail:
    return 0;
success:
    return 1;
}
