/* func_ov004_0223a7a8 @ 0x0223a7a8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223abe8(void *p);

void func_ov004_0223a7a8(char *self)
{
    func_ov004_0223abe8(self + 4 + (*(short *) (self + 0x0) & 1) * 168);
}
