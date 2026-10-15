/* func_ov126_022a1ed0 @ 0x022a1ed0, 0x1e bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov126_022a14d0(void *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);

struct UnkStruct_022a1ed0 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
};

int func_ov126_022a1ed0(struct UnkStruct_022a1ed0 *self)
{
    func_ov126_022a14d0(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}
