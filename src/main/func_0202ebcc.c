/* func_0202ebcc @ 0x0202ebcc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
int func_0202ebcc(unsigned char *p)
{
    unsigned int ok;
    if (data_020e54a8 == 1) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0 || p[0x650] == 0) {
        return 1;
    }
    return 0;
}
