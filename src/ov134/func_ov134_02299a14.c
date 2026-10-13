/* func_ov134_02299a14 @ 0x02299a14, 0x26 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229a1d8(void *self, int value);

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x5c];
    int unk_64;
    char pad_68[0x24];
    int unk_8C;
} UnkStruct_02299a14;

int func_ov134_02299a14(UnkStruct_02299a14 *self)
{
    func_ov134_0229a1d8(self, (self->unk_8C * (self->unk_64 - 0x20)) / 0x80);
    self->unk_04 = 0;
    return 0;
}
