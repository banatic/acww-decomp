/* func_0204cb2c @ 0x0204cb2c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984d4(int);
extern int func_0204cb48(int, int);
extern int func_0209df64(int);

int func_0204cb2c(int arg)
{
    int ret1 = func_020984d4(arg);
    int ret2 = func_0204cb48(arg, ret1);
    return func_0209df64(ret2);
}
