/* func_ov135_0229cc48 @ 0x0229cc48, 0x58 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov134_02299a90(char *p);
extern void func_ov134_02299a84(char *p);
extern int func_ov135_0229c7a8(char *p);
extern int func_ov135_0229c754(char *p);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov002_02208098(char *p, int n);

void func_ov135_0229cc48(char *self)
{
    int a;
    int b;
    if (data_021fbe40 & 1) {
        func_ov134_02299a90(self + 0x2c8);
        a = func_ov135_0229c7a8(self);
        b = func_ov135_0229c754(self);
        self = self + 0x98;
        func_ov002_0220a0b4(self, a, b);
    } else {
        func_ov134_02299a84(self + 0x2c8);
        func_ov002_02208098(self, 9);
    }
}
