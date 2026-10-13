/* func_020eed68 @ 0x020eed68, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(int);
extern void NNS_SndArcPlayerStartSeqArcEx(int, int, int, int, int, int);

void func_020eed68(int a, int b, int c, int d, int e, int f)
{
    if (a == 0) {
        OS_Terminate(a);
    }
    NNS_SndArcPlayerStartSeqArcEx(a, b, c, d, e, f);
}
