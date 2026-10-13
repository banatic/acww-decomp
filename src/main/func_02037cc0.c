/* func_02037cc0 @ 0x02037cc0, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02037cc0(int unused, unsigned short *ptr, int index)
{
    int result = 0;
    if (index >= 0 && index < 16) {
        unsigned short val = *ptr;
        result = 1;
        val &= ~(1 << index);
        *ptr = val;
    }
    return result;
}
