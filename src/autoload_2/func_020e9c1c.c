/* func_020e9c1c @ 0x020e9c1c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_020e9c1c {
    char pad_00[0x14];
    void *unk_14;
};

extern void *NNS_FndFreeToExpHeap(void *);

void *func_020e9c1c(void *self, int enable)
{
    if (enable == 0) {
        return self;
    }
    return NNS_FndFreeToExpHeap(((struct UnkStruct_020e9c1c *) self)->unk_14);
}
