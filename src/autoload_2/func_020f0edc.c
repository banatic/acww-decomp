/* func_020f0edc @ 0x020f0edc, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerSetVolume(void *dst, int value);

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
