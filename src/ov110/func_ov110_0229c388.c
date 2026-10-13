/* func_ov110_0229c388 @ 0x0229c388, 0x30 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

int func_ov110_0229c388(int unused, unsigned short *arr)
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
