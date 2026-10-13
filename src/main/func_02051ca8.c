/* func_02051ca8 @ 0x02051ca8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02051ca8(unsigned short *arr, int n)
{
    int i;
    int result = 0;
    i = result;
    while (i < n) {
        if (arr[i] == 0) {
            return result;
        }
        if (arr[i] != 0x3000 && arr[i] != 0x20) {
            result = i + 1;
        }
        i++;
    }
    return result;
}
