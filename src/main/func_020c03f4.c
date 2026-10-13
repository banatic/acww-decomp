/* func_020c03f4 @ 0x020c03f4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020c03f4(int a, int b)
{
    int result = 15;
    if (b != 0) {
        result = 0;
    } else if (a == 0) {
        result = 2;
    } else if (a == 1) {
        result = 4;
    } else if (a == 2) {
        result = 6;
    } else if (a == 3) {
        result = 8;
    }
    return result;
}
