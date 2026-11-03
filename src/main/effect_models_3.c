/* effect_models_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020911dc @ 0x020911dc, 0x30 bytes, Thumb
 * func_020911b0 @ 0x020911b0, 0x2c bytes, Thumb
 */

extern void *func_02055210(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020565b0(void *);
extern void func_020565c8(void *);
extern void *func_020902ac(void *);

void *func_020911dc(void *ptr)
{
    func_02055210((char *) ptr + 0x24);
    __cxa_vec_ctor((void *) ((char *) ptr + 0xe8), 3, 0x20, (void (*)(void *)) func_020565c8,
                   (((void (*)(void *)) func_020565b0)));
    return ptr;
}

void *func_020911b0(void *arg)
{
    __cxa_vec_ctor((void *) ((char *) arg + 4), 4, 0x148, (((void (*)(void *)) func_020911dc)),
                   (((void (*)(void *)) func_020902ac)));
    return arg;
}
