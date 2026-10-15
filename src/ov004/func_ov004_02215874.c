/* func_ov004_02215874 @ 0x02215874, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d208(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_0221078c(void *);
extern int func_ov004_02215d80(void *, int);

int func_ov004_02215874(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0220d208(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_02215d80(self, 0x1);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}
