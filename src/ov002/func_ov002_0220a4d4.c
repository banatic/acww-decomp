/* func_ov002_0220a4d4 @ 0x0220a4d4, 0x22 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e9e0(char *self, int *a, int *b);
extern int func_ov002_0220a51c(char *self);

int func_ov002_0220a4d4(char *self)
{
    int a;
    int b;

    func_0208e9e0(self, &a, &b);
    return b + func_ov002_0220a51c(self) + 7;
}
