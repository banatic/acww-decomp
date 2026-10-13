/* func_ov004_022384c0 @ 0x022384c0, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_022384c0(char *self)
{
    int v = 5 * (*(int *) (self + 0x200) * *(int *) (self + 0x158));
    int lim = *(int *) (self + 0x208);
    if (v >= lim) {
        v = lim;
        *(char *) (self + 0x20e) = 2;
        *(int *) (self + 0x158) = 0;
    }
    *(int *) (self + 0x110) = v;
}
