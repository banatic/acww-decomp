/* func_ov004_02215788 @ 0x02215788, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d208(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);
extern int func_ov004_02210744(void *);
extern int func_ov004_02215d80(void *, int);

int func_ov004_02215788(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_0220d208(self + 0x848, 0x0, 0x1, 0x0);
    func_ov004_02215d80(self, 0x0);
    func_ov004_02210054(self, 0x0, 0x3, 0x1000);
    func_ov004_02210744(self);
    return 0x1;
}
