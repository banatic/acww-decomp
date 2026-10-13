/* func_ov004_022176c0 @ 0x022176c0, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220ce20(char *self);
int func_ov004_022176c0(char *self)
{
    int r;
    if (func_ov004_0220ce20(self) != 0 && *(int *) (self + 0x864) == 0) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
