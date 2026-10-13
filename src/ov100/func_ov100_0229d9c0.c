/* func_ov100_0229d9c0 @ 0x0229d9c0, 0x44 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(char *p);
extern void func_ov002_022096d8(char *p, int v);
extern int func_0208e4bc(char *p);
extern void func_ov100_0229ca9c(char *p);
extern int func_ov002_02208098(char *p, int v);

int func_ov100_0229d9c0(char *self)
{
    int result;
    result = func_ov002_0220909c(self + 0x22d8);
    if (result == 0) {
        return result;
    }
    func_ov002_022096d8(self + 0x22d8, 0);
    if (func_0208e4bc(self + 0x2274)) {
        func_ov100_0229ca9c(self);
    }
    return func_ov002_02208098(self, 0x13);
}
