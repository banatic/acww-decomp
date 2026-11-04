/* sound_system_5: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f1158 @ 0x020f1158, 0x78 bytes, ARM
 * func_020f1108 @ 0x020f1108, 0x50 bytes, ARM
 * func_020f10b8 @ 0x020f10b8, 0x50 bytes, ARM
 */

extern void NNS_SndPlayerSetPlayerVolume(int, int);
extern void func_020f0ddc(void *p, int len);
extern void func_020f0d98(void *p, int a, int b);

void func_020f1158(int a, int value)
{
    if (value > 0x7f) {
        value = 0x7f;
    } else if (value < 0) {
        value = 0;
    }
    NNS_SndPlayerSetPlayerVolume(5, value);
    NNS_SndPlayerSetPlayerVolume(6, value);
    NNS_SndPlayerSetPlayerVolume(0x10, value);
    NNS_SndPlayerSetPlayerVolume(0x11, value);
    NNS_SndPlayerSetPlayerVolume(0x12, value);
    NNS_SndPlayerSetPlayerVolume(0x13, value);
    NNS_SndPlayerSetPlayerVolume(0x14, value);
}

void func_020f1108(char *s)
{
    s[0x60] = 1;
    func_020f0ddc(s + 0x10, 0x7f);
    func_020f0ddc(s + 0x1c, 0x7f);
    func_020f0d98(s + 0x10, 0x46, 0x0f);
    func_020f0d98(s + 0x1c, 0x28, 0x0f);
}

void func_020f10b8(void *p)
{
    char *q = (char *) p;
    q[0x60] = 0;
    func_020f0ddc(q + 0x10, 0x46);
    func_020f0ddc(q + 0x1c, 0x28);
    func_020f0d98(q + 0x10, 0x7f, 5);
    func_020f0d98(q + 0x1c, 0x7f, 5);
}
