/* func_020eec48 @ 0x020eec48, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_SndHeapGetCurrentLevel(void *);
extern void *data_021fd048;

int func_020eec48(void)
{
    return NNS_SndHeapGetCurrentLevel(data_021fd048);
}
