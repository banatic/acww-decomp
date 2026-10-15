/* func_020733d0 @ 0x020733d0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *, void *, unsigned int);

typedef struct {
    unsigned char pad_00[0x104];
    unsigned int unk_104;
} UnkStruct_020733d0;

void func_020733d0(UnkStruct_020733d0 *obj, unsigned int p1, unsigned int delta)
{
    MI_CpuCopy8((const void *) p1, (void *) obj->unk_104, delta);
    obj->unk_104 += delta;
}
