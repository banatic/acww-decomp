/* func_ov070_022796c0 @ 0x022796c0, 0x2c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_020051b0(void *element);
extern char data_ov070_02279dbc[];

#define DisposeElement_func_020051b0 ((void (*)(void *)) func_020051b0)

void *func_ov070_022796c0(void *self)
{
    *(void **) self = &data_ov070_02279dbc;
    __cxa_vec_cleanup((char *) self + 0xc4, 3, 2, DisposeElement_func_020051b0);
    func_0202eb20(self);
    return self;
}

#undef DisposeElement_func_020051b0
