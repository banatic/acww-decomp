/* func_ov123_0229bfe0 @ 0x0229bfe0, 0x64 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bfe0 {
    unsigned char pad_00[0x98];
    int unk_98;
    int unk_9C;
    unsigned char pad_A0[6];
    unsigned char unk_A6;
    unsigned char pad_A7[3];
    unsigned char unk_AA;
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char pad_AD[2];
    unsigned char unk_AF;
    unsigned char unk_B0;
    unsigned char pad_B1[2];
    unsigned char unk_B3;
};

extern void func_ov123_0229b160(struct UnkStruct_0229bfe0 *p, int x);
extern void func_ov123_0229a224(struct UnkStruct_0229bfe0 *p);
extern void func_ov123_02299ec4(struct UnkStruct_0229bfe0 *p);
extern int func_0206fc4c(int x);
extern void func_02095ce0(int x);

void func_ov123_0229bfe0(struct UnkStruct_0229bfe0 *p)
{
    func_ov123_0229b160(p, 1);
    p->unk_9C = 0;
    p->unk_A6 = 0x22;
    func_ov123_0229a224(p);
    p->unk_AA = 0;
    p->unk_AB = 0;
    p->unk_AC = 0;
    func_ov123_02299ec4(p);
    p->unk_AF = 0x10;
    p->unk_B0 = 0x10;
    func_02095ce0(func_0206fc4c(0));
    p->unk_98 = 0;
    p->unk_B3 = 0;
}
