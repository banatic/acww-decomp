/* func_ov094_0229a2ec @ 0x0229a2ec, 0x3c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b9af4(void *);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*callback3)(void *), void (*callback4)(void *));
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov094_0229a2ec(void *base)
{
    char *p = (char *) base + 0x38;
    char *end = (char *) base + 0xe0;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);
    __cxa_vec_ctor(end, 2, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    return base;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
