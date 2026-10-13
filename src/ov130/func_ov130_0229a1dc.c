/* func_ov130_0229a1dc @ 0x0229a1dc, 0x48 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fdd4(unsigned char *a0, int a1, int a2, int a3, int a4, int a5);
extern void func_ov130_0229a168(unsigned char *p, int n);
extern void func_ov130_022999a8(unsigned char *p, int n);

void func_ov130_0229a1dc(unsigned char *p)
{
    int value;
    if (p[8] == 0 || p[8] == 2) {
        value = 18;
    } else {
        value = 10;
    }
    func_0206fdd4(p + 0xa90, value, 12, value + 12, 19, 2);
    func_ov130_0229a168(p, 10);
    func_ov130_022999a8(p, 2);
}
