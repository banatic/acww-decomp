/* func_ov004_0222b494 @ 0x0222b494, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222b4dc(void *dst, int b);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f328(void *self, int msg);
void func_ov004_0222b494(unsigned char *self, unsigned char *p)
{
    int b;
    b = *(unsigned char *) (p + 0xc);
    func_ov004_0222b4dc(self + 0x8f0, b);
    func_020109a0(self, b != 0 ? 0xd : 0x10, 3, 0);
    func_0200f328(self, 0x4a4);
}
