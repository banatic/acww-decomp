/* func_02060a70 @ 0x02060a70, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02060a70(unsigned char *arr, unsigned int idx)
{
    if (idx < 70) {
        if ((arr[idx >> 3] >> (idx & 7)) & 1) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}
