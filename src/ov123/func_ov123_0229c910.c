/* func_ov123_0229c910 @ 0x0229c910, 0x1e bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c910 {
    char pad_00[0x8c];
    char unk_8C;
};

extern void func_ov123_0229bfe0(struct UnkStruct_0229c910 *p);
extern void func_ov002_022080a0(struct UnkStruct_0229c910 *p, int n);

int func_ov123_0229c910(struct UnkStruct_0229c910 *self)
{
    func_ov123_0229bfe0(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}
