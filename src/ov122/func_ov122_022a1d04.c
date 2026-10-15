/* func_ov122_022a1d04 @ 0x022a1d04, 0x5a bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    unsigned int unk_94;
} SelfType;

extern int func_ov002_02207f48(SelfType *self, int arg);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207e80(SelfType *self, int mode, int a, int b);
extern int func_ov002_02207f60(SelfType *self);
extern void func_ov122_0229fedc(SelfType *self);
extern unsigned char *func_ov122_022a0018(SelfType *self);

void func_ov122_022a1d04(SelfType *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov122_0229fedc(self);
        func_ov122_022a0018(self);
    }
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02207e80(self, 4, 0, ~0xf);
    func_ov002_02207e80(self, 3, 0, ~0xf);
    self->unk_94 = func_ov002_02207f60(self);
}
