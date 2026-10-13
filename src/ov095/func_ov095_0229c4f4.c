/* func_ov095_0229c4f4 @ 0x0229c4f4, 0x1c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern short data_ov095_0229e8e0[];
int func_ov095_0229c4f4(int param0, int index)
{
    if (index >= 59 && index <= 111) {
        return data_ov095_0229e8e0[index - 59];
    }
    return 0;
}
