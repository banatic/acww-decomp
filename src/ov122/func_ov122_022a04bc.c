/* func_ov122_022a04bc @ 0x022a04bc, 0x30 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov122_0229ff2c(int);
extern void func_ov122_0229ff94(int);
extern int func_ov002_02208e28(int);

void func_ov122_022a04bc(int param)
{
    if (func_ov002_02208e28(param + 0x42b0) != 0) {
        if (func_0206fe54() != 0) {
            func_ov122_0229ff2c(param);
        } else {
            func_ov122_0229ff94(param);
        }
    }
}
