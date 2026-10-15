/* func_ov145_022995a0 @ 0x022995a0, 0x50 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *p, int a, int b, void *c);
extern int **func_02070be8(void *unused0);
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_0220a5e4(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_ov002_0220826c(void *p);

extern unsigned char data_ov145_0229ae00[];

#define VisitElement_02070be8 func_02070be8

void *func_ov145_022995a0(void *this)
{
    *(void **) this = (void *) data_ov145_0229ae00;
    __cxa_vec_cleanup((char *) this + 0x340, 0x12, 0x6c, VisitElement_02070be8);
    func_ov002_0220afdc((char *) this + 0x174);
    func_ov002_0220a5e4((char *) this + 0x12c);
    func_ov002_02209cb4((char *) this + 0xc8);
    func_ov002_0220826c(this);
    return this;
}

#undef VisitElement_02070be8
