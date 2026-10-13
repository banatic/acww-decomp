/* func_ov122_0229efe8 @ 0x0229efe8, 0x12 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229efe8 {
    unsigned char pad_00[0xa8];
    unsigned short unk_A8;
};
int func_ov122_0229efe8(struct UnkStruct_0229efe8 *p, unsigned short mask)
{
    return (p->unk_A8 & mask) ? 1 : 0;
}
