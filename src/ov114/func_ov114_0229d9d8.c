/* func_ov114_0229d9d8 @ 0x0229d9d8, 0x40 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220a5e4(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*callback3)(void *));
extern void *func_ov114_0229d130(void *p);
extern void func_ov094_0229b0f8(void *p);
extern int **func_02070be8(void *element);

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov114_0229d9d8(void *arg)
{
    func_ov002_0220a5e4((char *) arg + 0x121c);
    __cxa_vec_cleanup((char *) arg + 0x106c, 4, 0x6c, DisposeElement_func_02070be8);
    func_ov114_0229d130((char *) arg + 0x808);
    func_ov094_0229b0f8(arg);
    return arg;
}

#undef DisposeElement_func_02070be8
