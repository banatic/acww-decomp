/* func_ov003_02214bc8 @ 0x02214bc8, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02214c00(void *, int argument1);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern int func_0200f328(void *, int);

void func_ov003_02214bc8(void *self, void *other, int previous)
{
    unsigned char c;
    char *base;

    c = *(unsigned char *) ((char *) other + 0xc);
    *(char *) ((char *) self + 0x7d4) = c;
    base = (char *) self + 0x8f0;
    func_ov003_02214c00(base, c);
    func_020109a0(self, 0x5a, 3, 3);
    func_0200f328(self, 0x4f);
}
