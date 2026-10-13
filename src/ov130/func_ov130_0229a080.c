/* func_ov130_0229a080 @ 0x0229a080, 0x24 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a080 {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char unk_05;
};

extern void func_ov130_0229a254(struct UnkStruct_0229a080 *self);

int func_ov130_0229a080(struct UnkStruct_0229a080 *self)
{
    unsigned char b = self->unk_05;
    if ((unsigned char) (b + 0xf5) <= 1) {
        return 0;
    }
    self->unk_04 = b;
    func_ov130_0229a254(self);
    return 1;
}
