/* func_ov110_0229d860 @ 0x0229d860, 0x34 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xf3];
    unsigned char unk_F3;
    char pad_F4;
    unsigned char unk_F5;
} UnkStruct_0229d860;

extern void func_ov110_0229cc58(UnkStruct_0229d860 *self);
extern void func_ov002_02207fc0(UnkStruct_0229d860 *self);
extern void func_ov110_0229ce44(UnkStruct_0229d860 *self);
extern void func_ov002_02208098(UnkStruct_0229d860 *self, int arg);
extern void func_ov110_0229cff8(UnkStruct_0229d860 *self, unsigned char arg);

void func_ov110_0229d860(UnkStruct_0229d860 *self)
{
    self->unk_F3 = 0x1f;
    func_ov110_0229cc58(self);
    func_ov002_02207fc0(self);
    func_ov110_0229ce44(self);
    func_ov002_02208098(self, 4);
    func_ov110_0229cff8(self, self->unk_F5);
}
