/* func_ov004_0223c908 @ 0x0223c908, 0x4a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223cadc(void *, int);
extern void *func_ov004_0223ca6c(void *, int);
extern int func_ov004_0223cb18(void *);
extern int func_ov004_0223c8b4(void *, short);
extern int func_ov004_0220ebd4(void *, int);
int func_ov004_0223c908(void *self, int y)
{
    void *a = func_ov004_0223cadc(self, 0);
    void *b = func_ov004_0223ca6c(self, 0);
    if (a != 0 && b != 0) {
        return func_ov004_0220ebd4(b, func_ov004_0223c8b4(self, (short) (y + func_ov004_0223cb18(a))));
    }
    return 0;
}
