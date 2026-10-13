/* func_ov112_0229fe50 @ 0x0229fe50, 0xe bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229fe50 {
    char pad_00[0xac];
    unsigned int unk_AC;
};

void func_ov112_0229fe50(struct UnkStruct_0229fe50 *s, unsigned int mask)
{
    unsigned int temp;
    temp = s->unk_AC;
    temp &= ~mask;
    s->unk_AC = temp;
}
