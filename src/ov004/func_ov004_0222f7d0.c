/* func_ov004_0222f7d0 @ 0x0222f7d0, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055060(void *, int, int, int, int, int);
extern int func_ov004_0222c2dc(void *, int);
extern int func_ov004_0222c3c4(void *, int);

int func_ov004_0222f7d0(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x1), 0x1, 0x1000, 0x0, 0x0);
    func_ov004_0222c2dc(self + 0x250, 0x4d7);
    return 0x1;
}
