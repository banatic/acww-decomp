/* func_ov120_0229b604 @ 0x0229b604, 0x48 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e95c(int, int);
extern void func_ov120_0229a870(int);
extern void func_ov002_02207fc0(int);
extern int func_ov120_0229a448(int, int);
extern void func_ov002_02208098(int, int);

void func_ov120_0229b604(int r0)
{
    int r4 = r0;
    func_0208e95c(r4 + 0x674, 1);
    func_ov120_0229a870(r4);
    func_ov002_02207fc0(r4);
    if (func_ov120_0229a448(r4, 0x800) != 0) {
        func_ov002_02208098(r4, 9);
    } else {
        func_ov002_02208098(r4, 2);
    }
}
