/* func_02082bc0 @ 0x02082bc0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02082bec(void *);
extern void func_02082bfc(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_02082bc0(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 0x40), 4, 8, (void (*)(void *)) func_02082bec);
    __cxa_vec_cleanup((void *) (arg), 8, 8, (void (*)(void *)) func_02082bfc);
    return arg;
}
