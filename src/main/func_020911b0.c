/* func_020911b0 @ 0x020911b0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020902ac(void);
extern void func_020911dc(void);
extern void __cxa_vec_ctor(void *a, int b, int c, void (*d)(void), void (*e)(void));

void *func_020911b0(void *arg)
{
    __cxa_vec_ctor((char *) arg + 4, 4, 0x148, func_020911dc, func_020902ac);
    return arg;
}
