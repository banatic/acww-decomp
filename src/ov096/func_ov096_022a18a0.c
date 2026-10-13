/* func_ov096_022a18a0 @ 0x022a18a0, 0x3c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_022a1394(char *p);
extern void func_ov094_0229a204(char *p, int a);
extern void func_ov002_02208090(char *p, int a);
extern int func_ov096_0229c2fc(char *p, int a);
extern void func_ov096_022a186c(char *p);

void func_ov096_022a18a0(char *p)
{
    func_ov096_022a1394(p);
    func_ov094_0229a204(p + 0xde0, 1);
    func_ov002_02208090(p, 1);
    if (func_ov096_0229c2fc(p, 0x80000) == 0) {
        func_ov096_022a186c(p);
    }
}
