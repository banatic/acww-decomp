/* func_020614e4 @ 0x020614e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020051b0(void *);

void *func_020614e4(void *arg1)
{
    __cxa_vec_cleanup((void *) (arg1), 0x100, 2, (void (*)(void *)) func_020051b0);
    return arg1;
}
