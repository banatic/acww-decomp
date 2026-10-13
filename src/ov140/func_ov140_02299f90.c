/* func_ov140_02299f90 @ 0x02299f90, 0x10 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

void func_ov140_02299f90(unsigned short *p, unsigned short mask)
{
    unsigned short v = p[0x456];
    v &= ~mask;
    p[0x456] = v;
}
