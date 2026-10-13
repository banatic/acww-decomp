/* func_020f1004 @ 0x020f1004, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f0ddc(void *p, int n);
extern void func_020f0d98(void *p, int n, int m);

void func_020f1004(void *p)
{
    func_020f0ddc((char *) p + 4, 0);
    func_020f0d98((char *) p + 4, 0x7f, 0x3c);
}
