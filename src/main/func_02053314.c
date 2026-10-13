/* func_02053314 @ 0x02053314, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02053314(unsigned short *arr, int bit, int idx, int flag)
{
    int b = bit & 0xF;
    int i = idx & 0xF;
    if (flag) {
        arr[i] |= (1 << b);
    } else {
        arr[i] &= ~(1 << b);
    }
}
