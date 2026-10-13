/* func_020e9b68 @ 0x020e9b68, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b84(void);
extern void NNS_FndVisitAllocatedForExpHeap(void *, void (*)(void), int);

typedef struct {
    unsigned char pad_00[0x14];
    void *unk_14;
} Unk020e9b68;

void func_020e9b68(Unk020e9b68 *self)
{
    NNS_FndVisitAllocatedForExpHeap(self->unk_14, func_020e9b84, 0);
}
