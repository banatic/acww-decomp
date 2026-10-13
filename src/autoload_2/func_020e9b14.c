/* func_020e9b14 @ 0x020e9b14, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndGetGroupIDForExpHeap(void *p);

struct _S {
    char pad_00[0x14];
    void *unk_14;
};

int func_020e9b14(struct _S *obj)
{
    return NNS_FndGetGroupIDForExpHeap(obj->unk_14);
}
