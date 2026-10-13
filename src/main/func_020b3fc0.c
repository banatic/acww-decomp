/* func_020b3fc0 @ 0x020b3fc0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b3fc0(int param)
{
    int count = 0;
    unsigned int i;
    for (i = count; i < 4; i++) {
        if ((param >> i) & 1) {
            count++;
        }
    }
    return count;
}
