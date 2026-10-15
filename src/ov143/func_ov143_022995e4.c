/* func_ov143_022995e4 @ 0x022995e4, 0x4c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *p, int a, int b, void (*callback3)(void *));
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern int **func_02070be8(void *element);
extern int data_ov143_0229b1c0;

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov143_022995e4(void *this)
{
    *(unsigned int *) this = (unsigned int) &data_ov143_0229b1c0;
    __cxa_vec_cleanup((char *) this + 0x2dc, 0x10, 0x6c, DisposeElement_func_02070be8);
    func_ov002_0220afdc((char *) this + 0x110);
    func_ov002_02209cb4((char *) this + 0xac);
    func_ov002_0220826c(this);
    func_ov002_02207f6c(this);
    return this;
}

#undef DisposeElement_func_02070be8
