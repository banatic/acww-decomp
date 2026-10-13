/* func_ov142_0229b59c @ 0x0229b59c, 0x4c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
void func_ov142_02299b08(int);
int func_ov142_0229b04c(int);
int func_ov142_0229afb0(int);
void func_ov002_0220a0b4(int, int, int);
void func_ov142_02299b94(int);
void func_ov002_02208098(int, int);

void func_ov142_0229b59c(int param)
{
    if (data_021fbe40 & 1) {
        int ret1;
        int ret2;
        func_ov142_02299b08(param);
        ret1 = func_ov142_0229b04c(param);
        ret2 = func_ov142_0229afb0(param);
        func_ov002_0220a0b4(param + 0xE8, ret1, ret2);
    } else {
        func_ov142_02299b94(param);
        func_ov002_02208098(param, 6);
    }
}
