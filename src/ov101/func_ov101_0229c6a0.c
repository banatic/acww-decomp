/* func_ov101_0229c6a0 @ 0x0229c6a0, 0x34 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229c878(char *);
extern int func_ov101_0229c868(char *);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_0220a374(char *, int);

void func_ov101_0229c6a0(char *self)
{
    int a = func_ov101_0229c878(self);
    int b = func_ov101_0229c868(self);
    func_ov002_0220a0b4(self + 0x229c, a, b);
    func_ov002_0220a374(self + 0x229c, 1);
}
