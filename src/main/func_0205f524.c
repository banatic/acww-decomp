/* func_0205f524 @ 0x0205f524, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020051b0(void *);
extern void *func_02054e18(void *);
extern void func_02055ce8(void *);

void *func_0205f524(void *p)
{
    __cxa_vec_cleanup((void *) ((char *) p + 0xb44), 9, 2, (void (*)(void *)) func_020051b0);
    __cxa_vec_cleanup((void *) ((char *) p + 0x28c), 9, 0xf4, (((void (*)(void *)) func_02054e18)));
    __cxa_vec_cleanup((void *) ((char *) p + 0xdc), 9, 0x14, (void (*)(void *)) func_02055ce8);
    return p;
}
