/* func_ov105_0229ddd4 @ 0x0229ddd4, 0x68 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b57c(const char *p);
extern int func_0208e4bc(const char *p);
extern int func_ov002_0220b5ec(const char *p, int);
extern int func_ov002_0220b59c(const char *p, int);
extern void func_ov002_0220a0b4(const char *p, int, int);
extern void func_ov105_0229cfc0(const char *p);
extern void func_ov002_02208090(const char *p, int);
extern void func_ov002_022080a0(const char *p, int);

void func_ov105_0229ddd4(char *self)
{
    if (func_ov002_0220b57c(self + 0x2d40) != 0) {
        if (func_0208e4bc(self + 0x24a4) != 0) {
            int a = func_ov002_0220b5ec(self + 0x2d40, 1);
            int b = func_ov002_0220b59c(self + 0x2d40, 1);
            func_ov002_0220a0b4(self + 0x24a4, a, b);
        }
    } else {
        func_ov105_0229cfc0(self);
        func_ov002_02208090(self, 9);
        func_ov002_022080a0(self, 1);
    }
}
