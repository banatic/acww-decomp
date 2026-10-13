/* func_02064558 @ 0x02064558, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02064558(int r0)
{
    if (r0 <= -0x6000) {
        return 2;
    }
    if (r0 <= -0x2000) {
        return 3;
    }
    if (r0 <= 0x2000) {
        return 0;
    }
    if (r0 <= 0x6000) {
        return 1;
    }
    return 2;
}
