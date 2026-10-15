/* func_02063ed4 @ 0x02063ed4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern void func_0206411c(void *);

void *func_02063ed4(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 9, 1, (void (*)(void *)) func_0206411c);
    return arg;
}
