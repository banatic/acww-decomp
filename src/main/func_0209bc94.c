/* func_0209bc94 @ 0x0209bc94, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209bc94(unsigned int r0)
{
    int r1 = 4;
    if (r0 < 10) {
        r1 = 0;
    } else if (r0 < 20) {
        r1 = 1;
    } else if (r0 < 21) {
        r1 = 2;
    } else if (r0 < 22) {
        r1 = 3;
    }
    return r1;
}
