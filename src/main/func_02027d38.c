/* func_02027d38 @ 0x02027d38, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02027d38(unsigned short *param1, int param2);

unsigned short func_02027d38(unsigned short *param1, int param2)
{
    unsigned short result;
    unsigned short value;
    int flag;

    result = 0;
    flag = 0;
    value = *param1;
    if (value >= 0x11a8 && value <= 0x12a7) {
        flag = 1;
    }
    if (flag != 0 && param2 == 2) {
        result = 1;
    }
    return result;
}
