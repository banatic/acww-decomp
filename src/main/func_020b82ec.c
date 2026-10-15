/* func_020b82ec @ 0x020b82ec, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b8020(void *);
extern void *func_020b8038(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_020b82ec(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 10, 0x44, (((void (*)(void *)) func_020b8038)), (((void (*)(void *)) func_020b8020)));
    return arg;
}
