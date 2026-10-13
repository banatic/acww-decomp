/* func_ov101_0229c28c @ 0x0229c28c, 0xe bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

void func_ov101_0229c28c(unsigned int *p, unsigned int mask)
{
    unsigned int value;
    value = p[0x25];
    value &= ~mask;
    p[0x25] = value;
}
