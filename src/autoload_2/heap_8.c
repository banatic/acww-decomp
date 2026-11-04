/* heap_8: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9e20 @ 0x020e9e20, 0x14 bytes, ARM
 * func_020e9e0c @ 0x020e9e0c, 0x14 bytes, ARM
 */

struct UnkStruct_020e9e20 {
    char pad_00[0x14];
    int unk_14;
};

extern int NNS_FndGetAllocatableSizeForExpHeapEx(int a, int b);
extern unsigned int NNS_FndGetAllocatableSizeForFrmHeapEx(int, int);

int func_020e9e20(struct UnkStruct_020e9e20 *self)
{
    return NNS_FndGetAllocatableSizeForExpHeapEx(self->unk_14, 4);
}

void func_020e9e0c(int *self)
{
    NNS_FndGetAllocatableSizeForFrmHeapEx(self[5], 4);
}
