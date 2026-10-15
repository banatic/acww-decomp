/* func_020b0a88 @ 0x020b0a88, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020b0aa4(void *);

void *func_020b0a88(void *param0)
{
    __cxa_vec_cleanup((void *) (param0), 2, 16, (void (*)(void *)) func_020b0aa4);
    return param0;
}
