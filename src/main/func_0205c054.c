/* func_0205c054 @ 0x0205c054, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node {
    unsigned char type;
    char pad_01[7];
    void (*func)(void);
    char pad_0C[12];
    struct Node *next;
} Node;

extern Node *data_021c9aa8;

void func_0205c054(void)
{
    Node *p;
    p = data_021c9aa8;
    while (p) {
        if ((unsigned char) (p->type + 0xFF) <= 1) {
            if (p->func != 0) {
                p->func();
            }
        }
        p = p->next;
    }
}
