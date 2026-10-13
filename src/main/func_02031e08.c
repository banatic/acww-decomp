/* func_02031e08 @ 0x02031e08, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02031e08(int *a, int *b)
{
    if (*b < *a) {
        *a = *b;
    }
    if (b[1] < a[1]) {
        a[1] = b[1];
    }
    if (b[2] < a[2]) {
        a[2] = b[2];
    }
}
