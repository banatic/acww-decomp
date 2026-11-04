/* heap_6: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9d54 @ 0x020e9d54, 0x10 bytes, ARM
 * func_020e9d44 @ 0x020e9d44, 0x10 bytes, ARM
 * func_020e9d34 @ 0x020e9d34, 0x10 bytes, ARM
 * func_020e9d20 @ 0x020e9d20, 0x14 bytes, ARM
 */

struct UnkStruct_020e9d54 {
    char pad_00[0x14];
    int unk_14;
};

struct UnkStruct_020e9d44 {
    unsigned char pad_00[0x14];
    int unk_14;
};

struct func_020e9d34_arg {
    char pad_00[0x14];
    unsigned int value;
};

extern int NNS_FndGetAllocatableSizeForExpHeapEx(int, int alignment);
extern int NNS_FndGetAllocatableSizeForFrmHeapEx(int, int alignment);
extern int NNS_FndGetTotalFreeSizeForExpHeap(unsigned int);

int func_020e9d54(struct UnkStruct_020e9d54 *self, int alignment)
{
    return NNS_FndGetAllocatableSizeForExpHeapEx(self->unk_14, alignment);
}

int func_020e9d44(struct UnkStruct_020e9d44 *obj, int alignment)
{
    return NNS_FndGetAllocatableSizeForFrmHeapEx(obj->unk_14, alignment);
}

int func_020e9d34(struct func_020e9d34_arg *self)
{
    return NNS_FndGetTotalFreeSizeForExpHeap(self->value);
}

void func_020e9d20(void *p)
{
    NNS_FndGetAllocatableSizeForFrmHeapEx(*(int *) ((char *) p + 0x14), 4);
}
