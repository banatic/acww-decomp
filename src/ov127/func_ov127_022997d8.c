/* func_ov127_022997d8 @ 0x022997d8, 0x2c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov127_0229a5d8[];

int func_ov127_022997d8(unsigned int idx)
{
    unsigned short val = data_ov127_0229a5d8[idx];
    if (((val & 0xF000) >> 12) == 2) {
        return val & 0xFFF;
    } else {
        return -1;
    }
}
