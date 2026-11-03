/* collision_box: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031e28 @ 0x02031e28, 0x20 bytes, Thumb
 * func_02031e08 @ 0x02031e08, 0x20 bytes, Thumb
 */

void func_02031e28(int *dest, int *src)
{
    if (src[0] > dest[0]) {
        dest[0] = src[0];
    }
    if (src[1] > dest[1]) {
        dest[1] = src[1];
    }
    if (src[2] > dest[2]) {
        dest[2] = src[2];
    }
}

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
