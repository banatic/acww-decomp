/* func_020e9d44 @ 0x020e9d44, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndGetAllocatableSizeForFrmHeapEx(int, int alignment);
struct UnkStruct_020e9d44 {
    unsigned char pad_00[0x14];
    int unk_14;
};
int func_020e9d44(struct UnkStruct_020e9d44 *obj, int alignment)
{
    return NNS_FndGetAllocatableSizeForFrmHeapEx(obj->unk_14, alignment);
}
