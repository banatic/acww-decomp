/* func_ov112_022a14d8 @ 0x022a14d8, 0x48 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a14d8 {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
};

extern int func_ov002_02207f3c(struct UnkStruct_022a14d8 *self, int arg);
extern void func_020027f0(int arg);
extern void func_ov002_022080a0(struct UnkStruct_022a14d8 *self, int arg);
extern void func_ov002_02207e80(struct UnkStruct_022a14d8 *self, int a, int b, int c);
extern int func_ov002_02207f60(struct UnkStruct_022a14d8 *self);

void func_ov112_022a14d8(struct UnkStruct_022a14d8 *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(4);
        func_ov002_022080a0(self, 5);
    } else {
        func_ov002_02207e80(self, 4, 0, -8);
    }
    self->unk_A4 = func_ov002_02207f60(self);
    self->unk_A8 = self->unk_A4;
}
