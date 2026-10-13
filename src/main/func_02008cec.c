/* func_02008cec @ 0x02008cec, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02011404(signed short *a, signed short b, unsigned int c, unsigned int d, unsigned int e);
extern void func_020110a0(unsigned char *a, signed short *b);

void func_02008cec(unsigned char *self)
{
    signed short s;

    s = *(signed short *) (self + 0x8e);
    func_02011404(&s, *(signed short *) (self + 0x7d4), 0x800, 0x1770000, 0xc0000);
    func_020110a0(self, &s);
}
