/* func_0207ca48 @ 0x0207ca48, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200363c(int);

void func_0207ca48(int a, int *arr, int bit)
{
    if (func_0200363c(bit)) {
        arr[bit >> 5] &= ~(1 << (bit & 31));
    }
}
