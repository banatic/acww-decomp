/* func_ov143_0229a374 @ 0x0229a374, 0x6c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(void *ptr);
extern int func_0208e4bc(void *ptr);
extern int func_ov002_0220a6e0(void *ptr);
extern int func_ov002_0220a768(void *ptr, int);
extern int func_ov002_0220a72c(void *ptr, int);
extern void func_ov002_0220a0b4(void *ptr, int, int);
extern void func_ov143_0229a014(void *ptr);
extern unsigned char *func_ov002_022080a0(void *ptr, unsigned char value);

void func_ov143_0229a374(char *self)
{
    if (func_ov002_0220a700(self + 0x110)) {
        int a, b, c;
        if (func_0208e4bc(self + 0xac) == 0) {
            return;
        }
        a = func_ov002_0220a6e0(self + 0x110);
        b = func_ov002_0220a768(self + 0x110, -1);
        c = func_ov002_0220a72c(self + 0x110, -1);
        func_ov002_0220a0b4(self + 0xac, a + (b - 6), a + c);
    } else {
        func_ov143_0229a014(self);
        func_ov002_022080a0(self, 1);
    }
}
