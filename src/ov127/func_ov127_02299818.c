/* func_ov127_02299818 @ 0x02299818, 0x2c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov127_0229a5d8[];

int func_ov127_02299818(unsigned int index)
{
    unsigned short value = data_ov127_0229a5d8[index];
    if (((value & 0xf000) >> 12) == 1) {
        return value & 0x0fff;
    }
    return -1;
}
