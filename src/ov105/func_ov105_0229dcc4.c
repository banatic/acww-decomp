/* func_ov105_0229dcc4 @ 0x0229dcc4, 0x6c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(int self, int a);
extern void func_ov105_0229da9c(int self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_0220a784(int ptr, int a);
extern void func_ov105_0229c62c(int self);
extern void func_ov105_0229c5fc(int self);

void func_ov105_0229dcc4(int self)
{
    unsigned int ok;
    if (func_ov002_02208054(self, 1)) {
        func_ov105_0229da9c(self);
        return;
    }
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }
    if (func_ov002_0220a784(self + 0x5fb8, 3)) {
        func_ov105_0229c62c(self);
    }
    if (func_ov002_0220a784(self + 0x5fb8, 4)) {
        func_ov105_0229c5fc(self);
    }
}
