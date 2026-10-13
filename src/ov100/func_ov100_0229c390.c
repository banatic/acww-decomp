/* func_ov100_0229c390 @ 0x0229c390, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

int func_ov100_0229c390(int unused, unsigned short *arr)
{
    int i = 0;
    int j = i;
    for (; i < 15; i++) {
        if (arr[i] != 0xFFF1) {
            if (i != j) {
                arr[j] = arr[i];
                arr[i] = 0xFFF1;
            }
            j++;
        }
    }
    return j;
}
