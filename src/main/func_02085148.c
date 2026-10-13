/* func_02085148 @ 0x02085148, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020852e4(unsigned short *param);
extern int func_020851e0(unsigned short *param);

int func_02085148(unsigned short *param)
{
    int nibble = (*param & 0xF000) >> 12;
    if (nibble == 0xE) {
        return func_020852e4(param);
    } else if (nibble == 0xD) {
        return func_020851e0(param);
    }
    return 0;
}
