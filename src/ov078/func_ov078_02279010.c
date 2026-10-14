/* func_ov078_02279010 @ 0x02279010, 0x38 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *self);
extern void func_02034ce0(void);
extern void func_020051b0(void);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*f1)(void), void (*f2)(void));
extern char data_ov078_02279a9c;

void *func_ov078_02279010(void *self)
{
    func_0202eb70(self);
    *(void **) self = &data_ov078_02279a9c;
    __cxa_vec_ctor((char *) self + 0xb8, 2, 2, func_02034ce0, func_020051b0);
    return self;
}
