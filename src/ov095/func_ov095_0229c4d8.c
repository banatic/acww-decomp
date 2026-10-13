/* func_ov095_0229c4d8 @ 0x0229c4d8, 0x1c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern short data_ov095_0229e774[];

int func_ov095_0229c4d8(int unused, int index)
{
    if (index >= 0x70 && index <= 0x91) {
        return data_ov095_0229e774[index - 0x70];
    } else {
        return 0;
    }
}
