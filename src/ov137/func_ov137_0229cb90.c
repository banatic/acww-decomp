/* func_ov137_0229cb90 @ 0x0229cb90, 0x58 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov134_02299a90(void *);
extern int func_ov137_0229c794(void *);
extern int func_ov137_0229c750(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov134_02299a84(void *);
extern void func_ov002_02208098(void *, int);

void func_ov137_0229cb90(char *self)
{
    if ((data_021fbe40 & 1) != 0) {
        int a;
        int b;
        func_ov134_02299a90(self + 0x2c4);
        a = func_ov137_0229c794(self);
        b = func_ov137_0229c750(self);
        self += 0x94;
        func_ov002_0220a0b4(self, a, b);
    } else {
        func_ov134_02299a84(self + 0x2c4);
        func_ov002_02208098(self, 7);
    }
}
