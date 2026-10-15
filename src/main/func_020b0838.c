/* func_020b0838 @ 0x020b0838, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0a80(void *);
extern void func_020b0a84(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_020b0838(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 6, (void (*)(void *)) func_020b0a84, (void (*)(void *)) func_020b0a80);
    return arg;
}
