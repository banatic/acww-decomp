/* func_ov004_0223a7d8 @ 0x0223a7d8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223abf0(void *p);

int func_ov004_0223a7d8(char *self)
{
    return func_ov004_0223abf0(self + 4 + (*(short *) (self + 0x0) & 1) * 168);
}
