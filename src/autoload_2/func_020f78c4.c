/* func_020f78c4 @ 0x020f78c4, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_SndArcPlayerStartSeq(void *dst, int size);

void func_020f78c4(void *self)
{
    NNS_SndArcPlayerStartSeq((char *) self + 4, 0xac);
    ((char *) self)[0xd] = 0;
}
