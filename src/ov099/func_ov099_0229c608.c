/* func_ov099_0229c608 @ 0x0229c608, 0x34 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229c788(char *param);
extern int func_ov099_0229c778(char *param);
extern void func_ov002_0220a0b4(void *target, int a, int b);
extern void func_ov002_0220a374(void *target, int flag);

void func_ov099_0229c608(char *param)
{
    int a = func_ov099_0229c788(param);
    int b = func_ov099_0229c778(param);
    func_ov002_0220a0b4(param + 0x2274, a, b);
    func_ov002_0220a374(param + 0x2274, 1);
}
