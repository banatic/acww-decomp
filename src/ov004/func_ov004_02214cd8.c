/* func_ov004_02214cd8 @ 0x02214cd8, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055060(void *, int, int, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0220da04(int, int);
extern int func_ov004_0220e220(void *);
extern void func_ov004_022101e4(void *, int, int, int, int);

int func_ov004_02214cd8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_022101e4(self, 0x0, 0x0, 0x1000, 0x0);
    func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0x0), 0x0, 0x0, 0x0, 0x0);
    return 0x1;
}
