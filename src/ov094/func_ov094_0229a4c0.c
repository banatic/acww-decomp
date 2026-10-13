/* func_ov094_0229a4c0 @ 0x0229a4c0, 0x18 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a4c0 {
    unsigned char pad_00[0xa58];
    unsigned char unk_A58;
};

int func_ov094_0229a4c0(struct UnkStruct_0229a4c0 *p)
{
    unsigned char val = p->unk_A58;
    if (val >= 3) {
        return 2;
    } else {
        p->unk_A58 = val + 1;
        return val;
    }
}
