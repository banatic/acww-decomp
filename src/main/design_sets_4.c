/* design_sets_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02072d14 @ 0x02072d14, 0x38 bytes, Thumb
 * func_02072ce8 @ 0x02072ce8, 0x2c bytes, Thumb
 */

extern void *func_02072da4(void *);
extern void *func_02072dbc(void *);
extern void func_02072ba0(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02072b9c(void *p);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

void *func_02072d14(void *ptr)
{
    __cxa_vec_ctor((void *) (ptr), 8, 0x234, (((void (*)(void *)) func_02072dbc)), (((void (*)(void *)) func_02072da4)));
    func_02072ba0((char *) ptr + 0x11a0);
    return ptr;
}

void *func_02072ce8(void *p)
{
    func_02072b9c((char *) p + 0x11a0);
    __cxa_vec_cleanup((void *) (p), 8, 0x234, (((void (*)(void *)) func_02072da4)));
    return p;
}
