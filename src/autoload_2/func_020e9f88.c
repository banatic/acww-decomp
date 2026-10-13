/* func_020e9f88 @ 0x020e9f88, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    void *unk_14;
} UnkStruct_020e9f88;
extern void NNS_FndDestroyFrmHeap(void *);
void func_020e9f88(UnkStruct_020e9f88 *self)
{
    NNS_FndDestroyFrmHeap(self->unk_14);
    self->unk_14 = 0;
}
