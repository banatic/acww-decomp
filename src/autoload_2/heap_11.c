/* heap_11: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9fc8 @ 0x020e9fc8, 0xc bytes, ARM
 * func_020e9fa8 @ 0x020e9fa8, 0x20 bytes, ARM
 * func_020e9f88 @ 0x020e9f88, 0x20 bytes, ARM
 */

struct S020e9fa8 {
    char pad_00[0x14];
    int unk_14;
};

typedef struct {
    char pad_00[0x14];
    void *unk_14;
} UnkStruct_020e9f88;

extern void func_020e9fd4(void *argument0);
extern void func_02101e20(int arg);
extern void NNS_FndDestroyFrmHeap(void *);

void func_020e9fc8(void *argument0)
{
    func_020e9fd4(argument0);
}

void func_020e9fa8(struct S020e9fa8 *s)
{
    func_02101e20(s->unk_14);
    s->unk_14 = 0;
}

void func_020e9f88(UnkStruct_020e9f88 *self)
{
    NNS_FndDestroyFrmHeap(self->unk_14);
    self->unk_14 = 0;
}
