/* func_0201a824 @ 0x0201a824, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a824(int r0, int r1);

int func_0201a824(int r0, int r1)
{
    if (r0 < 0) {
        r0 = -r0;
    }
    if (r0 < r1) {
        return 1;
    }
    return 0;
}
