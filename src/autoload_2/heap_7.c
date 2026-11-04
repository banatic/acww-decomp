/* heap_7: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9dbc @ 0x020e9dbc, 0x14 bytes, ARM
 * func_020e9da8 @ 0x020e9da8, 0x14 bytes, ARM
 */

typedef struct {
    char pad_00[0x14];
    void *ptr;
} UnkStruct_020e9dbc;

struct UnkStruct_020e9da8 {
    char pad_00[0x14];
    int unk_14;
};

extern unsigned int NNS_FndGetAllocatableSizeForExpHeapEx(void *heap, int alignment);
extern int NNS_FndGetAllocatableSizeForFrmHeapEx(int a, int b);

int func_020e9dbc(UnkStruct_020e9dbc *self)
{
    return NNS_FndGetAllocatableSizeForExpHeapEx(self->ptr, 4);
}

int func_020e9da8(struct UnkStruct_020e9da8 *p)
{
    return NNS_FndGetAllocatableSizeForFrmHeapEx(p->unk_14, 4);
}
