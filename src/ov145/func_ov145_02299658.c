/* func_ov145_02299658 @ 0x02299658, 0xe bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299658 {
    char pad_00[0xb4];
    unsigned short unk_B4;
};

void func_ov145_02299658(struct UnkStruct_02299658 *self, unsigned short mask)
{
    self->unk_B4 |= mask;
}
