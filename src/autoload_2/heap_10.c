/* heap_10: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9ec4 @ 0x020e9ec4, 0x10 bytes, ARM
 * func_020e9eb4 @ 0x020e9eb4, 0x10 bytes, ARM
 * func_020e9eac @ 0x020e9eac, 0x8 bytes, ARM
 * func_020e9ea4 @ 0x020e9ea4, 0x8 bytes, ARM
 */

struct func_020e9ec4_arg {
    char pad_00[0x14];
    void *unk_14;
};

struct UnkStruct_020e9eb4 {
    char pad_00[0x14];
    void *unk_14;
};

extern void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int alignment);
extern void *NNS_FndAllocFromFrmHeapEx(void *heap, unsigned int size, int alignment);

void *func_020e9ec4(struct func_020e9ec4_arg *arg, unsigned int size, int alignment)
{
    return NNS_FndAllocFromExpHeapEx(arg->unk_14, size, alignment);
}

void *func_020e9eb4(struct UnkStruct_020e9eb4 *p, unsigned int size, int alignment)
{
    return NNS_FndAllocFromFrmHeapEx(p->unk_14, size, alignment);
}

int func_020e9eac(void)
{
    return 1;
}

int func_020e9ea4(void)
{
    return 1;
}
