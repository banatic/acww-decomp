/* func_02097eb0 @ 0x02097eb0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02097eb0(unsigned char *base, int index)
{
    int bit = index & 7;
    int mask = 1 << bit;
    int result = 1;
    if ((*(base + (index >> 3) + 0x100) & mask) == 0) {
        result = 0;
    }
    return result;
}
