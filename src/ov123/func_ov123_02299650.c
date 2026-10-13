/* func_ov123_02299650 @ 0x02299650, 0x12 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299650 {
    char pad_00[0x9c];
    int unk_9C;
};

int func_ov123_02299650(struct UnkStruct_02299650 *s, int mask)
{
    int tmp = s->unk_9C & mask;
    if (tmp != 0) {
        return 1;
    } else {
        return 0;
    }
}
