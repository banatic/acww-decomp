/* func_ov004_0222a404 @ 0x0222a404, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222a404 {
    int a;
    int b;
    short c;
};
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern void func_ov004_0222a488(void *p, int a, int b, short c);
extern void func_ov004_0222a46c(void *p, int a, int b, short c);
void func_ov004_0222a404(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222a404 *q;
    int a, b;
    short s;
    func_020109a0(self, 0x1a, 3, 0);
    q = (struct UnkStruct_0222a404 *) (p + 0xc);
    a = q->a;
    b = q->b;
    s = q->c;
    func_ov004_0222a488(self + 0x7d4, a, b, s);
    func_ov004_0222a46c(self + 0x8f0, a, b, s);
}
