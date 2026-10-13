/* func_02037ce0 @ 0x02037ce0, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02037ce0(int unused, unsigned short *ptr, int index)
{
    int ret = 0;
    if (index >= 0 && index < 16) {
        *ptr |= (1 << index);
        ret = 1;
    }
    return ret;
}
