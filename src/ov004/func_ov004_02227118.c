/* func_ov004_02227118 @ 0x02227118, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *self, int a, int b, unsigned short d);

void func_ov004_02227118(void *self, void *msg, int previous)
{
    unsigned char *d;
    unsigned char b;

    func_020109a0(self, 0x6f, 3, 0);
    b = ((unsigned char *) ((int) msg + 0xc))[1];
    d = (unsigned char *) ((char *) self + 0x7d4);
    d[0] = *((unsigned char *) msg + 0xc);
    d[1] = b;
    d[2] = 0;
}
