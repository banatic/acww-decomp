/* func_02099808 @ 0x02099808, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02099808(unsigned char *base, int val)
{
    unsigned char *p = base + 0x243c;
    *p = (*p & ~0xf0) | ((val & 0xf) << 4);
}
