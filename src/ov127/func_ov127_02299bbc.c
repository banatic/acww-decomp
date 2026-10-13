/* func_ov127_02299bbc @ 0x02299bbc, 0x4c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299878(char *p, int n);
extern void func_ov127_02299858(char *p, int n);
extern void func_02004644(int a, int b);
extern void func_ov127_02299cd8(char *p, int n, int a, int b);

void func_ov127_02299bbc(char *p0, int p1)
{
    if (func_ov127_02299878(p0, 8)) {
        func_ov127_02299858(p0, 8);
        func_02004644(0x883, 1);
    }
    func_ov127_02299cd8(p0, p1, 1, 0);
    *(p0 + 0x2836) = 2;
    *(p0 + 0x2835) = p1;
}
