/* func_02060984 @ 0x02060984, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021ed268[];

int func_02060984(unsigned int param)
{
    int value;
    if (param < 0x1323) {
        return param;
    }
    if (param > 0x1368) {
        return param;
    }
    if (param >= 0x1323 && param <= 0x1368) {
        value = (int) (param - 0x1323);
    } else {
        value = -1;
    }
    return func_020609bc((unsigned int) data_021ed268, value);
}
