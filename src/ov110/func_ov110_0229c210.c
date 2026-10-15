/* func_ov110_0229c210 @ 0x0229c210, 0x98 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov110_0229ecb8[];
extern int **func_02070be8(void *unused0);
extern void __cxa_vec_cleanup(void *dest, int a, int b, void (*callback)(void *));
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

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov110_0229c210(void *this)
{
    *(int *) this = (int) data_ov110_0229ecb8;
    __cxa_vec_cleanup((char *) this + 0x2854, 2, 0x6c, VisitElement_02070be8);
    func_ov002_0220ba0c((char *) this + 0x2738);
    func_ov002_02209ac8((char *) this + 0x2344);
    func_ov002_02209cb4((char *) this + 0x22e0);
    func_ov002_02209e38((char *) this + 0x22c8);
    func_ov002_02207e28((char *) this + 0x21f8);
    func_ov094_0229a2d0((char *) this + 0x0bc0);
    func_ov094_0229bc30((char *) this + 0x0b98);
    func_ov094_0229afe0((char *) this + 0x0138);
    func_ov002_0220826c(this);
    func_ov002_02207f6c(this);
    return this;
}

#undef VisitElement_02070be8
