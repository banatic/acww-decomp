/* func_ov103_0229c868 @ 0x0229c868, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229c820(int);
extern int func_ov103_0229c810(int);
extern void func_ov103_0229c680(int);
extern void func_ov002_0220a0b4(int, int, int);
extern void func_ov002_0220a374(int, int);

void func_ov103_0229c868(int param)
{
    int v1 = func_ov103_0229c820(param);
    int v2 = func_ov103_0229c810(param);
    func_ov002_0220a0b4(param + 0x2274, v1, v2);
    func_ov002_0220a374(param + 0x2274, 1);
    func_ov103_0229c680(param);
}
