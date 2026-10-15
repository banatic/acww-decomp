/* func_ov113_022995f0 @ 0x022995f0, 0x54 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02209c60(void *p);
extern void __cxa_vec_cleanup(void *p, int size, int count, void (*callback3)(void *));
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern int **func_02070be8(void *element);

typedef struct {
    void *unk_00;
} Module;

extern unsigned char data_ov113_0229ac00[];

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

Module *func_ov113_022995f0(Module *self)
{
    self->unk_00 = (void *) data_ov113_0229ac00;
    func_ov002_02209c60((char *) self + 0x2b20);
    __cxa_vec_cleanup((char *) self + 0x2898, 6, 0x6c, DisposeElement_func_02070be8);
    __cxa_vec_cleanup((char *) self + 0x26e8, 4, 0x6c, DisposeElement_func_02070be8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef DisposeElement_func_02070be8
