/* func_ov131_0229ad44 @ 0x0229ad44, 0x18 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ad44 {
    unsigned char pad_00[0x1554];
    unsigned short flag;
};

int func_ov131_0229ad44(struct UnkStruct_0229ad44 *s, unsigned short mask)
{
    if (s->flag & mask) {
        return 1;
    }
    return 0;
}
