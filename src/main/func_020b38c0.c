/* func_020b38c0 @ 0x020b38c0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern long long _s32_div_f(int a, int b);

int func_020b38c0(const unsigned char *arr, int index)
{
    unsigned int val = arr[index & 3];
    if (val < 25) {
        return (int) val;
    }
    return (int) (_s32_div_f(val, 25) >> 32);
}
