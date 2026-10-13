/* func_0207eb7c @ 0x0207eb7c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02099728(void);

int func_0207eb7c(void)
{
    unsigned short *p = func_02099728();
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x1374 && v <= 0x1374) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1375 || v > 0x1375) {
            flag = 0;
        }
    }
    return flag;
}
