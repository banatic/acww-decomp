/* func_02051ce0 @ 0x02051ce0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02051ce0(unsigned short *arr, int count, int offset)
{
    int i = 0;
    while (i < count) {
        unsigned short value = arr[i];
        if (value == 0) {
            return i;
        }
        if (value == 0xa) {
            return i + offset;
        }
        i++;
    }
    return i;
}
