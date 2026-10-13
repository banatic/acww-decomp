/* func_0202fb28 @ 0x0202fb28, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __arm FX_MulFunc(int, int);

struct UnkStruct_0202fb28 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
};

struct UnkStruct_0202fb28_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

int func_0202fb28(struct UnkStruct_0202fb28 *a, struct UnkStruct_0202fb28_2 *b)
{
    int t0 = a->unk_34;
    int t1 = FX_MulFunc(a->unk_30, b->unk_08);
    int t2 = FX_MulFunc(a->unk_28, b->unk_00);
    int t3 = FX_MulFunc(a->unk_2C, b->unk_04);
    return t0 + (t1 + (t2 + t3));
}
