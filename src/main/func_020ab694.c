/* func_020ab694 @ 0x020ab694, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a82e4(void *);
extern void *func_020ab8c4(void *);
extern void *func_020ab7e8(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_020ab694(void *p)
{
    func_020a82e4((char *) p + 0x354);
    func_020ab8c4((char *) p + 0x2f8);
    __cxa_vec_cleanup((void *) (p), 5, 0x90, (((void (*)(void *)) func_020ab7e8)));
    return p;
}
