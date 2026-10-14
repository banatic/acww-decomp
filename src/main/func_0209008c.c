/* func_0209008c @ 0x0209008c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(int arg0, int arg1, int arg2, void (*callback)(void));
extern void func_020901a0(void);

int func_0209008c(int arg)
{
    __cxa_vec_cleanup(arg, 3, 0x950, func_020901a0);
    return arg;
}
