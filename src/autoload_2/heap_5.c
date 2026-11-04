/* heap_5: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020e9c1c @ 0x020e9c1c, 0x2c bytes, ARM
 * func_020e9bf4 @ 0x020e9bf4, 0x28 bytes, ARM
 */

struct UnkStruct_020e9c1c {
    char pad_00[0x14];
    void *unk_14;
};

extern void NNS_FndFreeToExpHeap(void *heap, void *block);
extern void OS_Terminate(void);

void func_020e9c1c(void *self, void *block)
{
    if (block == 0) {
        return;
    }
    NNS_FndFreeToExpHeap(((struct UnkStruct_020e9c1c *) self)->unk_14, block);
}

void func_020e9bf4(int p0, int p1)
{
    if (p1 == 0) {
        return;
    }
    OS_Terminate();
}
