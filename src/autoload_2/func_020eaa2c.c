/* func_020eaa2c @ 0x020eaa2c, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

int func_020eaa2c(int *a, int *b)
{
    if (a[0] != b[0] || a[1] != b[1] || a[2] != b[2]) {
        return 1;
    }
    return 0;
}
