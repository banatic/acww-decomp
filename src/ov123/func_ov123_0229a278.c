/* func_ov123_0229a278 @ 0x0229a278, 0x3c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xA4];
    volatile unsigned char unk_A4;
} UnkStruct_0229a278;

extern void func_ov123_0229a2f8(UnkStruct_0229a278 *p, unsigned char b, int n);
extern void func_0200467c(int);

void func_ov123_0229a278(UnkStruct_0229a278 *p, unsigned char val)
{
    unsigned char cur = p->unk_A4;
    if (cur != val) {
        if (cur != 0x22) {
            func_ov123_0229a2f8(p, cur, 4);
            func_0200467c(0xb);
        }
        p->unk_A4 = val;
        func_ov123_0229a2f8(p, p->unk_A4, 5);
    }
}
