/* func_ov004_0222bc60 @ 0x0222bc60, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67ac(void);
extern int func_0200dc8c(void *self);
extern int func_0200dc2c(void *self);
extern int func_ov004_0223c510(void *p, short a);
extern int func_ov004_0223c4b8(void *p, short a);
extern int func_ov004_0222b6a8(void *self, int a, int b, int c);
extern int func_ov004_0222bbe4(void *self, int a, int b, int c);

void func_ov004_0222bc60(char *self)
{
    int k;
    int r;
    unsigned char *p;
    int t, n;

    if (func_020b67ac() != 0) {
        return;
    }
    if (func_0200dc8c(self) <= 0) {
        return;
    }
    k = func_0200dc2c(self);
    if (*(unsigned char *) (self + 0x8ea) == k + 1) {
        return;
    }
    *(unsigned char *) (self + 0x8ea) = k + 1;
    switch (k) {
        case 0:
            r = func_ov004_0223c510(self + 0x5c, *(short *) (self + 0x8e));
            break;
        case 1:
            r = func_ov004_0223c4b8(self + 0x5c, *(short *) (self + 0x8e));
            break;
    }
    if (r == 1) {
        func_ov004_0222b6a8(self, (k == 0) ? 1 : 0, 6, -1);
    } else if (r == 2) {
        func_ov004_0222bbe4(self, (k == 0) ? 1 : 0, 6, -1);
    }
}
