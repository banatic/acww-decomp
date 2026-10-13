/* func_ov110_0229d98c @ 0x0229d98c, 0x3c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(int);
extern int func_0206fe54(void);
extern void func_ov110_0229ca7c(int);
extern void func_ov002_02208098(int, int);

void func_ov110_0229d98c(int param)
{
    if (func_ov002_02208e28(param + 0x2344) != 0) {
        if (func_0206fe54() != 0) {
            func_ov110_0229ca7c(param);
            func_ov002_02208098(param, 6);
        } else {
            func_ov002_02208098(param, 2);
        }
    }
}
