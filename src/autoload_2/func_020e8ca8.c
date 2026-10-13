/* func_020e8ca8 @ 0x020e8ca8, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node Node;
struct Node {
    Node *prev;
    Node *next;
};

int func_020e8ca8(Node *r0, Node *r1)
{
    if (r1 != 0) {
        if (r0->next != 0) {
            r0->next->next = r1;
            r1->prev = r0->next;
        } else {
            r0->prev = r1;
        }
        r0->next = r1;
    } else {
        return 0;
    }
    return 1;
}
