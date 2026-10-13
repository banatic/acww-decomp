/* func_0207ebf8 @ 0x0207ebf8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02099728(void);

int func_0207ebf8(void)
{
    unsigned short *p = func_02099728();
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x1376 && v <= 0x1376) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1377 || v > 0x1377) {
            flag = 0;
        }
    }
    return flag;
}
