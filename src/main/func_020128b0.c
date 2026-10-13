/* func_020128b0 @ 0x020128b0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020128b0 {
    int pad_00[5];
    int unk_14;
    int unk_18;
};

struct UnkStruct_020128b0_2 {
    int unk_00;
    int pad_04;
    int unk_08;
};

int func_020128b0(struct UnkStruct_020128b0 *p, struct UnkStruct_020128b0_2 *q)
{
    int a = q->unk_08 >> 17;
    int b = q->unk_00 >> 17;
    if (b == p->unk_14 && a == p->unk_18) {
        return 1;
    }
    return 0;
}
