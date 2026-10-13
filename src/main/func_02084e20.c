/* func_02084e20 @ 0x02084e20, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02084e20(unsigned short *arr, unsigned int x, unsigned int y)
{
    if (x < 16 && y < 16) {
        if ((arr[y] >> x) & 1) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
