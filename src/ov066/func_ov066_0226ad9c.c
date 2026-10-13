/* func_ov066_0226ad9c @ 0x0226ad9c, 0x30 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    struct Node *next;
    unsigned char pad_04[0x1c];
    unsigned char flag;
};

struct Node *func_ov066_0226ad9c(unsigned char key, struct Node *sentinel)
{
    struct Node *p;
    p = sentinel->next;
    if (sentinel != p) {
        do {
            if (p->flag == key) {
                return p;
            }
            p = p->next;
        } while (sentinel != p);
    }
    return 0;
}
