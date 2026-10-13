/* func_02080500 @ 0x02080500, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080758(int param);
extern int func_02080568(int param);
extern int func_0208052c(int param);

int func_02080500(int param)
{
    int result;
    int temp;

    result = func_02080758(param);
    if (result == -1) {
        result = func_02080568(param);
    }
    if (result == -1) {
        result = func_0208052c(param);
    }
    return result;
}
