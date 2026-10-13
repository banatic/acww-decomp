/* func_ov135_0229ca70 @ 0x0229ca70, 0x3c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229a24c(char *p);
extern int func_ov134_0229a8a0(char *p);
extern void func_ov135_0229ca1c(char *p);

void func_ov135_0229ca70(char *param)
{
    if (func_ov134_0229a24c(param + 0x2c8)) {
        int r = func_ov134_0229a8a0(param + 0x2c8);
        if (r == 6) {
            *(param + 0x95) = 5;
        } else {
            *(param + 0x95) = r;
        }
        func_ov135_0229ca1c(param);
    }
}
