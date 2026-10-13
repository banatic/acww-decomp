/* func_ov134_0229a1d8 @ 0x0229a1d8, 0x16 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
} UnkStruct_0229a1d8;

extern void func_ov134_0229a1b4(UnkStruct_0229a1d8 *self, int val);
extern void func_ov134_02299fd0(UnkStruct_0229a1d8 *self);

void func_ov134_0229a1d8(UnkStruct_0229a1d8 *self, int val)
{
    self->unk_00 = val;
    func_ov134_0229a1b4(self, val);
    func_ov134_02299fd0(self);
}
