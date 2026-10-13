/* func_02064594 @ 0x02064594, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064594(int r0);

int func_02064594(int r0)
{
    if (r0 > 0 && r0 < 0x8000) {
        return 0;
    }
    if (r0 > -0x8000 && r0 < 0) {
        return 1;
    }
    return 2;
}
