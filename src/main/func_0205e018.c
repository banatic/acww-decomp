/* func_0205e018 @ 0x0205e018, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *a, int b, int c, void *d);

extern void func_02055ce8(void);

void *func_0205e018(void *arg)
{
    __cxa_vec_cleanup((char *) arg + 16, 4, 20, (void *) func_02055ce8);
    return arg;
}
