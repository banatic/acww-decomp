/* func_02053340 @ 0x02053340, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02053340(unsigned short *arr, int bit, int index)
{
    int idx = index & 0xF;
    int val = arr[idx];
    int shift = bit & 0xF;
    if ((val >> shift) & 1) {
        return 1;
    } else {
        return 0;
    }
}
