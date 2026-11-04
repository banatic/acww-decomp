/* sound_system_3: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f1004 @ 0x020f1004, 0x2c bytes, ARM
 * func_020f0ff0 @ 0x020f0ff0, 0x14 bytes, ARM
 */

extern void func_020f0ddc(void *p, int n);
extern void func_020f0d98(void *p, int n, int m);

void func_020f1004(void *p)
{
    func_020f0ddc((char *) p + 4, 0);
    func_020f0d98((char *) p + 4, 0x7f, 0x3c);
}

int *func_020f0ff0(int *p)
{
    int *q;
    q = (int *) *p;
    if (q != 0) {
        return q + 5;
    } else {
        return 0;
    }
}
