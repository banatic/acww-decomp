/* func_ov107_0229c2a4 @ 0x0229c2a4, 0xe bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c2a4 {
    char pad_00[0x94];
    unsigned int unk_94;
};

void func_ov107_0229c2a4(struct UnkStruct_0229c2a4 *self, unsigned int mask)
{
    self->unk_94 |= mask;
}
