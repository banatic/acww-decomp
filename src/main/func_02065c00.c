/* func_02065c00 @ 0x02065c00, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    int unk_00;
    struct Node *next;
    int key;
};

struct Node *func_02065c00(struct Node **head, int key)
{
    struct Node *node;

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
