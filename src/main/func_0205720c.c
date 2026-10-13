/* func_0205720c @ 0x0205720c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020579b8(int, int);
extern int func_0205712c(int, int, int);

int func_0205720c(int a, int b, int c)
{
    if (c != 0) {
        return func_0205712c(a, b, func_020579b8(b, c));
    } else {
        return 1;
    }
}
