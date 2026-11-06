/* sound_7: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eec60 @ 0x020eec60, 0x50 bytes, ARM
 * func_020eec48 @ 0x020eec48, 0x18 bytes, ARM
 */

extern void OS_Terminate(void);
extern void NNS_SndHeapLoadState(int a, int b);
extern int data_021fd048;
extern int NNS_SndHeapGetCurrentLevel(void *);

int func_020eec48(void);

void func_020eec60(int param)
{
    if (param == 0xff) {
        OS_Terminate();
    }
    if (param == 0) {
        OS_Terminate();
    }
    NNS_SndHeapLoadState(data_021fd048, param);
    if (param != func_020eec48()) {
        OS_Terminate();
    }
    func_020eec48();
}

int func_020eec48(void)
{
    return NNS_SndHeapGetCurrentLevel((*(void **) &data_021fd048));
}
