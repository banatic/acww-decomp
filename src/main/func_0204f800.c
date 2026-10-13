/* func_0204f800 @ 0x0204f800, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0204f800(int *out_x, int *out_y, int x, int y, int offset_x, int offset_y)
{
    *out_x = (x << 4) + offset_x;
    *out_y = (y << 4) + offset_y;
}
