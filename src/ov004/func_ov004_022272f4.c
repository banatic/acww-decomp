/* func_ov004_022272f4 @ 0x022272f4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_022272f4 {
    unsigned char a;
    unsigned char b;
};
extern void func_020109a0(void *self, int a, int b, int c);
void func_ov004_022272f4(unsigned char *self, unsigned char *p)
{
    struct UnkStruct_022272f4 *q, *w;
    int t;
    func_020109a0(self, 0x6d, 3, 0);
    q = (struct UnkStruct_022272f4 *) (p + 0xc);
    t = q->b;
    w = (struct UnkStruct_022272f4 *) (self + 0x7d4);
    w->a = *(unsigned char *) (p + 0xc);
    w->b = t;
}
