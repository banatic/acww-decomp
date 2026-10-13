/* func_ov004_022112c4 @ 0x022112c4, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov004_0220d2b8(void *p);
int func_ov004_022112c4(unsigned char *self)
{
    unsigned short v;
    int a, b;
    v = *(unsigned short *) (self + 0xc);
    a = (v == 0x3b) ? 1 : 0;
    if (a != 0 || (b = ((v == 0x3c) ? 1 : 0)) != 0) {
        if (func_ov004_0220d2b8(self + 0x740) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
