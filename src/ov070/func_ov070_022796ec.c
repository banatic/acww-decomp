/* func_ov070_022796ec @ 0x022796ec, 0x38 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *obj);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*callback3)(void *), void (*callback4)(void *));
extern char data_ov070_02279dbc;
extern void func_02034ce0(void *element);
extern void func_020051b0(void *element);

#define DisposeElement_func_02034ce0 ((void (*)(void *)) func_02034ce0)

#define DisposeElement_func_020051b0 ((void (*)(void *)) func_020051b0)

void *func_ov070_022796ec(void *obj)
{
    func_0202eb70(obj);
    *(void **) obj = (void *) &data_ov070_02279dbc;
    __cxa_vec_ctor((char *) obj + 0xC4, 3, 2, DisposeElement_func_02034ce0, DisposeElement_func_020051b0);
    return obj;
}

#undef DisposeElement_func_02034ce0
#undef DisposeElement_func_020051b0
