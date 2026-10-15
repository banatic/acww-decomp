/* func_020e9d54 @ 0x020e9d54, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndGetAllocatableSizeForExpHeapEx(int, int alignment);

struct UnkStruct_020e9d54 {
    char pad_00[0x14];
    int unk_14;
};

int func_020e9d54(struct UnkStruct_020e9d54 *self, int alignment)
{
    return NNS_FndGetAllocatableSizeForExpHeapEx(self->unk_14, alignment);
}
