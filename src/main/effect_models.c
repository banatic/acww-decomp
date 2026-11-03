/* effect_models: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020902ac @ 0x020902ac, 0x24 bytes, Thumb
 * func_0209028c @ 0x0209028c, 0x20 bytes, Thumb
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_020551e0(void *);
extern void *func_020565b0(void *);

void *func_020902ac(void *self)
{
    __cxa_vec_cleanup((void *) ((void *) ((char *) self + 0xe8)), 3, 0x20, (((void (*)(void *)) func_020565b0)));
    func_020551e0((void *) ((char *) self + 0x24));
    return self;
}

void *func_0209028c(void *arg0)
{
    __cxa_vec_cleanup((void *) ((char *) arg0 + 4), 4, 0x148, (((void (*)(void *)) func_020902ac)));
    return arg0;
}
