/* func_02097f58 @ 0x02097f58, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

char *func_02097f58(char *base, int index)
{
    if (index >= 0 && index < 2) {
        return base + ((index * 25) << 8);
    }
    return 0;
}
