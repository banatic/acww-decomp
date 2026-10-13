/* func_ov066_0226bb7c @ 0x0226bb7c, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    int unk_00;
    struct Node *next;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
};

void func_ov066_0226bb7c(struct Node *node, int count)
{
    unsigned short i = 0;
    if (count > 0) {
        unsigned short v = i;
        do {
            i = i + 1;
            node->unk_08 = v;
            node->unk_0A = v;
            node->unk_0C = v;
            node = node->next;
        } while (i < count);
    }
}
