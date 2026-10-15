/* func_0207eb40 @ 0x0207eb40, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02099728(unsigned int);

int func_0207eb40(unsigned int argument0)
{
    unsigned short *p = func_02099728((unsigned int) argument0);
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x1378 && v <= 0x1378) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1379 || v > 0x1379) {
            flag = 0;
        }
    }
    return flag;
}
