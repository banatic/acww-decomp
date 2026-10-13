/* func_ov004_0222a2e8 @ 0x0222a2e8, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern void func_ov004_0222a23c(void *self, int a, int b, int arg, short v);
extern int func_ov004_0223cb10(void);
extern void func_ov004_0223c9d4(int h);
extern int func_02008258(void *self, int a);
extern void func_0200d4e8(void *self, int a, int b, int c);

void func_ov004_0222a2e8(char *self)
{
    int *q;
    int *v;

    q = (int *) (self + 0x7d4);
    v = (int *) (self + 0x5c);
    if (func_02056f94(self + 0x2d0) != 0 && v[0] == q[0] && v[2] == q[1] &&
        *(short *) ((char *) q + 8) == *(short *) (self + 0x8e)) {
        func_ov004_0222a23c(self, 1, 0, 5, -1);
        return;
    }
    if (*(unsigned char *) (self + 0x141) != 0) {
        return;
    }
    if (*((unsigned char *) q + 0xa) == 0) {
        *((unsigned char *) q + 0xa) = 1;
        if (func_02056f94(self + 0x2d0) == 0) {
            func_ov004_0223c9d4(func_ov004_0223cb10());
        }
    } else {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        func_0200d4e8(self, 3, 1, -1);
    }
}
