/* func_ov132_0229acc0 @ 0x0229acc0, 0x4c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov132_0229b990;
extern void *func_ov002_0220ba0c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern int **func_02070be8(void *element);

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov132_0229acc0(void *p)
{
    *(unsigned int *) p = (unsigned int) &data_ov132_0229b990;
    func_ov002_0220ba0c((void *) ((char *) p + 0x3e4));
    __cxa_vec_cleanup((void *) ((char *) p + 0x2c4), 2, 0x6c, DisposeElement_func_02070be8);
    func_ov002_0220afdc((void *) ((char *) p + 0xf8));
    func_ov002_02209cb4((void *) ((char *) p + 0x94));
    func_ov002_0220826c(p);
    return p;
}

#undef DisposeElement_func_02070be8
