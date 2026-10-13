/* func_0205c080 @ 0x0205c080, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node;
extern struct Node *data_021c9aa8;

struct Node {
    unsigned char state;
    void (*func4)(void);
    void (*func8)(void);
    unsigned int unk_0C;
    unsigned int unk_10;
    void (*unk_14)(void);
    struct Node *next;
};

void func_0205c080(void)
{
    struct Node *node = data_021c9aa8;
    while (node) {
        if (node->state == 0) {
            node->state = 1;
            node->unk_0C = node->unk_10;
            if (node->func8) {
                node->func8();
            }
        }
        if (node->func4) {
            node->func4();
        }
        if (node->state == 2) {
            node->state = 1;
            node->unk_0C = node->unk_10;
            node->func8 = node->unk_14;
            if (node->func8) {
                node->func8();
            }
        }
        node = node->next;
    }
}
