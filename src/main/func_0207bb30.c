/* func_0207bb30 @ 0x0207bb30, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_0207cf14(int, int);
extern int func_0207cf74(int);
extern int func_0207bb84(int, int, int);

int func_0207bb30(int a, int b, int c)
{
    int x = func_0207cf14(a, func_0208150c(b));
    int y = func_0207cf14(a, func_0208150c(c));
    if (x != y) {
        if (func_0207cf74(x) != 0) {
            if (func_0207cf74(y) != 0) {
                return func_0207bb84(a, x, y);
            }
        }
    }
    return 4;
}
