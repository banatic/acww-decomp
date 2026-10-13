/* func_ov138_0229c574 @ 0x0229c574, 0x12 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c574 {
    unsigned char pad_00[0x92];
    unsigned short unk_92;
};
int func_ov138_0229c574(struct UnkStruct_0229c574 *p, unsigned short mask)
{
    if ((p->unk_92 & mask) != 0) {
        return 1;
    }
    return 0;
}
