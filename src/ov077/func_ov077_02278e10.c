/* func_ov077_02278e10 @ 0x02278e10, 0xe bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02278e10 {
    char pad_00[0xb0];
    int unk_B0;
    char unk_B4;
};

void func_ov077_02278e10(struct UnkStruct_02278e10 *self, int value)
{
    self->unk_B0 = value;
    self->unk_B4 = 0x5a;
}
