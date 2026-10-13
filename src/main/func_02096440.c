/* func_02096440 @ 0x02096440, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02096440(unsigned char *src, unsigned char *low, unsigned char *high)
{
    *low = *src & 0xF;
    *high = (*src >> 4) & 0x7;
}
