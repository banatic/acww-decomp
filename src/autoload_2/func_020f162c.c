/* func_020f162c @ 0x020f162c, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndArcPlayerStartSeq(void *);
extern void NNS_SndPlayerSetVolume(void *, int);

void func_020f162c(void *r0, int r1, int r2)
{
    NNS_SndArcPlayerStartSeq((char *) r0 + 0x3c);
    NNS_SndPlayerSetVolume((char *) r0 + 0x3c, r2);
}
