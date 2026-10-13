/* func_ov142_0229a4d4 @ 0x0229a4d4, 0x6c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a4d4 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    unsigned char pad_A0[4];
    int unk_A4;
    unsigned char pad_A8[0x0c];
    short unk_B4;
};

extern void func_ov142_02299648(struct UnkStruct_0229a4d4 *arg0, int arg1);
extern void func_ov142_02299658(struct UnkStruct_0229a4d4 *arg0, int arg1);
extern void func_ov142_0229a5cc(struct UnkStruct_0229a4d4 *arg0);
extern void func_0200284c(int arg0, int arg1, int arg2);

void func_ov142_0229a4d4(struct UnkStruct_0229a4d4 *self, int value)
{
    func_ov142_02299648(self, 0x0C00);
    if (value <= 0) {
        func_ov142_02299658(self, 0x400);
    }
    if (value >= self->unk_A4) {
        func_ov142_02299658(self, 0x800);
    }
    self->unk_9C = value;
    func_0200284c(4, 0, self->unk_9C - 0x20);
    self->unk_B4 = (short) (value >> 4);
    func_ov142_0229a5cc(self);
    func_ov142_02299658(self, 4);
}
