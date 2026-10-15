/* func_ov004_02217360 @ 0x02217360, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0220da04(int, int);
extern int func_ov004_0220e220(void *);
extern void func_ov004_02210054(void *, int, int, int);

int func_ov004_02217360(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    if (*(int *) (self + 0x780) == 0xf) {
        func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0x0);
        func_ov004_02210054(self, 0x0, 0x1, 0x1000);
    } else {
        func_ov004_02210054(self, 0x0, 0x1, 0x1000);
    }
    return 0x1;
}
