/* func_0205d19c @ 0x0205d19c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern void func_02055ce8(void *);

char *func_0205d19c(char *arg0)
{
    __cxa_vec_cleanup((void *) (arg0 + 0x10), 4, 0x14, (void (*)(void *)) func_02055ce8);
    return arg0;
}
