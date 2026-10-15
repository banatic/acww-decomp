/* func_ov004_02228570 @ 0x02228570, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02228570 {
    int a;
    int b;
    short c;
    unsigned char d;
};
extern void func_ov004_02228610(void *p, int k, int a, int b, int s);
extern void func_ov004_022285e8(void *p, int k, int a, int b, int s);
void func_ov004_02228570(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_02228570 *q;
    int k, a, b, s;
    q = (struct UnkStruct_02228570 *) (p + 0xc);
    k = q->d;
    a = q->a;
    b = q->b;
    s = q->c;
    func_ov004_02228610(self + 0x7d4, k, a, b, s);
    func_ov004_022285e8(self + 0x8f0, k, a, b, s);
    *(unsigned char *) (self + 0x2e4) = 1;
}
