/* func_ov004_022339e0 @ 0x022339e0, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022339e0 {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    int unk_0C;
};

extern void func_ov004_02233aa4(struct UnkStruct_022339e0 *p);

void func_ov004_022339e0(struct UnkStruct_022339e0 *p)
{
    func_ov004_02233aa4(p);
    p->unk_04 = 0;
    p->unk_0C = 1;
    p->unk_08 = 0xfff1;
    p->unk_0A = 0xfff1;
}
