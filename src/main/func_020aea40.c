/* func_020aea40 @ 0x020aea40, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(int, int, int, void (*func)(void));
extern void func_020051b0(void);

int func_020aea40(int arg)
{
    __cxa_vec_cleanup(arg, 6, 2, func_020051b0);
    return arg;
}
