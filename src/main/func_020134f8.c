/* func_020134f8 @ 0x020134f8, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020134f8(int unused, int mask)
{
    int i;

    if (mask != 0) {
        for (i = 0; i < 4; i++) {
            if (((mask >> i) & 1) != 0) {
                return i;
            }
        }
    }
    return 4;
}
