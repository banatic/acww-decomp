/* func_0203ef5c @ 0x0203ef5c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ee34(void *a, void *b);

struct Node {
    int unk_00;
    struct Node *next;
    int unk_08;
    void *key;
};

extern struct Node *data_021c72cc;

void *func_0203ef5c(void *arg)
{
    struct Node *node;
    void *key;

    node = data_021c72cc;
    while (node) {
        key = node->key;
        if (key != arg && func_0203ee34(key, arg) != 0) {
            return key;
        }
        node = node->next;
    }
    return 0;
}
