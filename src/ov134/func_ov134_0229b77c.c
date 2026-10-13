/* func_ov134_0229b77c @ 0x0229b77c, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0229b77c;
struct UnkStruct_0229b77c {
    char pad_00[0xA3];
    unsigned char unk_A3;
    char pad_A4[0x17];
    unsigned char unk_BB;
};

void func_ov134_0229b5ac(struct UnkStruct_0229b77c *p, unsigned char b, int c, int d, unsigned char e, int f, int g);

void func_ov134_0229b77c(struct UnkStruct_0229b77c *p)
{
    func_ov134_0229b5ac(p, p->unk_A3, 0x19c, 3, p->unk_BB, 15, 0);
}
