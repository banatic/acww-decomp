/* func_020e9b2c @ 0x020e9b2c, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndSetGroupIDForExpHeap(void *);
struct UnkStruct_020e9b2c {
    unsigned char pad_00[0x14];
    void *unk_14;
};
int func_020e9b2c(struct UnkStruct_020e9b2c *s)
{
    return NNS_FndSetGroupIDForExpHeap(s->unk_14);
}
