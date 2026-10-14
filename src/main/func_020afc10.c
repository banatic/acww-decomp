/* func_020afc10 @ 0x020afc10, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020051b0(void);
extern void __cxa_vec_cleanup(void *, int, int, int (*)(void));

void *func_020afc10(void *arg)
{
    __cxa_vec_cleanup((char *) arg + 4, 0x25, 2, func_020051b0);
    return arg;
}
