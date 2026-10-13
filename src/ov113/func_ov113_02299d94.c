/* func_ov113_02299d94 @ 0x02299d94, 0xe bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299d94 {
    char pad_00[0x98];
    unsigned short unk_98;
};

void func_ov113_02299d94(struct UnkStruct_02299d94 *self, unsigned short val)
{
    self->unk_98 |= val;
}
