/* func_ov136_0229cba0 @ 0x0229cba0, 0x58 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov134_02299a90(char *);
extern unsigned int func_ov136_0229c794(char *);
extern unsigned int func_ov136_0229c750(char *);
extern void func_ov002_0220a0b4(char *, unsigned int, unsigned int);
extern void func_ov134_02299a84(char *);
extern void func_ov002_02208098(char *, int);

void func_ov136_0229cba0(char *self)
{
    if (data_021fbe40 & 1) {
        unsigned int a;
        unsigned int b;
        func_ov134_02299a90(self + 0x2c4);
        a = func_ov136_0229c794(self);
        b = func_ov136_0229c750(self);
        func_ov002_0220a0b4(self + 0x94, a, b);
    } else {
        func_ov134_02299a84(self + 0x2c4);
        func_ov002_02208098(self, 9);
    }
}
