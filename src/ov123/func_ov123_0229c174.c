/* func_ov123_0229c174 @ 0x0229c174, 0x44 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_02299664(void);
extern int func_ov123_02299650(int, int);
extern void func_ov123_02299630(int, int);
extern void func_ov123_02299954(int);
extern void func_ov002_02207e9c(int, int, int);
extern void func_ov002_02208090(int, int);

void func_ov123_0229c174(int param)
{
    int *p;
    func_ov123_02299664();
    if (func_ov123_02299650(param, 0x00020000)) {
        func_ov123_02299630(param, 0x00020000);
        func_ov123_02299954(param);
    }
    func_ov002_02207e9c(param, 0, 0);
    func_ov002_02208090(param, 10);
    p = (int *) (param + 0x98);
    *p = 0x10;
}
