/* func_020f9f98 @ 0x020f9f98, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_SndPlayerReadGlobalVariable(int, short *);
extern short data_021fd26c;

unsigned char func_020f9f98(void)
{
    short v;
    NNS_SndPlayerReadGlobalVariable(2, &v);
    data_021fd26c = v;
    return (unsigned char) v;
}
