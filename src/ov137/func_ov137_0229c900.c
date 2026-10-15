/* func_ov137_0229c900 @ 0x0229c900, 0x2c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov137_0229c734(char *a);
extern void func_ov134_0229a5c8(char *a, int b);
extern unsigned char *func_ov002_02208098(char *a, unsigned char value);

void func_ov137_0229c900(char *a, int b)
{
    func_ov137_0229c734(a);
    func_ov134_0229a5c8(a + 0x2c4, b);
    func_ov002_02208098(a, 0xc);
}
