/* func_020f11d0 @ 0x020f11d0, 0xfc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void NNS_SndPlayerSetPlayerVolume(int player, int volume);

void func_020f11d0(unsigned char *self, int volL, int volR)
{
    int half;

    if (volL > 0x7f) {
        volL = 0x7f;
    } else if (volL < 0) {
        volL = 0;
    }

    if (volR > 0x7f) {
        volR = 0x7f;
    } else if (volR < 0) {
        volR = 0;
    }

    half = volL >> 1;

    NNS_SndPlayerSetPlayerVolume(4, volL);
    NNS_SndPlayerSetPlayerVolume(7, volL);
    NNS_SndPlayerSetPlayerVolume(13, volL);
    NNS_SndPlayerSetPlayerVolume(9, volL);
    NNS_SndPlayerSetPlayerVolume(8, volR);
    NNS_SndPlayerSetPlayerVolume(11, volR);

    if (self[0x61] != 0) {
        return;
    }

    NNS_SndPlayerSetPlayerVolume(5, volR);
    NNS_SndPlayerSetPlayerVolume(6, volR);
    NNS_SndPlayerSetPlayerVolume(16, volR);
    NNS_SndPlayerSetPlayerVolume(17, volR);
    NNS_SndPlayerSetPlayerVolume(18, half);
    NNS_SndPlayerSetPlayerVolume(19, half);
    NNS_SndPlayerSetPlayerVolume(20, volR);

    return;
}
