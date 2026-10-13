/* func_ov134_0229ae78 @ 0x0229ae78, 0x24 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

int func_ov134_0229ae78(int unused, int x, int y, int r)
{
    if ((x - 0x38) * (x - 0x38) + (y - 0x34) * (y - 0x34) >= r * r) {
        return 0;
    } else {
        return 1;
    }
}
