/* func_020b19e4 @ 0x020b19e4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020b1a54(void *);
extern int func_020b1a64(void *);

int func_020b19e4(int arg)
{
    __cxa_vec_ctor((void *) (arg), 0x10, 0x4A, (((void (*)(void *)) func_020b1a64)), (((void (*)(void *)) func_020b1a54)));
    return arg;
}
