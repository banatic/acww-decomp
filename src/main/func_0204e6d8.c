/* func_0204e6d8 @ 0x0204e6d8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *p, int s, int n, void (*cb)(void));
extern void func_020051b0(void);

void *func_0204e6d8(void *p)
{
    __cxa_vec_cleanup(p, 0x100, 2, func_020051b0);
    return p;
}
