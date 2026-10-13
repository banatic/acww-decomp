/* func_02019e80 @ 0x02019e80, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
    unsigned int unk_28;
} UnkStruct_02019e80;

extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);

void func_02019e80(UnkStruct_02019e80 *a, UnkStruct_02019e80 *b)
{
    MI_CpuCopy8(b, a, 0x34);
    a->unk_28 = b->unk_28;
}
