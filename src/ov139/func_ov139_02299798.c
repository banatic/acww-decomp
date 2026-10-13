/* func_ov139_02299798 @ 0x02299798, 0x28 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_0229964c(int a, int b, int c, unsigned char d);
extern void func_ov139_022995e4(int a, int b, int c, unsigned char d);

void func_ov139_02299798(int param0, int param1)
{
    unsigned char v = (unsigned char) (14 - param1);
    func_ov139_0229964c(param0, param1, 0, v);
    func_ov139_022995e4(param0, param1, 0, v);
}
