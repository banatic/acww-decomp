/* func_020f503c @ 0x020f503c, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerWriteVariable(void *p, int a, int b, int c);

void func_020f503c(void *p, int a, int b, int c)
{
    NNS_SndPlayerWriteVariable((char *) p + 8, 0, a, c);
}
