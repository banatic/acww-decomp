/* func_0204e6d8 @ 0x0204e6d8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020051b0(void *);

void *func_0204e6d8(void *p)
{
    __cxa_vec_cleanup((void *) (p), 0x100, 2, (void (*)(void *)) func_020051b0);
    return p;
}
