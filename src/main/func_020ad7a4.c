/* func_020ad7a4 @ 0x020ad7a4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(unsigned char *buf);

int func_020ad7a4(void)
{
    unsigned char buf[4];
    func_0209def4(buf);
    if (buf[1] >= 8 && buf[1] < 0x17) {
        return 1;
    } else {
        return 0;
    }
}
