/* func_020e9d20 @ 0x020e9d20, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_FndGetAllocatableSizeForFrmHeapEx(int, int);

void func_020e9d20(void *p)
{
    NNS_FndGetAllocatableSizeForFrmHeapEx(*(int *) ((char *) p + 0x14), 4);
}
