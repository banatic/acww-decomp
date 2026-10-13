/* func_ov127_02299858 @ 0x02299858, 0x10 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

void func_ov127_02299858(void *base, unsigned short mask)
{
    *(unsigned short *) ((char *) base + 0x2830) &= ~mask;
}
