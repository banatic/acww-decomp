/* func_ov052_02260420 @ 0x02260420, 0x3c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov052_02261128(void *);
extern void *func_0202ee5c(void *);
extern void func_020051b0(void *arg0);

extern unsigned char data_ov052_02261f40[];

#define DisposeElement_func_020051b0 ((void (*)(void *)) func_020051b0)

void *func_ov052_02260420(void *self)
{
    *(void **) self = (void *) data_ov052_02261f40;
    __cxa_vec_cleanup((char *) self + 0x720, 3, 2, DisposeElement_func_020051b0);
    func_ov052_02261128((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}

#undef DisposeElement_func_020051b0
