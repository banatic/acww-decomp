/* func_020e8dbc @ 0x020e8dbc, 0x78 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    struct Node *a;
    struct Node *b;
    struct Node *c;
    struct Node *d;
};

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
