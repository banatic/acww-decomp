/* heap_4: 9 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9b84 @ 0x020e9b84, 0x18 bytes, ARM
 * func_020e9b68 @ 0x020e9b68, 0x1c bytes, ARM
 * func_020e9b54 @ 0x020e9b54, 0x14 bytes, ARM
 * func_020e9b44 @ 0x020e9b44, 0x10 bytes, ARM
 * func_020e9b3c @ 0x020e9b3c, 0x8 bytes, ARM
 * func_020e9b2c @ 0x020e9b2c, 0x10 bytes, ARM
 * func_020e9b24 @ 0x020e9b24, 0x8 bytes, ARM
 * func_020e9b14 @ 0x020e9b14, 0x10 bytes, ARM
 * func_020e9b0c @ 0x020e9b0c, 0x8 bytes, ARM
 */

typedef struct {
    unsigned char pad_00[0x14];
    void *unk_14;
} Unk020e9b68;

struct UnkStruct_020e9b2c {
    unsigned char pad_00[0x14];
    void *unk_14;
};

struct _S {
    char pad_00[0x14];
    void *unk_14;
};

extern void NNS_FndFreeToExpHeap(void *heap, void *memBlock);
extern void NNS_FndVisitAllocatedForExpHeap(void *, void (*)(void *, void *, unsigned int), int);
extern void NNS_FndFreeToFrmHeap(int a, int b);
extern int NNS_FndGetSizeForMBlockExpHeap(int x);
extern int NNS_FndSetGroupIDForExpHeap(void *, unsigned short group_id);
extern int NNS_FndGetGroupIDForExpHeap(void *p);

void func_020e9b84(void *memBlock, void *heap, unsigned int userParam)
{
    NNS_FndFreeToExpHeap(heap, memBlock);
}

void func_020e9b68(Unk020e9b68 *self)
{
    NNS_FndVisitAllocatedForExpHeap(self->unk_14, func_020e9b84, 0);
}

void func_020e9b54(void *self)
{
    NNS_FndFreeToFrmHeap(*(int *) ((char *) self + 0x14), 3);
}

int func_020e9b44(int a, int b)
{
    return NNS_FndGetSizeForMBlockExpHeap(b);
}

int func_020e9b3c(void)
{
    return -1;
}

int func_020e9b2c(struct UnkStruct_020e9b2c *s, unsigned short group_id)
{
    return NNS_FndSetGroupIDForExpHeap(s->unk_14, group_id);
}

int func_020e9b24(void)
{
    return 0;
}

int func_020e9b14(struct _S *obj)
{
    return NNS_FndGetGroupIDForExpHeap(obj->unk_14);
}

int func_020e9b0c(void)
{
    return 0;
}
