/* func_0205c024 @ 0x0205c024, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    char unk_00;
    unsigned char pad_01[3];
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int pad_14;
    struct Node *unk_18;
};

extern struct Node *data_021c9aac;
extern struct Node *data_021c9aa8;

int func_0205c024(struct Node *node, int a, int b, int c)
{
    node->unk_10 = a;
    node->unk_0C = 0;
    node->unk_08 = b;
    node->unk_04 = c;
    node->unk_18 = 0;
    node->unk_00 = 0;
    if (data_021c9aac) {
        data_021c9aac->unk_18 = node;
        data_021c9aac = node;
    } else {
        data_021c9aac = node;
        data_021c9aa8 = node;
    }
    return 1;
}
