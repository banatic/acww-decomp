/* func_ov139_022997c0 @ 0x022997c0, 0x2e bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_0229964c(int a, int b, void *c, unsigned char x);
extern void func_ov139_022995e4(int a, int b, void *c, unsigned char x);

void func_ov139_022997c0(int a, int b, void *c)
{
    unsigned char x = (unsigned char) (14 - b);
    func_ov139_0229964c(a, b, c, x);
    func_ov139_022995e4(a, b, (char *) c + 12, x);
}
