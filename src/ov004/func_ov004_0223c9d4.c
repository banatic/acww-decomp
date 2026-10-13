/* func_ov004_0223c9d4 @ 0x0223c9d4, 0x96 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223ca6c(void *self, int k);
extern void *func_ov004_0223cadc(void *self, int k);
extern int func_ov004_0220fde0(void *p);
extern int func_02053b2c(int x);
extern int func_ov004_0223cb20(void *p);
extern int func_ov004_0220fd98(void *p);

void func_ov004_0223c9d4(void *self)
{
    void *a, *b;
    int ok;

    a = func_ov004_0223ca6c(self, 1);
    b = func_ov004_0223cadc(self, 1);
    if (a != 0 && b != 0) {
        ok = 1;
        if (func_02053b2c(func_ov004_0220fde0(a)) != 0 && func_ov004_0223cb20(b) != 0) {
            ok = 0;
        }
        if (ok != 0 && func_ov004_0220fd98(a) != 0) {
            return;
        }
    }
    a = func_ov004_0223ca6c(self, 0);
    b = func_ov004_0223cadc(self, 0);
    if (a != 0 && b != 0) {
        ok = 1;
        if (func_02053b2c(func_ov004_0220fde0(a)) != 0 && func_ov004_0223cb20(b) != 0) {
            ok = 0;
        }
        if (ok != 0 && func_ov004_0220fd98(a) != 0) {
            return;
        }
    }
}
