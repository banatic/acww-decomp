/* func_02083a04 @ 0x02083a04, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *obj, int size);
extern void func_02083a50(void);
extern void func_02083a68(void);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*f1)(void), void (*f2)(void));
extern char data_020e1aac;

void *func_02083a04(void *self)
{
    func_02083ca8(self, 8);
    ((void **) self)[0] = &data_020e1aac;
    __cxa_vec_ctor((char *) self + 8, 8, 8, &func_02083a68, &func_02083a50);
    return self;
}
