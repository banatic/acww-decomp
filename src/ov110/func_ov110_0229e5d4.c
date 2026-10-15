/* func_ov110_0229e5d4 @ 0x0229e5d4, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov110_0229d840(void *);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

struct UnkStruct_0229e5d4 {
    char pad_00[0x9c];
    int unk_9C;
};

void func_ov110_0229e5d4(struct UnkStruct_0229e5d4 *self)
{
    int zero = 0;

    if (func_ov002_02207f48(self, zero)) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov110_0229d840(self);
    }
    func_ov002_02207e80(self, 4, zero, zero);
    self->unk_9C = func_ov002_02207f60(self);
}
