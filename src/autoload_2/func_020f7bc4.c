/* func_020f7bc4 @ 0x020f7bc4, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_Terminate(void);
extern int NNS_SndArcPlayerStartSeqArc(int, int, int);

int func_020f7bc4(int a1, int a2, int a3)
{
    if (a3 == 0) {
        OS_Terminate();
    }
    return NNS_SndArcPlayerStartSeqArc(a3, 1, a2 % 1000);
}
