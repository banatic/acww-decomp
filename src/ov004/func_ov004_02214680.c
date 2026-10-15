/* func_ov004_02214680 @ 0x02214680, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *p, int a, int b);
extern void *func_ov004_0220e220(void *p);
extern void *func_ov004_0220d9f8(void *p, int a);
extern int func_ov004_0220e4b0(void *p);
extern int func_02055e00(void *p);
extern void func_02056440(void *p, int a, void *b, int c, int d, int e);
extern int func_ov004_0221078c(void *self);

int func_ov004_02214680(char *self)
{
    void *p;

    func_ov004_0220d280(self + 0x740, 1, 0);
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0) != 0) {
        p = func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0);
        if (func_ov004_0220e4b0(self + 0x7c4) != 0) {
            func_02056440(self + 0x7c4, func_02055e00(self + 0x538), p, 1, 0x1000, 0);
        }
    }
    func_ov004_0221078c(self);
    return 1;
}
