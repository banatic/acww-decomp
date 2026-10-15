/* func_020a0140 @ 0x020a0140, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __arm MI_CompressLZ(const void *a, int b, int *c);
extern void __arm MI_CpuCopy8(const void *a, int *b, int c);

extern char data_021dc7a8[];

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a0140;

void func_020a0140(UnkStruct_020a0140 *s)
{
    int result;
    result = MI_CompressLZ(data_021dc7a8, 0x000173fc, &s->unk_04);
    if (result == 0) {
        s->unk_00 = 0;
        MI_CpuCopy8(data_021dc7a8, &s->unk_04, 0x000173fc);
    } else {
        s->unk_00 = result;
    }
}
