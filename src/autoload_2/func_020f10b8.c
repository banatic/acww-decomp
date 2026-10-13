/* func_020f10b8 @ 0x020f10b8, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f0ddc(void *p, int n);
extern void func_020f0d98(void *p, int n, int m);

void func_020f10b8(void *p)
{
    char *q = (char *) p;
    q[0x60] = 0;
    func_020f0ddc(q + 0x10, 0x46);
    func_020f0ddc(q + 0x1c, 0x28);
    func_020f0d98(q + 0x10, 0x7f, 5);
    func_020f0d98(q + 0x1c, 0x7f, 5);
}
