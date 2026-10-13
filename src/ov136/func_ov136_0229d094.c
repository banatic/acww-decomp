/* func_ov136_0229d094 @ 0x0229d094, 0x38 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov136_0229d044(int);
extern void func_ov002_02208090(int, int);

void func_ov136_0229d094(int self)
{
    int tmp;

    tmp = func_020ee45c(self);
    func_ov092_02299324(tmp, 0x44, 1);
    func_ov002_02207f04(self, 10, 0, 0, 0x30);
    func_ov136_0229d044(self);
    func_ov002_02208090(self, 3);
}
