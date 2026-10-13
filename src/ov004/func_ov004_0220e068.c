/* func_ov004_0220e068 @ 0x0220e068, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220e448(char *self);
int func_ov004_0220e068(char *self)
{
    if (func_ov004_0220e448(self)) {
        return *(int *) (self + 8);
    }
    return 0;
}
