/* func_ov100_0229c20c @ 0x0229c20c, 0x94 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov100_0229ecb8;
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

extern int **func_02070be8(void *unused0);

#define VisitElement_02070be8 (void *) func_02070be8

void *func_ov100_0229c20c(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_ov100_0229ecb8;
    __cxa_vec_cleanup((char *) self + 0x27e8, 2, 0x6c, VisitElement_02070be8);
    func_ov002_0220ba0c((char *) self + 0x26cc);
    func_ov002_02209ac8((char *) self + 0x22d8);
    func_ov002_02209cb4((char *) self + 0x2274);
    func_ov002_02209e38((char *) self + 0x225c);
    func_ov002_02207e28((char *) self + 0x218c);
    func_ov094_0229a2d0((char *) self + 0x0b54);
    func_ov094_0229bc30((char *) self + 0x0b2c);
    func_ov094_0229afe0((char *) self + 0xcc);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef VisitElement_02070be8
