/* func_ov004_02212d44 @ 0x02212d44, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);

int func_ov004_02212d44(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_022101e4(self, 0x0, 0x3, 0x1000, 0x0);
    return 0x1;
}
