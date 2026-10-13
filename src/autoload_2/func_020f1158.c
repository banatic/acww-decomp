/* func_020f1158 @ 0x020f1158, 0x78 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerSetPlayerVolume(int, int);

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
