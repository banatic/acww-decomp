/* func_0205bfdc @ 0x0205bfdc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    char pad_00[0x18];
    struct Node *next;
};

extern struct Node *data_021c9aa8;
extern struct Node *data_021c9aac;

int func_0205bfdc(struct Node *node)
{
    struct Node *prev;
    if (node == data_021c9aa8) {
        data_021c9aa8 = node->next;
        if (data_021c9aac == node) {
            data_021c9aac = 0;
        }
        return 1;
    }
    prev = data_021c9aa8;
    while (prev) {
        if (prev->next == node) {
            prev->next = prev->next->next;
            if (data_021c9aac == node) {
                data_021c9aac = prev;
            }
            return 1;
        }
        prev = prev->next;
    }
    return 0;
}
