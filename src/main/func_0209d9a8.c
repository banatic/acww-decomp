/* func_0209d9a8 @ 0x0209d9a8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *a, int b, int c, void (*d)(void));
extern void func_0209d934(void);

void *func_0209d9a8(void *arg)
{
    __cxa_vec_cleanup(arg, 0x33, 1, func_0209d934);
    return arg;
}
