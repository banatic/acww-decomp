/* func_020b95b4 @ 0x020b95b4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b96f8(unsigned int *, unsigned int *, unsigned int);
extern void func_020b962c(unsigned int *, unsigned int);

unsigned int func_020b95b4(unsigned int a, unsigned int b)
{
    unsigned int x, y;

    if (b) {
        func_020b96f8(&x, &y, a);
    } else {
        func_020b962c(&x, a);
    }

    return (b << 31) | (((a >> 4) << 16) | ((x >> 3) & 0xffff));
}
