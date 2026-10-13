/* func_ov004_0220d268 @ 0x0220d268, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b3740(char *self);
char *func_ov004_0220d268(char *self)
{
    func_020b3740(self);
    *(signed char *) (self + 0x14) = -1;
    *(int *) (self + 0x18) = 0;
    return self;
}
