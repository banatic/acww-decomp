/* func_ov004_02225cac @ 0x02225cac, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(char *self);
extern void func_0201b38c(char *p, int a);
int func_ov004_02225cac(char *self)
{
    int r;
    if (func_0202edc8(self) == 0) {
        r = 0;
    } else {
        func_0201b38c(self + 0x2a0, 0xff);
        r = 1;
    }
    return r;
}
