/* func_02097ff0 @ 0x02097ff0, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02097ff0(int a, int b)
{
    if (b >= 0 && b < 10) {
        return a + (b << 8);
    }
    return 0;
}
