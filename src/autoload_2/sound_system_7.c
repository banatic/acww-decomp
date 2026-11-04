/* sound_system_7: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f162c @ 0x020f162c, 0x30 bytes, ARM
 * func_020f161c @ 0x020f161c, 0x10 bytes, ARM
 */

extern int NNS_SndArcPlayerStartSeq(void *, int sequence);
extern void NNS_SndPlayerSetVolume(void *, int);
extern void *NNS_SndPlayerStopSeq(void *);

void func_020f162c(void *r0, int r1, int r2)
{
    NNS_SndArcPlayerStartSeq((char *) r0 + 0x3c, r1);
    NNS_SndPlayerSetVolume((char *) r0 + 0x3c, r2);
}

void *func_020f161c(void *self)
{
    return NNS_SndPlayerStopSeq((void *) ((char *) self + 0x3c));
}
