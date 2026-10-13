/* func_ov096_022a13b4 @ 0x022a13b4, 0x3c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229c3c4(char *p);
extern void func_ov002_022091cc(char *p);
extern void func_ov094_0229a05c(char *p);
extern int func_ov002_02207d5c(char *p);
extern void func_ov096_0229eb98(char *p);

void func_ov096_022a13b4(char *p)
{
    func_ov096_0229c3c4(p);
    func_ov002_022091cc(p + 0x2564);
    func_ov094_0229a05c(p + 0x0de0);
    if (func_ov002_02207d5c(p + 0x2418)) {
        func_ov096_0229eb98(p);
    }
}
