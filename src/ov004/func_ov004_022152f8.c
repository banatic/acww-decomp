/* func_ov004_022152f8 @ 0x022152f8, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022152f8 {
    int a;
    int b;
    int c;
};
extern void func_02054cf4(void *p, unsigned char *c);
void func_ov004_022152f8(unsigned char *self, int idx, unsigned char *c)
{
    unsigned char *base, *p, *q;
    struct UnkStruct_022152f8 *v;
    int *dst;
    int off, n;

    base = *(unsigned char **) (c + 0xd4);
    off = *(unsigned short *) (base + 6);
    n = *(unsigned short *) (base + off);
    p = base + off + n * idx;
    q = base + *(int *) (p + 4);
    v = (struct UnkStruct_022152f8 *) (q + 4);
    dst = *(int **) (c + 0xb4);
    dst[0x13] = v->a;
    dst[0x14] = v->b;
    dst[0x15] = v->c;
    func_02054cf4(self + 0x538, c);
}
