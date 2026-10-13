/* func_02097cd4 @ 0x02097cd4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02097cd4(unsigned char *data, int index)
{
    int mask;
    mask = 1 << (index & 7);
    return (mask & *(data + (index >> 3) + 4)) != 0;
}
