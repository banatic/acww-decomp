/* func_ov004_0220e050 @ 0x0220e050, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220e448(char *self);
int func_ov004_0220e050(char *self)
{
    if (func_ov004_0220e448(self)) {
        return *(int *) (self + 0xc);
    }
    return 0;
}
