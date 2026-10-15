/* func_ov093_022997f8 @ 0x022997f8, 0x68 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov093_02298fd8(void *);
extern void *func_ov093_02298f64(void *);
extern void *func_020b9cfc(void *);
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov093_022997f8(void *self)
{
    func_ov093_02298fd8((char *) self + 0x18);
    func_ov093_02298fd8((char *) self + 0x820);
    func_ov093_02298f64((char *) self + 0x1828);
    __cxa_vec_ctor((char *) self + 0x19e0, 0x1a, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    {
        char *p = (char *) self + 0x24d8;
        char *end = (char *) self + 0x2520;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);
    }
    return self;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
