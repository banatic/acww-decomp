/* func_ov130_02299ac0 @ 0x02299ac0, 0x2e bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_02299a08(int a, int b, int c, int d);

void func_ov130_02299ac0(int a, int b, int c, int d, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        func_ov130_02299a08(a, b, c, d);
        c--;
    }
}
