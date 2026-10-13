/* func_ov096_0229e9f8 @ 0x0229e9f8, 0x3c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a99c(void *sub, unsigned short a, unsigned char b);
extern void func_ov096_0229e258(void *p);

struct UnkStruct_0229e9f8 {
    unsigned char pad_00;
};

struct UnkStruct_0229e9f8_2 {
    unsigned char pad_00[0xAC];
    unsigned short unk_AC;
    unsigned char pad_AE[2];
    unsigned char unk_B0;
    unsigned char unk_B1;
    unsigned char pad_B2[0x2A6];
    struct UnkStruct_0229e9f8 sub;
};

void func_ov096_0229e9f8(struct UnkStruct_0229e9f8_2 *p, unsigned short a, unsigned char b)
{
    p->unk_B1 = 2;
    p->unk_AC = a;
    p->unk_B0 = b;
    func_ov094_0229a99c(&p->sub, p->unk_AC, p->unk_B0);
    func_ov096_0229e258(p);
}
