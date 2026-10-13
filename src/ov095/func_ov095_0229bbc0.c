/* func_ov095_0229bbc0 @ 0x0229bbc0, 0x40 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

int func_ov095_0229bbc0(int unused, unsigned short *arr, int a, int b, int n)
{
    int i, j, lo, hi;
    if (a > b) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }
    for (i = 0; i + hi < n; i++) {
        arr[i + lo] = arr[i + hi];
    }
    hi -= lo;
    for (j = 1; j <= hi; j++) {
        arr[n - j] = 0;
    }
    return lo;
}
