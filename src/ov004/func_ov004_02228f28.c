/* func_ov004_02228f28 @ 0x02228f28, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_02228f28 {
    int a;
    int b;
    short c;
};

extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_0200f328(void *self, int a);
extern void func_ov004_02228fbc(void *p, int a, int b, short c);
extern void func_ov004_02228fa0(void *p, int a, int b, short c);

void func_ov004_02228f28(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_02228f28 *q;
    volatile int t[3];
    int a, b, x;
    short s;

    func_020109a0(self, 0x23, 0, 0);
    func_0200f328(self, 0x4c5);
    q = (struct UnkStruct_02228f28 *) (p + 0xc);
    s = q->c;
    b = q->b;
    x = *(int *) (self + 0x60);
    a = q->a;
    t[0] = a;
    t[1] = x;
    t[2] = b;
    func_ov004_02228fbc(self + 0x7d4, a, b, s);
    func_ov004_02228fa0(self + 0x8f0, t[0], t[2], s);
}
