/* func_020ef918 @ 0x020ef918, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerStopSeq(int *p, int q);
extern void func_020ef8d0(int *p, int a, int b);

void func_020ef918(int *p, int q)
{
    if (*p != 0) {
        NNS_SndPlayerStopSeq(p, q);
    }
    func_020ef8d0(p, 2, 0);
    func_020ef8d0(p, 3, 0);
    func_020ef8d0(p, 1, 0);
}
