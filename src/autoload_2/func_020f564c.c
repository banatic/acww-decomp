/* func_020f564c @ 0x020f564c, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerStopSeqBySeqArcIdx(int, int, int);

void func_020f564c(void)
{
    int r4 = 0;
    int r5 = 2;
    int r6 = 0x52;
    while (r6 < 0x61) {
        NNS_SndPlayerStopSeqBySeqArcIdx(r5, r6, r4);
        r6++;
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(2, 0x36, 0);
}
