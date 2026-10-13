/* func_02084e40 @ 0x02084e40, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02084e40(unsigned short *arr, unsigned int bit, unsigned int index)
{
    unsigned short val;
    if (bit < 16 && index < 16) {
        val = arr[index];
        val &= ~(1 << bit);
        arr[index] = val;
        return 1;
    }
    return 0;
}
