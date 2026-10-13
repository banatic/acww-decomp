/* func_ov003_0222d6a8 @ 0x0222d6a8, 0x52 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(unsigned char *p);

int func_ov003_0222d6a8(void)
{
    unsigned char buf[4];
    unsigned char v;

    func_0209def4(buf);
    v = buf[1];
    if (v >= 4 && v <= 7) {
        return 1;
    }
    if (v >= 8 && v <= 0xf) {
        return 2;
    }
    if (v == 0x10) {
        return 3;
    }
    if (v == 0x11 || v == 0x12) {
        return 4;
    }
    if (v >= 0x13 && v <= 0x16) {
        return 5;
    }
    return 0;
}
