/* func_020f503c @ 0x020f503c, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_SndPlayerWriteVariable(void *handle, int index, short value);

void func_020f503c(void *p, short value)
{
    NNS_SndPlayerWriteVariable((char *) p + 8, 0, value);
}
