/* func_ov142_022995a0 @ 0x022995a0, 0x50 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220a5e4(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern int **func_02070be8(void *unused0);

extern unsigned char data_ov142_0229c3e8[];

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov142_022995a0(void *self)
{
    char *base = self;
    *(unsigned int *) base = (unsigned int) data_ov142_0229c3e8;
    __cxa_vec_cleanup(base + 0x360, 0xe, 0x6c, VisitElement_02070be8);
    func_ov002_0220afdc(base + 0x194);
    func_ov002_0220a5e4(base + 0x14c);
    func_ov002_02209cb4(base + 0xe8);
    func_ov002_0220826c(base);
    return self;
}

#undef VisitElement_02070be8
