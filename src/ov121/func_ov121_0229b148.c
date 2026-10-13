/* func_ov121_0229b148 @ 0x0229b148, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern int func_ov121_0229a1e4(int);
extern int func_ov002_02208e28(int);
extern void func_ov002_02208098(int, int);

void func_ov121_0229b148(int param)
{
    if (func_ov002_02208e28(param + 0x528) != 0) {
        if (func_0206fe54() != 0) {
            func_ov121_0229a1e4(param);
            func_ov002_02208098(param, 0xc);
        } else {
            func_ov002_02208098(param, 3);
        }
    }
}
