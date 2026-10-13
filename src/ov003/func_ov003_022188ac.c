/* func_ov003_022188ac @ 0x022188ac, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(char *p, int a1, int a2, int a3);
extern int func_02077910(char *p, int a3);

int func_ov003_022188ac(char *p, int a1, int a2, int a3)
{
    func_020779b8(p, a1, a2, a3);
    return func_02077910(p + 5, a3);
}
