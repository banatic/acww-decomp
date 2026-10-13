/* func_ov004_02228ae0 @ 0x02228ae0, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f328(void *self, int msg);
void func_ov004_02228ae0(unsigned char *self)
{
    *(short *) (self + 0x7d4) = (short) (*(short *) (self + 0x8e) + 0x4000);
    func_020109a0(self, 0x25, 0, 0);
    func_0200f328(self, 0x4c9);
}
