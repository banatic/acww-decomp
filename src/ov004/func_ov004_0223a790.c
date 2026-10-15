/* func_ov004_0223a790 @ 0x0223a790, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223abe0(void *p);

int func_ov004_0223a790(char *self)
{
    return func_ov004_0223abe0(self + 4 + (*(short *) (self + 0x0) & 1) * 168);
}
