/* func_ov142_022995f0 @ 0x022995f0, 0x58 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022995f0 {
    void *unk_00;
} UnkStruct_022995f0;

extern int data_ov142_0229c3e8;
extern int **func_02070be8(void *unused0);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220a5e4(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov142_022995f0(UnkStruct_022995f0 *self)
{
    self->unk_00 = &data_ov142_0229c3e8;
    __cxa_vec_cleanup((char *) self + 0x360, 14, 0x6c, VisitElement_02070be8);
    func_ov002_0220afdc((char *) self + 0x194);
    func_ov002_0220a5e4((char *) self + 0x14c);
    func_ov002_02209cb4((char *) self + 0xe8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef VisitElement_02070be8
