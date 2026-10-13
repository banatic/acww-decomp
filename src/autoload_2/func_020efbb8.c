/* func_020efbb8 @ 0x020efbb8, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern void NNS_SndArcPlayerStartSeqArcEx(int p0, int p1, int p2, int p3, int p4, int p5);

void func_020efbb8(int r0, int r1, int r2)
{
    int r4;
    int r5;
    int r3;
    int ip;
    int r0b;
    int r2b;
    int ipb;

    r4 = r0 + 8 + r1 * 12;
    r5 = r2;
    r0b = *(unsigned char *) (r0 + 0x36);
    if (r0b == 0) {
        OS_Terminate();
    }
    r2b = *(unsigned char *) (r4 + 8);
    r3 = -1;
    ipb = *(unsigned short *) (r4 + 6);
    NNS_SndArcPlayerStartSeqArcEx(r4, r3, r3, r5, r2b, ipb);
}
