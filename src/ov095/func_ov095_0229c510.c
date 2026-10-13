/* func_ov095_0229c510 @ 0x0229c510, 0x1c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov095_0229e874[];

unsigned short func_ov095_0229c510(int unused, int index)
{
    if (index >= 0x3b && index <= 0x6f) {
        return data_ov095_0229e874[index - 0x3b];
    }
    return 0;
}
