/* func_020eedb8 @ 0x020eedb8, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern int NNS_SndArcPlayerStartSeqArc(void *, int, int);

int func_020eedb8(int r0, int r1, int r2)
{
    int r4 = r2;
    int r6 = r0;
    int r5 = r1;

    if (r4 != 0) {
        goto label_020eedd0;
    }

    OS_Terminate();

label_020eedd0:
    return NNS_SndArcPlayerStartSeqArc((void *) r4, r5, r6);
}
