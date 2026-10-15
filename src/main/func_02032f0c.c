/* func_02032f0c @ 0x02032f0c, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Src {
    int a, b, c;
} Src;

typedef struct Node {
    char pad_00[0x14];
    unsigned char unk_14;
    char pad_15[0x1c - 0x15];
    int type;
    char pad_20[0x24 - 0x20];
} Node;

typedef struct Header {
    int count;
    Node arr[1];
} Header;

extern int func_020305b0(Node *p, Src *src, int extra);
extern void func_020eaca0(int *outvec, Src *src, Node *p);
extern int func_020e8ed8(int a, int b);
extern int func_02032cac(int *outp, int val, int type, int b14);

int func_02032f0c(Header *h, Src *src, int extra, int *out, unsigned int mode, int value)
{
    Node *start;
    Node *p;
    int result = 0;
    start = h->arr;
    for (p = start; p < start + h->count; p++) {
        volatile int a, b, c;
        a = src->a;
        b = src->b;
        c = src->c;
        if (func_020305b0(p, src, extra)) {
            int vec[3];
            int combined;
            func_020eaca0(vec, src, p);
            combined = func_020e8ed8(vec[0], vec[2]);
            func_02032cac(out + 3, combined, p->type, p->unk_14);
            result = 1;
        }
    }
    return result;
}
