/* func_ov004_0222c6e0 @ 0x0222c6e0, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203efdc(char *self);
extern void func_ov004_0222c2f0(char *p);
int func_ov004_0222c6e0(char *self)
{
    int r;
    if (func_0203efdc(self) == 0) {
        r = 0;
    } else {
        func_ov004_0222c2f0(self + 0x250);
        r = 1;
    }
    return r;
}
