/* func_ov099_0229de98 @ 0x0229de98, 0x20 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov099_0229d994(unsigned char *arg0);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);

int func_ov099_0229de98(int param)
{
    int r4 = param;
    func_ov099_0229d994((unsigned char *) param);
    func_ov002_02208090(r4, 0);
    func_ov002_022080a0(r4, 0);
    return 1;
}
