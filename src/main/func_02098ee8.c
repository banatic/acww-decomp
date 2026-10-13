/* func_02098ee8 @ 0x02098ee8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02098ee8(unsigned int *base, unsigned int shift, unsigned int val)
{
    unsigned int bit = shift << 1;
    unsigned int mask = 3 << bit;
    unsigned int *addr = base + 0x29B;
    *addr &= ~mask;
    *addr |= (val << bit);
}
