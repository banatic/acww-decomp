/* func_02032f78 @ 0x02032f78, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __arm __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern void *func_020330e8(void *);

void *func_02032f78(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 4), 0x10, 0x24, (((void (*)(void *)) func_020330e8)));
    return arg;
}
