/* func_ov123_02299d44 @ 0x02299d44, 0x58 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299d34(unsigned char *p);
extern int func_ov123_02299d24(unsigned char *p);
extern void func_ov123_02299ce0(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int val);

void func_ov123_02299d44(unsigned char *p)
{
    int a;
    int b;
    a = func_ov123_02299d34(p);
    b = func_ov123_02299d24(p);
    func_ov002_0220a0b4(p + 0x1cc, a, b);
    if ((unsigned char) (p[0xaa] + 0xe3) <= 1) {
        func_ov002_0220a374(p + 0x1cc, 7);
    } else {
        func_ov002_0220a374(p + 0x1cc, 1);
    }
    func_ov123_02299ce0(p);
}
