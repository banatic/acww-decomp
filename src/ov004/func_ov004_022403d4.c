/* func_ov004_022403d4 @ 0x022403d4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02240f2c(void *, int, int, int, int, int, int);

void func_ov004_022403d4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02240f2c(self, 0x5a, 0x40, 0x0, 0x0, 0x0, 0xf);
    *(int *) (self + 0x4c) = *(int *) (self + 0x2c8);
}
