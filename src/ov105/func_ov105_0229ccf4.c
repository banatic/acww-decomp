/* func_ov105_0229ccf4 @ 0x0229ccf4, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(char *a, int b);
extern void func_ov002_0220a374(char *a, int b);
extern unsigned char *func_ov002_02208098(char *a, unsigned char value);

void func_ov105_0229ccf4(char *arg0, char arg1)
{
    func_ov002_02207d24(arg0 + 0x23bc, 1);
    arg0[0x2bc] = arg1;
    func_ov002_0220a374(arg0 + 0x24a4, 5);
    func_ov002_02208098(arg0, 0x12);
}
