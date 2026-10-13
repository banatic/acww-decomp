/* func_020f0ea8 @ 0x020f0ea8, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eed68(void *p, int a, int b, int c, long long d);

void func_020f0ea8(void *p, int x)
{
    func_020eed68((char *) p + 0x40, 10, -1, -1, ((long long) x << 32));
}
