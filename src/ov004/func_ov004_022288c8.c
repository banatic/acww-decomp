/* func_ov004_022288c8 @ 0x022288c8, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051e9c(void);
extern int func_02008258(void *self, int a);
extern int func_ov004_02228dfc(void *self, int a, int b, int c);
extern int func_ov004_02228850(void *self, int a, int b);
extern int func_ov004_02228b14(void *self, int a, int b);
extern int func_ov004_02228be0(void *self, int a, int b);

void func_ov004_022288c8(char *self)
{
    unsigned char *q;

    switch (func_02051e9c()) {
        case 0:
            return;
        case 1:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            break;
        case 2:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_ov004_02228dfc(self, 3, 6, -1);
            return;
    }
    q = (unsigned char *) (self + 0x7d4);
    if (*(unsigned char *) (self + 0x200) != 0) {
        func_ov004_02228dfc(self, 3, 6, -1);
        return;
    }
    switch (q[0xc]) {
        case 0:
            func_ov004_02228850(self, 6, -1);
            break;
        case 1:
            func_ov004_02228b14(self, 6, -1);
            break;
        case 2:
            func_ov004_02228be0(self, 6, -1);
            break;
    }
}
