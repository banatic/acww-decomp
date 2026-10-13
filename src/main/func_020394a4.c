/* func_020394a4 @ 0x020394a4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node Node;
typedef struct Container Container;

struct Node {
    unsigned char pad_00[0xa4];
    int unk_A4;
    unsigned char pad_A8[8];
    int unk_B0;
};

struct Container {
    unsigned char pad_00[0x2f4];
    Node *arr[4];
};

void func_020394a4(Container *p)
{
    int i;
    for (i = 0; i < 4; i++) {
        Node *n = p->arr[i];
        if (n != 0) {
            if (n->unk_A4 == 0) {
                if (n->unk_B0 == 0) {
                    p->arr[i] = 0;
                }
            }
        }
    }
    {
        int a;
        for (a = 0; a < 4; a++) {
            if (p->arr[a] == 0) {
                int b;
                for (b = a + 1; b < 4; b++) {
                    if (p->arr[b] != 0) {
                        p->arr[a] = p->arr[b];
                        p->arr[b] = 0;
                        break;
                    }
                }
            }
        }
    }
}
