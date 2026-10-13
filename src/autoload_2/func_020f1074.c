/* func_020f1074 @ 0x020f1074, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
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
