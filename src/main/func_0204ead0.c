/* func_0204ead0 @ 0x0204ead0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e6d8(void *);
extern int func_0204e6f8(void *);
extern void func_02037d0c(void *);
extern void func_02037d10(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_0204ead0(void *p)
{
    __cxa_vec_ctor((void *) ((char *) p + 0x24), 0x10, 0x200, (((void (*)(void *)) func_0204e6f8)),
                   (((void (*)(void *)) func_0204e6d8)));
    __cxa_vec_ctor((void *) ((char *) p + 0x2024), 0x10, 0x20, (void (*)(void *)) func_02037d10,
                   (void (*)(void *)) func_02037d0c);
    return p;
}
