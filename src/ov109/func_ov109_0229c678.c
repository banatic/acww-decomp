/* func_ov109_0229c678 @ 0x0229c678, 0x34 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229c85c(char *param);
extern int func_ov109_0229c84c(char *param);
extern void func_ov002_0220a0b4(void *target, int a, int b);
extern void func_ov002_0220a374(void *target, int flag);

void func_ov109_0229c678(char *param)
{
    int a = func_ov109_0229c85c(param);
    int b = func_ov109_0229c84c(param);
    func_ov002_0220a0b4(param + 0x2274, a, b);
    func_ov002_0220a374(param + 0x2274, 1);
}
