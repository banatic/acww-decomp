/* func_02091140 @ 0x02091140, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021d52cc;
extern void *NNS_FndAllocFromFrmHeapEx(void *heap, unsigned int size, int align);

void *func_02091140(unsigned int param)
{
    return NNS_FndAllocFromFrmHeapEx(data_021d52cc, param, 4);
}
