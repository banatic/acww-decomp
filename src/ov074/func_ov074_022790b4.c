/* func_ov074_022790b4 @ 0x022790b4, 0x58 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern unsigned int data_ov074_02279d4c;
extern Pair data_ov074_02279b90;
extern Pair data_ov074_02279b50;
extern Pair data_ov074_02279d74[2];

void func_ov074_022790b4(unsigned int *out, int idx)
{
    unsigned int guard;
    unsigned int off;
    Pair *base;
    Pair *p;
    unsigned int a, b;

    guard = data_ov074_02279d4c;
    if (!(guard & 1)) {
        data_ov074_02279d74[0] = data_ov074_02279b90;
        data_ov074_02279d74[1] = data_ov074_02279b50;
        guard |= 1;
        data_ov074_02279d4c = guard;
    }
    off = idx * 8;
    base = data_ov074_02279d74;
    p = (Pair *) ((unsigned char *) base + off);
    a = p->a;
    b = p->b;
    out[45] = a;
    out[46] = b;
}
