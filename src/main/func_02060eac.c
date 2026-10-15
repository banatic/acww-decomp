/* func_02060eac @ 0x02060eac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060ee0(int, int);
extern int *func_0206122c(int, int);
extern int func_02060da8(int, int);

int *func_02060eac(int arg0, int arg1, int arg2)
{
    int *p = 0;
    int ret = func_02060ee0(arg0, arg1);
    if (ret) {
        p = func_0206122c(ret, arg2);
        if (p) {
            *p = func_02060da8(arg0, arg1);
        }
    }
    return p;
}
