/* func_ov004_02229c14 @ 0x02229c14, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void func_ov004_0223cb10(void);
extern int func_ov004_0223c8a8(void);
extern int func_020b67d4(void);
extern void func_0200f328(void *self, int k);
extern int func_0200dc10(void *self);
extern int func_0200dc8c(void *self);
extern int func_02008258(void *self, int a);
extern void func_ov004_0222a23c(void *self, int a, int b, int c, int d);
extern void func_ov004_02229a44(void *self, int a, int b);
extern void func_ov004_0223c86c(void);

void func_ov004_02229c14(void *self)
{
    unsigned char fl;
    unsigned char *p;
    int r;

    if (func_02056f94((char *) self + 0x2d0) != 0) {
        if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
            fl = 0;
            func_ov004_0223cb10();
            if (func_ov004_0223c8a8() == 0) {
                fl = 1;
            }
            if (func_020b67d4() == 0 || *(int *) ((char *) self + 0x800) != 0) {
                fl = (unsigned char) (fl | 2);
            }
            if (fl != 0) {
                p = (unsigned char *) ((char *) self + 0x7d4);
                if (*p == 0) {
                    *p = 1;
                    if (fl == 1) {
                        func_0200f328(self, 0x6d);
                    }
                }
                r = func_0200dc10(self);
                if (func_0200dc8c(self) > 0 && r == 0) {
                    return;
                }
                *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
                func_ov004_0222a23c(self, 0, 1, 5, -1);
            } else {
                func_ov004_02229a44(self, 6, -1);
                func_ov004_0223cb10();
                func_ov004_0223c86c();
            }
        } else {
            *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
        }
    }
}
