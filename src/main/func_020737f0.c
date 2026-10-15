/* func_020737f0 @ 0x020737f0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xD4];
    int unk_D4;
} UnkStruct_020737f0;

extern int func_02073d90(UnkStruct_020737f0 *a);
extern void __arm MI_CpuCopy8(int a, int b, int c);

void func_020737f0(UnkStruct_020737f0 *a, int b, int c)
{
    if (func_02073d90(a)) {
        MI_CpuCopy8(b, a->unk_D4, c);
        a->unk_D4 = a->unk_D4 + c;
    }
}
