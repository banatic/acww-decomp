/* func_0205d690 @ 0x0205d690, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d51c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020051b0(void *);

void *func_0205d690(void *p)
{
    func_0205d51c((void *) ((char *) p + 0x3c));
    __cxa_vec_cleanup((void *) ((void *) ((char *) p + 0x28)), 0xa, 2, (void (*)(void *)) func_020051b0);
    return p;
}
