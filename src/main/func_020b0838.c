/* func_020b0838 @ 0x020b0838, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0a80();
extern void func_020b0a84();
extern void __cxa_vec_ctor(void *a, int b, int c, void (*d)(), void (*e)());

void *func_020b0838(void *arg)
{
    __cxa_vec_ctor(arg, 3, 6, func_020b0a84, func_020b0a80);
    return arg;
}
