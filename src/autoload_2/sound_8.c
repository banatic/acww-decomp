/* sound_8: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eedfc @ 0x020eedfc, 0xc bytes, ARM
 * func_020eede8 @ 0x020eede8, 0x14 bytes, ARM
 * func_020eedb8 @ 0x020eedb8, 0x30 bytes, ARM
 * func_020eed68 @ 0x020eed68, 0x50 bytes, ARM
 * func_020eed48 @ 0x020eed48, 0x20 bytes, ARM
 * func_020eed18 @ 0x020eed18, 0x30 bytes, ARM
 */

extern void NNS_SndMain(void);
extern unsigned char data_021fd04c[];
extern void OS_Terminate(void);
extern int NNS_SndArcPlayerStartSeqArc(void *, int, int);
extern int NNS_SndArcPlayerStartSeqArcEx(int, int, int, int, int, int);
extern void func_0210b7e0(void *self);
extern int NNS_SndPlayerStopSeq(int, int);

int func_020eedb8(int r0, int r1, int r2);

void func_020eedfc(void)
{
    NNS_SndMain();
}

int func_020eede8(int a, int b)
{
    return func_020eedb8(a, b, (unsigned int) data_021fd04c);
}

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

void func_020eed68(int a, int b, int c, int d, int e, int f)
{
    if (a == 0) {
        OS_Terminate();
    }
    NNS_SndArcPlayerStartSeqArcEx(a, b, c, d, e, f);
}

void func_020eed48(void *self)
{
    if (self == 0) {
        OS_Terminate();
    }
    func_0210b7e0(self);
}

int func_020eed18(int a, int b)
{
    if (a == 0) {
        OS_Terminate();
    }
    return NNS_SndPlayerStopSeq(a, b);
}
