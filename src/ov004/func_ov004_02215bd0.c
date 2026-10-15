/* func_ov004_02215bd0 @ 0x02215bd0, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d208(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0221078c(void *);
extern int func_ov004_02215d80(void *, int);

int func_ov004_02215bd0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0221078c(self);
    func_ov004_0220d208(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_02215d80(self, 0x1);
    return 0x1;
}
