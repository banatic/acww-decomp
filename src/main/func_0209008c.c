/* func_0209008c @ 0x0209008c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_020901a0(void *);

int func_0209008c(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 3, 0x950, (((void (*)(void *)) func_020901a0)));
    return arg;
}
