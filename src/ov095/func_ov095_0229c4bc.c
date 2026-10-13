/* func_ov095_0229c4bc @ 0x0229c4bc, 0x1c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern short data_ov095_0229e7b8[];

int func_ov095_0229c4bc(int r0, int r1)
{
    if (r1 >= 0xc9 && r1 <= 0xf6) {
        return data_ov095_0229e7b8[r1 - 0xc9];
    }
    return 0;
}
