/* func_02031e28 @ 0x02031e28, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
