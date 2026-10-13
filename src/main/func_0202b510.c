/* func_0202b510 @ 0x0202b510, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0202b510(int n)
{
    int result = ((n + 5) / 10) * 10;
    if (result < 10) {
        result = 10;
    }
    return result;
}
