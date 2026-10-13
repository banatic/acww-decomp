/* func_0205738c @ 0x0205738c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a40(int a, int b);
extern int func_02057238(int a, int b, int c);

int func_0205738c(int a, int b, int c)
{
    if (c != 0) {
        return func_02057238(a, b, func_02057a40(b, c));
    } else {
        return 1;
    }
}
