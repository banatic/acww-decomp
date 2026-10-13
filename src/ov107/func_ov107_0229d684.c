/* func_ov107_0229d684 @ 0x0229d684, 0x3c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov107_0229cd1c(int);
extern void func_ov002_02208098(int, int);
extern int func_ov002_02208e28(int);

void func_ov107_0229d684(int param)
{
    if (func_ov002_02208e28(param + 0x2318) != 0) {
        if (func_0206fe54() != 0) {
            func_ov107_0229cd1c(param);
            func_ov002_02208098(param, 6);
        } else {
            func_ov002_02208098(param, 4);
        }
    }
}
