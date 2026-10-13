/* func_ov123_0229a340 @ 0x0229a340, 0x22 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_0229a8dc(void *ptr, unsigned char a, unsigned char b);
extern void func_ov123_0229b160(void *ptr, int val);

struct func_ov123_0229a340_unk {
    unsigned char pad_00[0xaf];
    unsigned char unk_AF;
    unsigned char unk_B0;
};

void func_ov123_0229a340(struct func_ov123_0229a340_unk *p)
{
    func_ov123_0229b160(p, func_ov123_0229a8dc(p, p->unk_AF, p->unk_B0));
}
