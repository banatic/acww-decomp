/* func_ov096_022a1794 @ 0x022a1794, 0x38 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a1794 {
    char pad_00[0x98];
    void *unk_98;
};

extern int func_ov002_02207f48(struct UnkStruct_022a1794 *self, int a);
extern void func_ov002_022080a0(struct UnkStruct_022a1794 *self, int a);
extern void func_ov096_0229fb9c(struct UnkStruct_022a1794 *self);
extern void func_ov002_02207e80(struct UnkStruct_022a1794 *self, int a, int b, int c);
extern void *func_ov002_02207f60(struct UnkStruct_022a1794 *self);

void func_ov096_022a1794(struct UnkStruct_022a1794 *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0(self, 2);
        func_ov096_0229fb9c(self);
    }
    func_ov002_02207e80(self, 6, 0, 0);
    self->unk_98 = func_ov002_02207f60(self);
}
