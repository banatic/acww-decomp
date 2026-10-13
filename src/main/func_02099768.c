/* func_02099768 @ 0x02099768, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02099768(unsigned char *array, int val)
{
    unsigned char *p = array + 0x243d;
    *p = (*p & ~0xc0) | ((val & 3) << 6);
}
