/* func_02051c90 @ 0x02051c90, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02051c90(unsigned short *arr, int count, int arg2, int start)
{
    int i = start;
    do {
        if (arr[i] == 0) {
            return i;
        }
        i++;
    } while (i < count);
    return i;
}
