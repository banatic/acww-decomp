/* func_0209028c @ 0x0209028c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020902ac(void);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));

void *func_0209028c(void *arg0)
{
    __cxa_vec_cleanup((char *) arg0 + 4, 4, 0x148, func_020902ac);
    return arg0;
}
