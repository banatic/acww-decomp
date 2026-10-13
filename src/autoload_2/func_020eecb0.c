/* func_020eecb0 @ 0x020eecb0, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eec48(int);
extern int NNS_SndArcLoadGroup(int, int);
extern int NNS_SndHeapSaveState(int);
extern void OS_Terminate(void);
extern int data_021fd048;

int func_020eecb0(int arg)
{
    int ret = func_020eec48(arg);
    if (NNS_SndArcLoadGroup(arg, data_021fd048) == 0) {
        return -1;
    }
    if (NNS_SndHeapSaveState(data_021fd048) == -1) {
        OS_Terminate();
    }
    return ret;
}
