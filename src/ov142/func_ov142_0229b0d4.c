/* func_ov142_0229b0d4 @ 0x0229b0d4, 0x36 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229b04c(int);
extern int func_ov142_0229afb0(int);
extern void func_ov002_0220a0b4(int, int, int);
extern void func_ov002_0220a374(int, int);
extern void func_ov142_0229af00(int);

void func_ov142_0229b0d4(int r0)
{
    int r4;
    int r5;
    int r2;

    r5 = r0;
    r4 = func_ov142_0229b04c(r0);
    r2 = func_ov142_0229afb0(r0);
    func_ov002_0220a0b4(r0 + 0xe8, r4, r2);
    func_ov002_0220a374(r0 + 0xe8, 1);
    func_ov142_0229af00(r0);
}
