/* func_ov140_02299ee0 @ 0x02299ee0, 0x54 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov140_0229b404;
extern void __cxa_vec_cleanup(void *base, int a, int b, void (*cb)(void *));
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_ov139_02299b30(void *p);
extern void *func_ov002_0220826c(void *p);
extern int **func_02070be8(void *unused0);

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov140_02299ee0(void *self)
{
    ((char **) self)[0] = &data_ov140_0229b404;
    __cxa_vec_cleanup((char *) self + 0x1abc, 3, 0x6c, VisitElement_02070be8);
    func_ov002_0220afdc((char *) self + 0x12f0);
    func_ov002_02209cb4((char *) self + 0x128c);
    func_ov139_02299b30((char *) self + 0x8e8);
    func_ov002_0220826c(self);
    return self;
}

#undef VisitElement_02070be8
