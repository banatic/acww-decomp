/* func_02072a48 @ 0x02072a48, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02072a48(unsigned int r0, unsigned int r1);

unsigned int func_02072a48(unsigned int r0, unsigned int r1)
{
    r1 &= 7;
    r1 *= 0x234;
    return r0 + r1;
}
