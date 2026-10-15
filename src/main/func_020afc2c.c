/* func_020afc2c @ 0x020afc2c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void func_020afbcc(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_020afc2c(void *p)
{
    __cxa_vec_ctor((void *) ((char *) p + 4), 0x25, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_020afbcc(p);
    return p;
}
