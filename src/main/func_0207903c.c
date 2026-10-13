/* func_0207903c @ 0x0207903c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207905c(int, int);
extern int func_0208259c(int, int);

int func_0207903c(int a, int b)
{
    int result;
    result = func_0207905c(a, b);
    if (result == 0) {
        return func_0208259c(a, b);
    }
    return result;
}
