/* func_0207ebb8 @ 0x0207ebb8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02099728(unsigned int);

int func_0207ebb8(unsigned int argument0)
{
    unsigned short *p = func_02099728((unsigned int) argument0);
    int flag = 1;
    int cond = 0;
    unsigned short v = *p;
    if (v >= 0x136b && v <= 0x1372) {
        cond = flag;
    }
    if (cond == 0) {
        if (v < 0x1373 || v > 0x1373) {
            flag = 0;
        }
    }
    return flag;
}
