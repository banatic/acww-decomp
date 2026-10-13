/* func_ov004_0223abf0 @ 0x0223abf0, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223ac0c(char *self);
int func_ov004_0223abf0(char *self)
{
    if (func_ov004_0223ac0c(self) == 0xff) {
        return *(short *) (self + 0xa4);
    }
    return -1;
}
