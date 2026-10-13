/* func_020573f0 @ 0x020573f0, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205738c(int a, int b, int c, int d);
extern int func_0205720c(int a, int b, int d);

int func_020573f0(int a, int b, int c, int d)
{
    int ret = (func_0205738c(a, b, c, d) & 1) != 0;
    return (ret & func_0205720c(a, b, d)) != 0;
}
