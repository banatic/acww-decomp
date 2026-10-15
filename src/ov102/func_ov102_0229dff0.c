/* func_ov102_0229dff0 @ 0x0229dff0, 0x4c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94; // 0x021fbe94
extern int func_02002ca4(const void *a, int b, int c);
extern int func_02002c6c(const void *a, int b, int c, int d, int e, int f);
extern void func_ov102_0229c4c0(int a, int b);

extern unsigned char data_ov102_0229eb6c[];
extern unsigned char data_ov102_0229eb90[];

void func_ov102_0229dff0(int param0)
{
    int val = data_021fbe94;
    func_02002ca4((const void *) data_ov102_0229eb6c, val, 4);
    func_02002c6c((const void *) data_ov102_0229eb90, val, 4, 0x1b9, 0x1b9, 0x238);
    func_ov102_0229c4c0(param0, 0);
}
