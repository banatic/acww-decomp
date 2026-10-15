/* func_ov105_0229dee4 @ 0x0229dee4, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov105_0229cdf0(int);
extern int func_ov002_02208e28(int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov105_0229dee4(int param)
{
    if (func_ov002_02208e28(param + 0x2508) != 0) {
        if (func_0206fe54() != 0) {
            func_ov105_0229cdf0(param);
            func_ov002_02208098(param, 0xb);
        } else {
            func_ov002_02208098(param, 6);
        }
    }
}
