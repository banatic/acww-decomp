/* func_020342ac @ 0x020342ac, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020342ac(int *ptr, int value)
{
    if (value >= 0 && value < 8) {
        *ptr = value;
        return 1;
    }
    return 0;
}
