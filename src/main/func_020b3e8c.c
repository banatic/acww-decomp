/* func_020b3e8c @ 0x020b3e8c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b3f44(unsigned int);
extern unsigned int func_020b3e58(unsigned int, unsigned int, unsigned int, unsigned int);

int func_020b3e8c(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    if (d < func_020b3f44(a)) {
        return func_020b3e58(a, b, c, d);
    } else {
        return 0;
    }
}
