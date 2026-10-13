/* func_ov099_0229c7d0 @ 0x0229c7d0, 0x3c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229c788(int);
extern int func_ov099_0229c778(int);
extern void func_ov099_0229c5e8(int);
extern void func_ov002_0220a0b4(int, int, int);
extern void func_ov002_0220a374(int, int);

void func_ov099_0229c7d0(int param)
{
    int v1 = func_ov099_0229c788(param);
    int v2 = func_ov099_0229c778(param);
    func_ov002_0220a0b4(param + 0x2274, v1, v2);
    func_ov002_0220a374(param + 0x2274, 1);
    func_ov099_0229c5e8(param);
}
