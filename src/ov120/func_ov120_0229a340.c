/* func_ov120_0229a340 @ 0x0229a340, 0x6c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov120_0229c650;
extern void __cxa_vec_cleanup(void *ptr, int a, int b, void (*callback3)(void *));
extern void *func_ov002_02209cb4(void *ptr);
extern void *func_ov002_0220a5e4(void *ptr);
extern void *func_ov002_0220826c(void *ptr);
extern void func_ov120_0229a420(void *element);
extern int **func_02070be8(void *element);

#define DisposeElement_func_ov120_0229a420 ((void (*)(void *)) func_ov120_0229a420)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov120_0229a340(void *p)
{
    int count = 3;
    *(unsigned int *) p = (unsigned int) &data_ov120_0229c650;
    __cxa_vec_cleanup((char *) p + 0x2743, 14, 3, DisposeElement_func_ov120_0229a420);
    __cxa_vec_cleanup((char *) p + 0x273a, count, count, DisposeElement_func_ov120_0229a420);
    func_ov002_02209cb4((char *) p + 0x6bc);
    func_ov002_0220a5e4((char *) p + 0x674);
    __cxa_vec_cleanup((char *) p + 0xf8, 13, 108, DisposeElement_func_02070be8);
    func_ov002_0220826c(p);
    return p;
}

#undef DisposeElement_func_ov120_0229a420
#undef DisposeElement_func_02070be8
