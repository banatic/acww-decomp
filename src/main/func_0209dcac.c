/* func_0209dcac @ 0x0209dcac, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *);

int func_0209dcac(void)
{
    unsigned char buf[2];
    unsigned char b;
    int result;

    func_0209def4(buf);
    b = buf[1];
    if (b < 5) {
        result = 3;
    } else if (b < 12) {
        result = 0;
    } else if (b < 17) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}
