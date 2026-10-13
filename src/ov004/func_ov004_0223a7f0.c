/* func_ov004_0223a7f0 @ 0x0223a7f0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223ac0c(void *p);

void func_ov004_0223a7f0(char *self)
{
    func_ov004_0223ac0c(self + 4 + (*(short *) (self + 0x0) & 1) * 168);
}
