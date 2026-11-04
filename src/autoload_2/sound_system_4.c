/* sound_system_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f1074 @ 0x020f1074, 0x44 bytes, ARM
 * func_020f1030 @ 0x020f1030, 0x44 bytes, ARM
 */

extern void func_020f0ddc(void *p, int n);
extern void func_020f0d98(void *p, int n, int m);

void func_020f1074(void *self)
{
    unsigned char *b = (unsigned char *) self;
    b[0x61] = 1;
    if (b[0x60] == 0) {
        func_020f0ddc((char *) self + 0x1c, 0x7f);
        func_020f0d98((char *) self + 0x1c, 0x28, 0xf);
    }
}

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
