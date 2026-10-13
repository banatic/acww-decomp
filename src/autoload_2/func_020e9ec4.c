/* func_020e9ec4 @ 0x020e9ec4, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndAllocFromExpHeapEx(void *);

struct func_020e9ec4_arg {
    char pad_00[0x14];
    void *unk_14;
};

int func_020e9ec4(struct func_020e9ec4_arg *arg)
{
    return NNS_FndAllocFromExpHeapEx(arg->unk_14);
}
