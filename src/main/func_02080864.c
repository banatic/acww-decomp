/* func_02080864 @ 0x02080864, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int, unsigned int);
extern int func_02003648(int);
extern int func_02082500(int);

int func_02080864(int param1, unsigned int param2)
{
    int ret = 0;
    if (param2 < 6u) {
        int tmp = func_02082500(func_02003648(func_0208150c(param1, param2)));
        if (tmp != 0) {
            ret = tmp + 26 + param2 * 2;
        }
    }
    return ret;
}
