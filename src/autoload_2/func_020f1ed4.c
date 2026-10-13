/* func_020f1ed4 @ 0x020f1ed4, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void NNS_SndPlayerStopSeqBySeqArcIdx(int q, int r, int c);

void func_020f1ed4(void *self, int v, int a2)
{
    NNS_SndPlayerStopSeqBySeqArcIdx(v / 1000, v % 1000, a2);
}
