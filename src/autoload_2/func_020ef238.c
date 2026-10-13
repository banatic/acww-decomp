/* func_020ef238 @ 0x020ef238, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_Terminate(void);
extern void NNS_SndHandleReleaseSeq(unsigned char *p);

void func_020ef238(unsigned char *self)
{
    int i;
    unsigned char *p;

    if (self == 0) {
        OS_Terminate();
    }
    i = 0;
    if ((int) self[0x36] > 0) {
        p = self + 8;
        do {
            NNS_SndHandleReleaseSeq(p);
            i = i + 1;
            p = p + 0xc;
        } while (i < (int) self[0x36]);
    }
}
