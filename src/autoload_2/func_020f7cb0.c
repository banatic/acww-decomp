/* func_020f7cb0 @ 0x020f7cb0, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerSetVolume(void *p, int v);

void func_020f7cb0(void *p)
{
    NNS_SndPlayerSetVolume((char *) p + 4, 0);
    NNS_SndPlayerSetVolume((char *) p + 8, 0);
}
