/* func_0207cee4 @ 0x0207cee4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);
extern int func_0208150c(int);
extern int func_02003704(int);

int func_0207cee4(int arg0, int arg1)
{
    int result;
    result = 0;
    if (func_0207cf74(arg1) != 0) {
        result = func_02003704(func_0208150c(arg0 + arg1 * 0x7ec));
    }
    return result;
}
