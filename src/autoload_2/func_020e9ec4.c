/* func_020e9ec4 @ 0x020e9ec4, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int alignment);

struct func_020e9ec4_arg {
    char pad_00[0x14];
    void *unk_14;
};

void *func_020e9ec4(struct func_020e9ec4_arg *arg, unsigned int size, int alignment)
{
    return NNS_FndAllocFromExpHeapEx(arg->unk_14, size, alignment);
}
