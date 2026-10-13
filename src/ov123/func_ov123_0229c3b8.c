/* func_ov123_0229c3b8 @ 0x0229c3b8, 0x90 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(int, int);
extern void func_ov123_02299630(int, int);
extern void func_ov002_02208090(int, int);
extern void func_ov123_0229c35c(int);
extern int func_020984e8(void);
extern int func_02099710(int);
extern int func_02095b58(int);
extern int func_020996f8(int);
extern int func_02095b40(int);

void func_ov123_0229c3b8(int param)
{
    if (func_ov123_02299650(param, 0x8000) == 0 && func_ov123_02299650(param, 0x10000) == 0) {
        func_ov002_02208090(param, 4);
        func_ov123_0229c35c(param);
        return;
    }

    {
        int r4 = func_020984e8();
        if (func_ov123_02299650(param, 0x8000) != 0) {
            if (func_02095b58(func_02099710(r4)) != 0) {
                func_ov123_02299630(param, 0x8000);
            } else {
                return;
            }
        }
        if (func_ov123_02299650(param, 0x10000) != 0) {
            if (func_02095b40(func_020996f8(r4)) != 0) {
                func_ov123_02299630(param, 0x8000);
            } else {
                return;
            }
        }
        func_ov002_02208090(param, 3);
    }
}
