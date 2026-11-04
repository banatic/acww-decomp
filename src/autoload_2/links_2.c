/* links_2: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e8ec0 @ 0x020e8ec0, 0x18 bytes, ARM
 * func_020e8ea8 @ 0x020e8ea8, 0x18 bytes, ARM
 * func_020e8e34 @ 0x020e8e34, 0x74 bytes, ARM
 * func_020e8dbc @ 0x020e8dbc, 0x78 bytes, ARM
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

struct Node {
    struct Node *a;
    struct Node *b;
    struct Node *c;
    struct Node *d;
};

void func_020e8ea8(int *p);

int func_020e8ec0(int x)
{
    func_020e8ea8((int *) x);
    return x;
}

void func_020e8ea8(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

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

int func_020e8dbc(struct Node **pp, struct Node *node)
{
    if (node) {
        if (node->b != 0) {
            return 0;
        }
        if (node->c != 0) {
            node->c->d = node->d;
        } else {
            if (node->a != 0) {
                node->a->b = node->d;
            } else {
                *pp = 0;
            }
        }
        if (node->d != 0) {
            node->d->c = node->c;
        }
        node->c = 0;
        node->d = 0;
        node->a = 0;
    } else {
        return 0;
    }
    return 1;
}
