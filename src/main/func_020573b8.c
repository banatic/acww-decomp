/* func_020573b8 @ 0x020573b8, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057238(int a, int b, int c);
extern int func_0205712c(int a, int b, int d);

int func_020573b8(int a, int b, int c, int d)
{
    int ret = (func_02057238(a, b, c) & 1) != 0;
    return (ret & func_0205712c(a, b, d)) != 0;
}
