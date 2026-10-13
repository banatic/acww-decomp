/* func_ov103_0229c2f4 @ 0x0229c2f4, 0x18 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

int func_ov103_0229c2f4(unsigned int *arr, unsigned int mask)
{
    if (arr[0x2b88 / 4] & mask) {
        return 1;
    }
    return 0;
}
