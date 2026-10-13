/* func_020e8b4c @ 0x020e8b4c, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8b4c(int a, int b);

int func_020e8b4c(int a, int b)
{
    int diff = a - b;
    diff = (short) diff;
    if (diff < 0) {
        diff = -diff;
    }
    return diff;
}
