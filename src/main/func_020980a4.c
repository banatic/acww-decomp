/* func_020980a4 @ 0x020980a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_020980a4(void *p)
{
    __cxa_vec_cleanup((void *) (p), 10, 0x100, (void (*)(void *)) func_02066688);
    return p;
}
