/* func_ov146_02299670 @ 0x02299670, 0x12 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299670 {
    char pad_00[0xac];
    unsigned short unk_AC;
};

int func_ov146_02299670(struct UnkStruct_02299670 *s, unsigned short mask)
{
    if ((s->unk_AC & mask) != 0) {
        return 1;
    } else {
        return 0;
    }
}
