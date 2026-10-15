/* func_ov122_0229ef30 @ 0x0229ef30, 0x98 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov122_022a2738;
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_02065c98(void *);
extern void *func_0206da80(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220a5e4(void *);
extern void *func_0206e35c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int **func_02070be8(void *unused0);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov122_0229ef30(void *self)
{
    *(void **) self = &data_ov122_022a2738;
    func_ov002_0220ba0c((char *) self + 0x4864);
    func_ov002_0220afdc((char *) self + 0x4698);
    func_ov002_02209ac8((char *) self + 0x42b0);
    func_02065c98((char *) self + 0x4150);
    func_0206da80((char *) self + 0x40bc);
    func_ov002_02209cb4((char *) self + 0x4058);
    func_ov002_0220a5e4((char *) self + 0x4010);
    func_0206e35c((char *) self + 0x3ce8);
    __cxa_vec_cleanup((char *) self + 0x2410, 2, 0x6c, VisitElement_02070be8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef VisitElement_02070be8
