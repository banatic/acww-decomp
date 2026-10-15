/* func_ov133_0229bc64 @ 0x0229bc64, 0x70 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(char *p);
extern int func_0208e4bc(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int i);
extern int func_ov002_0220a72c(char *p, int i);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov133_0229ba10(char *self);
extern unsigned char *func_ov002_022080a0(char *self, unsigned char value);

void func_ov133_0229bc64(char *self)
{
    int a;
    int b;
    int c;

    if (func_ov002_0220a700(self + 0x180)) {
        if (func_0208e4bc(self + 0x11c) != 0) {
            a = func_ov002_0220a6e0(self + 0x180);
            b = func_ov002_0220a768(self + 0x180, -1);
            c = func_ov002_0220a72c(self + 0x180, -1);
            func_ov002_0220a0b4(self + 0x11c, a + (b - 6), a + c);
        }
    } else {
        func_ov133_0229ba10(self);
        func_ov002_022080a0(self, 1);
    }
}
