/* func_ov004_0222654c @ 0x0222654c, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222654c {
    int a;
    int b;
    int c;
};
extern void func_020109fc(void *self, int a, int b, int c);
extern void func_ov004_022265c0(void *dst, struct UnkStruct_0222654c v, int a, int b);
extern void func_ov004_022265b8(void *dst, int a, int c);
void func_ov004_0222654c(unsigned char *self, unsigned char *p)
{
    struct UnkStruct_0222654c *q;
    struct UnkStruct_0222654c v;
    q = (struct UnkStruct_0222654c *) (p + 0xc);
    if (*(int *) (self + 0x704) != 1) {
        func_020109fc(self, 1, 3, 0);
    }
    v.a = q->a;
    v.b = q->b;
    v.c = q->c;
    func_ov004_022265c0(self + 0x7d4, v, *(int *) (self + 0x98), 0x400);
    func_ov004_022265b8(self + 0x8f0, v.a, v.c);
}
