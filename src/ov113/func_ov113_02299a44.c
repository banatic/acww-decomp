/* func_ov113_02299a44 @ 0x02299a44, 0x3c bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov113_022999c4(char *a0);
extern int func_ov113_022999a4(char *a0);
extern void func_ov002_0220a0b4(char *a0, int r1, int r2);
extern void func_ov002_0220a374(char *a0, int r1);
extern void func_ov113_022998ac(char *a0);

void func_ov113_02299a44(char *a0)
{
    int r1 = func_ov113_022999c4(a0);
    int r2 = func_ov113_022999a4(a0);
    func_ov002_0220a0b4(a0 + 0x2b20, r1, r2);
    func_ov002_0220a374(a0 + 0x2b20, 1);
    func_ov113_022998ac(a0);
}
