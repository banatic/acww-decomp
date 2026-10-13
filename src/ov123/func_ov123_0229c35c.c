/* func_ov123_0229c35c @ 0x0229c35c, 0x3e bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_02299664(int arg);
extern int func_020ee45c(int arg);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(int a, int b, int c, int d, int e);
extern void func_ov123_0229c07c(int arg);
extern int func_ov002_02208090(int a, int b);

int func_ov123_0229c35c(int arg)
{
    func_ov123_02299664(arg);
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02207f04(arg, 0xb, 0, 0, 0x30);
    func_ov123_0229c07c(arg);
    return func_ov002_02208090(arg, 5);
}
