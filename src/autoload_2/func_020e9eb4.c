/* func_020e9eb4 @ 0x020e9eb4, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *NNS_FndAllocFromFrmHeapEx(void *heap, unsigned int size, int alignment);

struct UnkStruct_020e9eb4 {
    char pad_00[0x14];
    void *unk_14;
};

void *func_020e9eb4(struct UnkStruct_020e9eb4 *p, unsigned int size, int alignment)
{
    return NNS_FndAllocFromFrmHeapEx(p->unk_14, size, alignment);
}
