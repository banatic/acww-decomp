/* func_ov126_0229f720 @ 0x0229f720, 0x88 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220ba0c(void *);
extern void *func_020707b8(void *);
extern void *func_02070be8(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220afdc(void *);
extern void __cxa_vec_cleanup(void *, unsigned int, unsigned int, void (*)(void *));
extern void *func_ov124_0229f43c(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern char data_ov126_022a20c8;

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov126_0229f720(void *self)
{
    *(void **) self = &data_ov126_022a20c8;
    func_ov002_0220ba0c((void *) ((char *) self + 0x412c));
    func_020707b8((void *) ((char *) self + 0x40cc));
    func_02070be8((void *) ((char *) self + 0x4060));
    func_02070be8((void *) ((char *) self + 0x3ff4));
    func_ov002_02209cb4((void *) ((char *) self + 0x3f90));
    func_ov002_0220afdc((void *) ((char *) self + 0x3dc4));
    __cxa_vec_cleanup((void *) ((char *) self + 0x24ec), 2, 0x6c, VisitElement_02070be8);
    func_ov124_0229f43c((void *) ((char *) self + 0xb0));
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef VisitElement_02070be8
