/* func_ov094_0229b154 @ 0x0229b154, 0x1e bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

void func_ov094_0229b154(int *arr, int bit)
{
    arr[bit >> 5] |= 1 << (bit & 31);
}
