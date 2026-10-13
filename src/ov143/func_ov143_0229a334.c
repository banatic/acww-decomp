/* func_ov143_0229a334 @ 0x0229a334, 0x40 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int data_020df2a0;

extern int func_ov143_02299650(char *param, int x);
extern void func_ov143_02299b04(char *param);
extern int func_ov143_02299630(char *param, int x);

void func_ov143_0229a334(char *param)
{
    int g = data_020df2a0;
    if (g == -1 || g >= 16) {
        if (func_ov143_02299650(param, 8) != 0) {
            return;
        }
        func_ov143_02299b04(param);
        return;
    } else {
        func_ov143_02299630(param, 8);
        param += 0x9a;
        *(unsigned short *) param = (unsigned short) g;
    }
}
