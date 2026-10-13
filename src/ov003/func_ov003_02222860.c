/* func_ov003_02222860 @ 0x02222860, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02222860 {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    int unk_0C;
};

extern void func_ov003_02222aa4(struct UnkStruct_02222860 *p);

void func_ov003_02222860(struct UnkStruct_02222860 *p)
{
    func_ov003_02222aa4(p);
    p->unk_04 = 0;
    p->unk_0C = 15;
    p->unk_08 = 0xfff1;
    p->unk_0A = 0xfff1;
}
