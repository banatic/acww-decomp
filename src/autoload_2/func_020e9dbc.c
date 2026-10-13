/* func_020e9dbc @ 0x020e9dbc, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndGetAllocatableSizeForExpHeapEx(void *a, int b, int c, int d);

typedef struct {
    char pad_00[0x14];
    void *ptr;
} UnkStruct_020e9dbc;

int func_020e9dbc(UnkStruct_020e9dbc *self, int unused, int c, int d)
{
    return NNS_FndGetAllocatableSizeForExpHeapEx(self->ptr, 4, c, d);
}
