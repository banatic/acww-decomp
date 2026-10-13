/* func_ov095_0229cf64 @ 0x0229cf64, 0x12 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229cf64(int *a, int b);

int func_ov095_0229cf64(int *a, int b)
{
    int result;
    int mask;

    mask = 1 << b;
    result = (a[8] & mask) != 0;
    return result;
}
