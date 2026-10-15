/* func_ov004_0222ba44 @ 0x0222ba44, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051e18(void);
extern int func_02008258(void *self, int a);
extern int func_ov004_0222bdf0(void *self, int a, int b, int c);
extern int func_ov004_0222b9d4(void *self, int a, int b, int arg, short v);

void func_ov004_0222ba44(char *self)
{
    unsigned char *q;

    switch (func_02051e18()) {
        case 0:
            return;
        case 1:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            break;
        case 2:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_ov004_0222bdf0(self, 0, 6, -1);
            return;
    }
    q = (unsigned char *) (self + 0x7d4);
    if (*(unsigned char *) (self + 0x200) != 0) {
        func_ov004_0222bdf0(self, 0, 6, -1);
    } else {
        func_ov004_0222b9d4(self, q[0xc], 0, 6, -1);
    }
}
