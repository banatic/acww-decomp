/* func_020793c4 @ 0x020793c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
int func_020793c4(unsigned char *p)
{
    unsigned int ok;
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0) {
        unsigned char v = p[3];
        if (v >= 0xa) {
            return 2;
        }
        if (v >= 7) {
            return 1;
        }
    }
    return 0;
}
