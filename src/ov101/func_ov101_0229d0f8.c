/* func_ov101_0229d0f8 @ 0x0229d0f8, 0x3c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(char *);
extern int func_0206fe54(void);
extern void func_ov101_0229c6d4(char *);
extern unsigned char *func_ov002_02208098(char *, unsigned char value);

void func_ov101_0229d0f8(char *param)
{
    if (func_ov002_02208e28(param + 0x2300)) {
        if (func_0206fe54()) {
            func_ov101_0229c6d4(param);
            func_ov002_02208098(param, 8);
        } else {
            func_ov002_02208098(param, 4);
        }
    }
}
