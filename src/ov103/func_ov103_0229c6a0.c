/* func_ov103_0229c6a0 @ 0x0229c6a0, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229c820(char *param);
extern int func_ov103_0229c810(char *param);
extern void func_ov002_0220a0b4(void *target, int a, int b);
extern void func_ov002_0220a374(void *target, int flag);

void func_ov103_0229c6a0(char *param)
{
    int a = func_ov103_0229c820(param);
    int b = func_ov103_0229c810(param);
    func_ov002_0220a0b4(param + 0x2274, a, b);
    func_ov002_0220a374(param + 0x2274, 1);
}
