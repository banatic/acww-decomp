/* func_020f1030 @ 0x020f1030, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020f0ddc(void *p, int n);
extern void func_020f0d98(void *p, int a, int b);

void func_020f1030(void *self)
{
    unsigned char *p = (unsigned char *) self;

    p[0x61] = 0;
    if (p[0x60] != 0) {
        return;
    }

    func_020f0ddc(p + 0x1c, 0x28);
    func_020f0d98(p + 0x1c, 0x7f, 0xf);
}
