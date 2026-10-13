/* func_0204fb08 @ 0x0204fb08, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204fb08(unsigned int r0)
{
    int r1 = 0;
    if ((r0 >= 4 && r0 < 9) || (r0 >= 16 && r0 < 21)) {
        r1 = 0;
    } else if (r0 >= 9 && r0 < 16) {
        r1 = 1;
    } else if ((r0 >= 21 && r0 <= 24) || (r0 < 4)) {
        r1 = 2;
    }
    return r1;
}
