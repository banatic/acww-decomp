/* func_ov137_0229c854 @ 0x0229c854, 0x3c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c854;

extern int func_ov134_022999ac(int *p);
extern void func_ov134_02299980(int *p, int val);
extern void func_ov137_0229c564(struct UnkStruct_0229c854 *self, int param);
extern void func_ov137_0229c7d8(struct UnkStruct_0229c854 *self);
extern void func_ov002_02207fc0(struct UnkStruct_0229c854 *self);
extern void func_ov002_02208098(struct UnkStruct_0229c854 *self, int param);

struct UnkStruct_0229c854 {
    char pad_00[0x2c4];
    int unk_2C4;
};

void func_ov137_0229c854(struct UnkStruct_0229c854 *self)
{
    int tmp;
    tmp = func_ov134_022999ac(&self->unk_2C4);
    func_ov134_02299980(&self->unk_2C4, tmp);
    func_ov137_0229c564(self, 2);
    func_ov137_0229c7d8(self);
    func_ov002_02207fc0(self);
    func_ov002_02208098(self, 5);
}
