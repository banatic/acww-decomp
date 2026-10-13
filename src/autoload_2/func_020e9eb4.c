/* func_020e9eb4 @ 0x020e9eb4, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndAllocFromFrmHeapEx(int a);

struct UnkStruct_020e9eb4 {
    char pad_00[0x14];
    int unk_14;
};

int func_020e9eb4(struct UnkStruct_020e9eb4 *p)
{
    return NNS_FndAllocFromFrmHeapEx(p->unk_14);
}
