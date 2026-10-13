/* func_ov106_0229d8e0 @ 0x0229d8e0, 0x68 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b57c(void *p);
extern int func_0208e4bc(void *p);
extern int func_ov002_0220b5ec(void *p, int a);
extern int func_ov002_0220b59c(void *p, int a);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov106_0229cc50(void *p);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov002_022080a0(void *p, int a);

void func_ov106_0229d8e0(char *self)
{
    if (func_ov002_0220b57c(self + 0x2b3c) != 0) {
        if (func_0208e4bc(self + 0x22a0) != 0) {
            int a = func_ov002_0220b5ec(self + 0x2b3c, 1);
            int b = func_ov002_0220b59c(self + 0x2b3c, 1);
            func_ov002_0220a0b4(self + 0x22a0, a, b);
        }
    } else {
        func_ov106_0229cc50(self);
        func_ov002_02208090(self, 9);
        func_ov002_022080a0(self, 1);
    }
}
