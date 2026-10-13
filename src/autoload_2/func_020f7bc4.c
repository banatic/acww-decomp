/* func_020f7bc4 @ 0x020f7bc4, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_Terminate(int);
extern void NNS_SndArcPlayerStartSeqArc(int, int, int);

void func_020f7bc4(int a1, int a2, int a3)
{
    if (a3 == 0) {
        OS_Terminate(a1);
    }
    NNS_SndArcPlayerStartSeqArc(a3, 1, a2 % 1000);
}
