/* __sinit_020c5e30 @ 0x020c5e30, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: compiler-generated static initialiser; the pointer copies and the identity inline reproduce the constructor-call order that the C++ global objects of this unit would give */

extern void func_02138d6c(void *a, int b, int c, void (*d)(void), void (*e)(void));
extern void __register_global_object(void *a, void *b, void *node);
extern void func_02082c00(void);
extern void func_02082bfc(void);
extern void func_02082bf0(void);
extern void func_02082bec(void);
extern void func_02082bc0(void);
extern char data_021d1d4c;
extern char data_021d1d8c;
extern char data_021d1d40;
inline void *inline_fn()
{
    return (void *) (&data_021d1d4c);
}

void __sinit_020c5e30(void)
{
    char *ptr;
    void **ptr2;
    void *ptr3;
    ptr = &data_021d1d40;
    ptr3 = (void *) (&data_021d1d4c);
    func_02138d6c(ptr3, 8, 8, func_02082c00, func_02082bfc);
    ptr3 = &data_021d1d8c;
    ptr2 = &ptr3;
    func_02138d6c((void *) (*ptr2), 4, 8, func_02082bf0, func_02082bec);
    __register_global_object(inline_fn(), (void *) func_02082bc0, (void *) ptr);
}
