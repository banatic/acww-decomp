/* func_ov106_0229eed0 @ 0x0229eed0, 0x58 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_020978bc(unsigned char *a, int b);
extern unsigned char *func_020984e8(unsigned char *a);
extern unsigned char *func_020989b4(unsigned char *a);
extern unsigned char *func_02098090(unsigned char *a, int b);
extern void func_0206fc4c(int a);
extern void func_02066830(unsigned char *a, unsigned char *b);
extern void func_020ee470(unsigned char *a);

int func_ov106_0229eed0(unsigned char *self)
{
    unsigned char *p;
    int i;

    func_0206fc4c(1);
    p = func_02098090(func_020989b4(func_020984e8(func_020978bc(self + 0x2bb4, 10))), 0);
    for (i = 0; i < 10; i++) {
        func_02066830(p, self + 0x2bb4 + i * 256);
        p += 0x100;
    }
    func_020ee470(self);
    return 1;
}
