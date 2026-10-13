/* func_020e9da8 @ 0x020e9da8, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndGetAllocatableSizeForFrmHeapEx(int a, int b);

struct UnkStruct_020e9da8 {
    char pad_00[0x14];
    int unk_14;
};

int func_020e9da8(struct UnkStruct_020e9da8 *p)
{
    return NNS_FndGetAllocatableSizeForFrmHeapEx(p->unk_14, 4);
}
