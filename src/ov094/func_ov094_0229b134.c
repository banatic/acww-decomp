/* func_ov094_0229b134 @ 0x0229b134, 0x1e bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b134(unsigned int *arr, int bit);

void func_ov094_0229b134(unsigned int *arr, int bit)
{
    int idx;
    unsigned int mask;
    unsigned int val;

    idx = bit >> 5;
    mask = 1 << (bit & 0x1f);
    val = arr[idx];
    val &= ~mask;
    arr[idx] = val;
}
