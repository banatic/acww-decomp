/* func_0209b218 @ 0x0209b218, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_0209b218(int unused, int param)
{
    unsigned char count = 0;
    int i = 0;
    do {
        if ((param >> i) & 1) {
            count++;
        }
        i++;
    } while (i < 5);
    return count;
}
