/* func_0203e5f4 @ 0x0203e5f4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    void *unk_00;
    struct Node *next;
    unsigned char pad_08[12];
    unsigned char unk_14;
    unsigned char unk_15;
};

extern struct Node *data_021c72c4;            // 0x021c72c4
extern struct Node *data_021c72b8;            // 0x021c72b8
extern int (*data_020daa28[])(struct Node *); // 0x020daa28
extern void func_020e8ce0(struct Node **list_head, struct Node *node);

void func_0203e5f4(void)
{
    struct Node *node = data_021c72c4;

    while (node) {
        if (data_020daa28[node->unk_15](node)) {
            func_020e8ce0(&data_021c72c4, node);
            data_021c72b8 = node;
            node->unk_14 = 2;
            break;
        }
        node = node->next;
    }
}
