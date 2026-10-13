/* func_01ffcc30 @ 0x01ffcc30, 0x30 bytes, Thumb, module itcm
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    int unk_00;
    int unk_04;
    int unk_08;
    void (*func)(void);
    int unk_10;
    int unk_14;
    struct Node *next;
};

extern struct Node *data_021c9aa8;

void func_01ffcc30(void)
{
    struct Node *p;
    if ((unsigned int) (*(volatile unsigned short *) 0x04000006) >= 0xc0u) {
        return;
    }
    p = data_021c9aa8;
    if (p) {
        do {
            if (p->func) {
                p->func();
            }
            p = p->next;
        } while (p);
    }
}
