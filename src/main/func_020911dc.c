/* func_020911dc @ 0x020911dc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02055210(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020565b0(void *);
extern void func_020565c8(void *);

void *func_020911dc(void *ptr)
{
    func_02055210((char *) ptr + 0x24);
    __cxa_vec_ctor((void *) ((char *) ptr + 0xe8), 3, 0x20, (void (*)(void *)) func_020565c8,
                   (((void (*)(void *)) func_020565b0)));
    return ptr;
}
