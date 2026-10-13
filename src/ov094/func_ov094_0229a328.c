/* func_ov094_0229a328 @ 0x0229a328, 0x24 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

int func_ov094_0229a328(int *arr, int bit)
{
    return (arr[bit >> 5] & (1 << (bit & 31))) ? 1 : 0;
}
