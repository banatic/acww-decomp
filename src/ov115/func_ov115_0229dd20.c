/* func_ov115_0229dd20 @ 0x0229dd20, 0x40 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_ov114_0229d9d8(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern int **func_02070be8(void *unused0);
extern int data_ov115_0229e8b8;

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov115_0229dd20(void *self)
{
    *(void **) self = &data_ov115_0229e8b8;
    __cxa_vec_cleanup((char *) self + 0x13b8, 1, 0x6c, VisitElement_02070be8);
    func_ov114_0229d9d8((char *) self + 0xf8);
    func_ov002_02209cb4((char *) self + 0x94);
    func_ov002_0220826c(self);
    return self;
}

#undef VisitElement_02070be8
