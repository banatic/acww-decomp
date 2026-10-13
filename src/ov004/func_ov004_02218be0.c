/* func_ov004_02218be0 @ 0x02218be0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);

int func_ov004_02218be0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_02210054(self, 0x1, 0x0, 0x1000);
    return 0x1;
}
