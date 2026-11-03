/* design_editor_input_3: 3 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_02299d44 @ 0x02299d44, 0x58 bytes, Thumb
 * func_ov123_02299d34 @ 0x02299d34, 0x10 bytes, Thumb
 * func_ov123_02299d24 @ 0x02299d24, 0x10 bytes, Thumb
 */

extern void func_ov123_02299ce0(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int val);
extern unsigned char data_ov123_0229ca54[];
extern unsigned char data_ov123_0229ca78[];

unsigned char func_ov123_02299d34(unsigned char *param0);
unsigned char func_ov123_02299d24(unsigned char *r0);

void func_ov123_02299d44(unsigned char *p)
{
    int a;
    int b;
    a = (int) func_ov123_02299d34(p);
    b = (int) func_ov123_02299d24(p);
    func_ov002_0220a0b4(p + 0x1cc, a, b);
    if ((unsigned char) (p[0xaa] + 0xe3) <= 1) {
        func_ov002_0220a374(p + 0x1cc, 7);
    } else {
        func_ov002_0220a374(p + 0x1cc, 1);
    }
    func_ov123_02299ce0(p);
}

unsigned char func_ov123_02299d34(unsigned char *param0)
{
    return data_ov123_0229ca54[param0[0xaa]];
}

unsigned char func_ov123_02299d24(unsigned char *r0)
{
    return data_ov123_0229ca78[r0[0xaa]];
}
