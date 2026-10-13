/* func_02080b64 @ 0x02080b64, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_02003704(int);
extern int func_02003648(int);
extern int func_02082500(int);

int func_02080b64(int arg)
{
    int val;
    int ret = 0;

    if (func_02003704(func_0208150c(arg))) {
        val = func_02082500(func_02003648(func_0208150c(arg)));
        if (val) {
            ret = val + 0x28;
        }
    }

    return ret;
}
