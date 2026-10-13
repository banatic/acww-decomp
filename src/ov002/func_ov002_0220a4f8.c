/* func_ov002_0220a4f8 @ 0x0220a4f8, 0x22 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e9e0(char *self, int *a, int *b);
extern int func_ov002_0220a530(char *self);

int func_ov002_0220a4f8(char *self)
{
    int a;
    int b;

    func_0208e9e0(self, &a, &b);
    return a + func_ov002_0220a530(self) + 7;
}
