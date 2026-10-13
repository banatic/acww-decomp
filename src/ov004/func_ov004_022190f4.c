/* func_ov004_022190f4 @ 0x022190f4, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220cfec(void *, int);
extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);

int func_ov004_022190f4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210054(self, 0x1, 0x1, 0x1000);
    func_ov004_0220cfec(self + 0x764, 0x0);
    return 0x1;
}
