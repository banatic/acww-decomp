/* sound_system: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f0f34 @ 0x020f0f34, 0x14 bytes, ARM
 * func_020f0edc @ 0x020f0edc, 0x58 bytes, ARM
 * func_020f0ea8 @ 0x020f0ea8, 0x34 bytes, ARM
 * func_020f0e74 @ 0x020f0e74, 0x34 bytes, ARM
 * func_020f0e60 @ 0x020f0e60, 0x14 bytes, ARM
 */

extern int func_020eede8(int, int);
extern void NNS_SndPlayerSetVolume(void *dst, int value);
extern void func_020eed68(void *p, int a, int b, int c, int d, int e);
extern void *func_020eed18(void *p, int arg);

int func_020f0f34(void *context, void *receiver)
{
    return func_020eede8(0x2c, 0);
}

void func_020f0edc(void *self, int param)
{
    int a, b;

    if (param < 0) {
        a = 0x10;
        b = 0x50;
    } else {
        a = (param << 1) + 0x10;
        b = param + 0x50;
    }

    if (a > 0x7f) {
        a = 0x7f;
    }
    if (b > 0x7f) {
        b = 0x7f;
    }

    NNS_SndPlayerSetVolume((char *) self + 0x38, a);
    NNS_SndPlayerSetVolume((char *) self + 0x40, b);
}

void func_020f0ea8(void *p, int x)
{
    func_020eed68((char *) p + 0x40, 10, -1, -1, 0, x);
}

void func_020f0e74(void *p, int b)
{
    func_020eed68((char *) p + 0x40, 10, -1, -1, 0, b);
}

void *func_020f0e60(void *p)
{
    return func_020eed18((char *) p + 0x40, 0);
}
