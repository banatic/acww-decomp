/* func_ov111_0229ef08 @ 0x0229ef08, 0x70 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov111_022a1008[];
extern char data_ov111_022a0ff0[];
extern void *func_ov002_0220ba0c(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_020a887c(void *p);
extern void *func_0203a3ec(void *p);
extern __arm void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void *));
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern int **func_02070be8(void *unused0);

struct UnkStruct_0229ef08 {
    void *unk_00;
    u8 pad_04[0x3d04];
    void *unk_3D08;
    u8 pad_3D0C[0x90];
};

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

struct UnkStruct_0229ef08 *func_ov111_0229ef08(struct UnkStruct_0229ef08 *self)
{
    self->unk_00 = (void *) data_ov111_022a1008;
    func_ov002_0220ba0c((char *) self + 0x3d9c);
    func_ov002_02209cb4((char *) self + 0x3d38);
    self->unk_3D08 = (void *) data_ov111_022a0ff0;
    func_020a887c(&self->unk_3D08);
    func_0203a3ec((char *) self + 0x3cd4);
    __cxa_vec_cleanup((char *) self + 0x23fc, 2, 0x6c, VisitElement_02070be8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef VisitElement_02070be8
