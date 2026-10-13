/* func_ov135_0229d178 @ 0x0229d178, 0x38 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov135_0229d128(int);
extern void func_ov002_02208090(int, int);

void func_ov135_0229d178(int param)
{
    int zero = 0;
    func_ov092_02299324(func_020ee45c(param), 0x44, 1);
    func_ov002_02207f04(param, 0xa, zero, zero, 0x30);
    func_ov135_0229d128(param);
    func_ov002_02208090(param, 3);
}
