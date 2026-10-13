/* func_ov144_02299670 @ 0x02299670, 0xe bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299670 {
    char pad_00[0xb4];
    unsigned short unk_B4;
};
void func_ov144_02299670(struct UnkStruct_02299670 *s, unsigned short v)
{
    s->unk_B4 |= v;
}
