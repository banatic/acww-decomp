/* func_ov004_0222c774 @ 0x0222c774, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f030(char *self);
extern void func_0203efb0(char *self, int a);
extern void func_ov004_0222c314(char *p);
int func_ov004_0222c774(char *self)
{
    int r;
    if (func_0203f030(self) == 0) {
        r = 0;
    } else {
        func_0203efb0(self, 0);
        func_ov004_0222c314(self + 0x250);
        r = 1;
    }
    return r;
}
