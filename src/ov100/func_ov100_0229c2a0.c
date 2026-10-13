/* func_ov100_0229c2a0 @ 0x0229c2a0, 0x10 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

void func_ov100_0229c2a0(unsigned char *ptr, unsigned int mask)
{
    *(unsigned int *) (ptr + 0x28c0) &= ~mask;
}
