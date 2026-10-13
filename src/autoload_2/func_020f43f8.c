/* func_020f43f8 @ 0x020f43f8, 0xc0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerStopSeqByPlayerNo(int playerNo, int handle);

void func_020f43f8(int unused, int handle)
{
    NNS_SndPlayerStopSeqByPlayerNo(0xb, handle);
    NNS_SndPlayerStopSeqByPlayerNo(2, handle);
    NNS_SndPlayerStopSeqByPlayerNo(4, handle);
    NNS_SndPlayerStopSeqByPlayerNo(5, handle);
    NNS_SndPlayerStopSeqByPlayerNo(6, handle);
    NNS_SndPlayerStopSeqByPlayerNo(7, handle);
    NNS_SndPlayerStopSeqByPlayerNo(8, handle);
    NNS_SndPlayerStopSeqByPlayerNo(9, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0xa, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0xc, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0xf, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x10, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x11, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x12, handle);
    NNS_SndPlayerStopSeqByPlayerNo(0x13, handle);
}
