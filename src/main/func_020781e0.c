/* func_020781e0 @ 0x020781e0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020782d0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_020781e0(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 0xf, 0xc4, (void (*)(void *)) func_020782d0);
    return arg;
}
