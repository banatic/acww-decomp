/* func_020131c0 @ 0x020131c0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020131c0(int a, int b)
{
    if (b != 0) {
        b = b << 2;
        if ((b & 0xf) == 0) {
            b = (b >> 4) & 0xf;
        }
        return b;
    }
    return 0;
}
