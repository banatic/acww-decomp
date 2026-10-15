/* func_020eed18 @ 0x020eed18, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern int NNS_SndPlayerStopSeq(int, int);

int func_020eed18(int a, int b)
{
    if (a == 0) {
        OS_Terminate();
    }
    return NNS_SndPlayerStopSeq(a, b);
}
