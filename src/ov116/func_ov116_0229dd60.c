/* func_ov116_0229dd60 @ 0x0229dd60, 0x48 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov116_0229e8b8;
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov114_0229d9d8(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern int **func_02070be8(void *element);

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov116_0229dd60(void *p)
{
    *(void **) p = (void *) &data_ov116_0229e8b8;
    __cxa_vec_cleanup((char *) p + 0x13b8, 1, 0x6c, DisposeElement_func_02070be8);
    func_ov114_0229d9d8((char *) p + 0xf8);
    func_ov002_02209cb4((char *) p + 0x94);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return p;
}

#undef DisposeElement_func_02070be8
