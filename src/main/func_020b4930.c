/* func_020b4930 @ 0x020b4930, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020b4930(signed char *arr, int end, int start, int offset)
{
    if (offset != 0) {
        int i = end - offset - 1;
        signed char *dest = arr + offset;
        while (i >= start) {
            dest[i] = arr[i];
            i--;
        }
    }
}
