/* func_ov003_0221efa4 @ 0x0221efa4, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ca0ec;

struct UnkStruct_0221efa4 {
    char unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
};

void func_ov003_0221efa4(struct UnkStruct_0221efa4 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_14 = 0x11;
    p->unk_10 = data_020ca0ec * 8;
}
