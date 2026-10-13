/* func_ov105_0229c330 @ 0x0229c330, 0xe bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c330 {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
};

void func_ov105_0229c330(struct UnkStruct_0229c330 *self, unsigned int mask)
{
    self->unk_94 |= mask;
}
