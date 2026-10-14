/* func_0205e65c @ 0x0205e65c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02055ce8(void);

void *func_0205e65c(void *p)
{
    __cxa_vec_cleanup((void *) ((char *) p + 0x10), 8, 0x14, func_02055ce8);
    return p;
}
