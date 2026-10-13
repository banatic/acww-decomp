/* func_ov109_0229c28c @ 0x0229c28c, 0x10 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

void func_ov109_0229c28c(unsigned int *base, unsigned int mask)
{
    base = (unsigned int *) ((char *) base + 0x29b4);
    *base &= ~mask;
}
