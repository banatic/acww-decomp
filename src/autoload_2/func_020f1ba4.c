/* func_020f1ba4 @ 0x020f1ba4, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void NNS_SndArcStrmMoveVolume(void *p, int v, int w);
extern void NNS_SndPlayerMoveVolume(void *p, int v, int w);

void func_020f1ba4(unsigned char *self, int v, int w)
{
    unsigned int has;

    if (v > 0x7f) {
        v = 0x7f;
    } else if (v < 0) {
        v = 0;
    }
    has = (*(int *) (self + 0x34) != 0);
    if (has > 0) {
        NNS_SndArcStrmMoveVolume(self + 0x34, v, w);
    } else {
        NNS_SndPlayerMoveVolume(self + 0x3c, v, w);
    }
}
