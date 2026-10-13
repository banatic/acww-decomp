/* func_0207ce70 @ 0x0207ce70, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207ce70(unsigned short *arr, int n)
{
    arr += n - 1;
    while (n > 0) {
        if (*arr != 0 && *arr != 0x3000) {
            return n;
        }
        n--;
        arr--;
    }
    return 0;
}
