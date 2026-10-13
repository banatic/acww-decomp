/* func_020e9e20 @ 0x020e9e20, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020e9e20 {
    char pad_00[0x14];
    int unk_14;
};

extern int NNS_FndGetAllocatableSizeForExpHeapEx(int a, int b);

int func_020e9e20(struct UnkStruct_020e9e20 *self)
{
    return NNS_FndGetAllocatableSizeForExpHeapEx(self->unk_14, 4);
}
