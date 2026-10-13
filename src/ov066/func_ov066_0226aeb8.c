/* func_ov066_0226aeb8 @ 0x0226aeb8, 0x4c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node {
    struct Node *next;
    unsigned char pad[6];
    unsigned short flags1;
    unsigned short flags2;
} Node;

typedef struct ListObj {
    unsigned char pad[0x10];
    Node *head;
} ListObj;

extern ListObj *data_ov066_0226be08;

void func_ov066_0226aeb8(int bit)
{
    Node *head;
    Node *cur;
    unsigned short mask;

    mask = ~(1 << bit);
    head = data_ov066_0226be08->head;
    cur = head;
    do {
        cur->flags1 &= mask;
        cur->flags2 &= mask;
        cur = cur->next;
    } while (head != cur);
}
