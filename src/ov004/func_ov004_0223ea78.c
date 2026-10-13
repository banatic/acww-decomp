/* func_ov004_0223ea78 @ 0x0223ea78, 0x52 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *);
int func_ov004_0223ea78(void)
{
    unsigned char d[4];
    unsigned char m;
    func_0209def4(d);
    m = d[1];
    if (m >= 4 && m <= 7) {
        return 2;
    }
    if (m >= 8 && m <= 0xf) {
        return 4;
    }
    if (m == 0x10) {
        return 8;
    }
    if ((unsigned char) (m + 0xef) <= 1) {
        return 0x10;
    }
    if (m >= 0x13 && m <= 0x16) {
        return 0x20;
    }
    return 1;
}
