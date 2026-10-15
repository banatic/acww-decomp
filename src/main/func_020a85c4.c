/* func_020a85c4 @ 0x020a85c4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
} ctx;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} node;

extern void func_020a8718(ctx *p0, unsigned char *out1, unsigned char *out2);
extern int func_020a8a34(node *ptr, unsigned int base);

unsigned int func_020a85c4(ctx *p0, unsigned char *p1, node *p2, unsigned char *p3, node *p4)
{
    unsigned char b0, b1;
    node *arr[2];
    unsigned int base;
    unsigned int sum;
    unsigned int i;

    func_020a8718(p0, &b0, &b1);
    *p1 = b0;
    *p3 = b1;

    arr[0] = p2;
    arr[1] = p4;

    base = p0->unk_0C + p0->unk_08 + 2;

    sum = 2;
    for (i = 0; i < 2; i++) {
        node *ptr = arr[i];
        unsigned int v;
        func_020a8a34(ptr, base);
        v = ptr->unk_04 + 2;
        sum += v;
        base += v;
    }

    return sum;
}
