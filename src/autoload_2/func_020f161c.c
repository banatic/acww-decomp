/* func_020f161c @ 0x020f161c, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *NNS_SndPlayerStopSeq(void *);

void *func_020f161c(void *self)
{
    return NNS_SndPlayerStopSeq((void *) ((char *) self + 0x3c));
}
