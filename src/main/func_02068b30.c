/* func_02068b30 @ 0x02068b30, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020def3c;

struct UnkStruct_02068b30 {
    void *unk_00;
    int unk_04;
    char pad_08[12];
    int unk_14;
    int unk_18;
    char unk_1C;
    char unk_1D;
    char unk_1E;
    char pad_1F;
    int unk_20;
    int unk_24;
    int unk_28;
};

extern void func_02068ae4(struct UnkStruct_02068b30 *p, int flag);

struct UnkStruct_02068b30 *func_02068b30(struct UnkStruct_02068b30 *p, int arg)
{
    p->unk_00 = &data_020def3c;
    p->unk_04 = arg;
    p->unk_14 = 7;
    p->unk_18 = 0;
    p->unk_1C = 0;
    p->unk_1D = 0;
    p->unk_1E = 0;
    p->unk_20 = 5;
    p->unk_24 = 5;
    p->unk_28 = 0;
    func_02068ae4(p, 1);
    return p;
}
