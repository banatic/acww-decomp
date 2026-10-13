/* func_020f1108 @ 0x020f1108, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f0ddc(void *p, int len);
extern void func_020f0d98(void *p, int a, int b);

void func_020f1108(char *s)
{
    s[0x60] = 1;
    func_020f0ddc(s + 0x10, 0x7f);
    func_020f0ddc(s + 0x1c, 0x7f);
    func_020f0d98(s + 0x10, 0x46, 0x0f);
    func_020f0d98(s + 0x1c, 0x28, 0x0f);
}
